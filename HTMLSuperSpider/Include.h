#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<random>
#include<direct.h>
#include<Windows.h> 
#include <io.h>

using namespace std;

const string savepath = "HSS-GET";
string spdurl;

int SpawnRandomNum(int min, int max) {

	string minb, maxb;
	minb = to_string(min);
	maxb = to_string(max);

	//string chars = "Min :  " + minb + "   Max :   " + maxb + "  Bug Report";
	//MessageBox(0, chars.c_str(), "MXBug Report", MB_OK);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max); // Missing
	int outdata = dis(gen);

	//string dis_str = to_string(dis(gen));
	//MessageBox(0,dis_str.c_str(),"Bug check",MB_OK);

	return dis(gen);
}

bool createmark(string File, string info) {
	ofstream CMark;
	CMark.open(File);
	CMark << info << endl;
	CMark.close();

	if (_access(File.c_str(), 0)) {
		return true;
	}
	else {
		return false;
	}
}

bool ExistFolder_check(string dir) {
	string tmpDoct = dir + "/" + "test~" + to_string(SpawnRandomNum(1, 999999)) + "~.mark";

	if (createmark(tmpDoct, "nWn")) {
		remove(tmpDoct.c_str());
		return true;
	}
	else {
		remove(tmpDoct.c_str());
		return false;
	}
}


//1 TRUE
//0 FALSE
int checkChar(string text, string chechchar) {
	const char* c = chechchar.c_str();

	if (text.find(c) != string::npos) {
		return 1;
	}
	else {
		return 0;
	}
}

void winapi_mkdir(string mk) {
	if (ExistFolder_check(mk)){
		mk = "md \"" + mk + "\"";
		if (system(mk.c_str()) == 1) {
			cout << " Create Failed .  Command : " << endl;
			cout << mk << endl;
		}
		return;
	}
	else {
		return;
	}
}

bool check_file_existence(const std::string& filename) {
	std::ifstream file(filename);
	if (file.is_open()) {
		return true;
	}
	else {
		return false;
	}
}

int urlrmapi = 0;