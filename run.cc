#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

void product_data(string& path){
    	//  产生数据
	ofstream outFile;
	outFile.open(path, ios::out); // 打开模式可省略
    outFile << 1234567 << "," << "aaa" << "," << 10 << "," << 12 << endl;
    // outFile << 52924702 << "," << "aaa" << "," << 13 << "," << 1136 << endl;  
    // outFile << 52924702 << "," << "aac" << "," << 20 << "," << 477 << endl;  
    // outFile << 52925641 << "," << "aab" << "," << 31 << "," << 907 << endl;  
    // outFile << 52927350 << "," << "aab" << "," << 29 << "," << 724 << endl;  
    // outFile << 52927783 << "," << "aac" << "," << 21 << "," << 638 << endl;  
    // outFile << 52930489 << "," << "aaa" << "," << 18 << "," << 1222 << endl; 
    // outFile << 52931654 << "," << "aaa" << "," << 9 << "," << 1077 << endl;  
    // outFile << 52933453 << "," << "aab" << "," << 9 << "," << 756 << endl;  
    // outFile << 52933458 << "," << "aad" << "," << 10 << "," << 800 << endl;  
    // outFile << 52933458 << "," << "aae" << "," << 20 << "," << 1000 << endl;  
    // outFile << 52933458 << "," << "aaf" << "," << 30 << "," << 900 << endl;  

	outFile.close();
}

void run_read(vector<vector<string>>& strArray, string& path){
    // 读文件
	ifstream inFile(path, ios::in);
	string lineStr;
	while (getline(inFile, lineStr))
	{
		// 打印整行字符串
		// cout << lineStr << endl;
		// 存成二维表结构
		stringstream ss(lineStr);
		string str;
		vector<string> lineArray;
		// 按照逗号分隔
		while (getline(ss, str, ',')){
            lineArray.push_back(str);
        }
			
		strArray.push_back(lineArray);
	}
}
void run_write(vector<vector<string>>&Vec, string& path){
    ofstream outFile;
	outFile.open(path, ios::out); // 打开模式可省略

    for(auto& vec: Vec){
        outFile << vec[0] << "," << vec[1] << "," << vec[2] << "," << vec[3] << "," << vec[4] << endl;
    }
	outFile.close();
}
int main(int argc, char** argv)
{
    // string in_path = "data/input.csv";
    // string out_path = "outputs/output.csv";
    // string in_path = "input.csv";
    // string out_path = "output.csv";
    string in_path = argv[1];
    string out_path = argv[2];

    /* 产生数据 需要自己生成input文件数据的时候打开它 */
    // product_data(in_path);

	vector<vector<string>>strArray; //从文件读取的数据，存到这
    // 读文件
    run_read(strArray, in_path);

    //debug 显示作用
    cout << "Orign---------" << endl;
    for(auto& vec: strArray){
        for(auto& ve : vec){
            cout << ve << " ";
        }
        cout << endl;
    }
    cout << endl;
	
    /*
    排序，复杂度：差不多是O(nlogn) ；
    如果数据文件是大文件，这块是耗时的因素
    */
    sort(strArray.begin(), strArray.end(), [](vector<string>& v1, vector<string>& v2){ return v1[1] < v2[1]; });

    //debug 显示作用
    cout << "Sorted---------" << endl;
    for(auto& vec: strArray){
        for(auto& ve : vec){
            cout << ve << " ";
        }
        cout << endl;
    }
    cout << endl;
    
    // 定义变量
    string symbol = strArray[0][1];
    string TimeStamp = strArray[0][0];
    long long Volume = 0, MaxPrice = 0, Weight = 0, MaxTimeGap = 0;

    vector<vector<string>>Vec;
    strArray.push_back({"", "", "", ""});
	for(auto& lineArray: strArray){
        if(lineArray[1] == symbol){
            long long num = strtoll(lineArray[2].c_str(), NULL, 10), price = strtoll(lineArray[3].c_str(), NULL, 10);;
            MaxTimeGap = max(MaxTimeGap, strtoll(lineArray[0].c_str(), NULL, 10) - strtoll(TimeStamp.c_str(), NULL, 10));
            TimeStamp = lineArray[0]; //
            Volume += num; //成交量 
            MaxPrice = max(MaxPrice, price); // 最大的价钱
            Weight += num * price;
        }else{
            //表明换了一个符号了
            vector<string>vs;

            vs.push_back(symbol);
            vs.push_back(to_string(MaxTimeGap));
            vs.push_back(to_string(Volume));
            vs.push_back(to_string(Weight / Volume)); /////
            vs.push_back(to_string(MaxPrice));

            symbol = lineArray[1];
            TimeStamp = lineArray[0];
            MaxTimeGap = 0;
            Weight = strtoll(lineArray[2].c_str(), NULL, 10) * strtoll(lineArray[3].c_str(), NULL, 10);;
            Volume = strtoll(lineArray[2].c_str(), NULL, 10);
            MaxPrice = strtoll(lineArray[3].c_str(), NULL, 10);
            
            Vec.push_back(vs);
        }
        
    }

    // debug 显示作用
    cout << "Output---------" << endl;
    for(auto& vec: Vec){
        for(auto& ve : vec){
            cout << ve << " ";
        }
        cout << endl;
    }
    cout << endl;

    // 写文件
    run_write(Vec, out_path);
	
    //完结
	return 0;
}