#pragma once

#include"Include.h"
using namespace std;

int CountLines(string filename)
{
	ifstream ReadFile;
	int n = 0;
	string tmp;
	ReadFile.open(filename.c_str());
	if (ReadFile.fail())
	{
		return 0;
	}
	else
	{
		while (getline(ReadFile, tmp, '\n'))
		{
			n++;
		}
		ReadFile.close();
		return n;
	}
}

string LineReader(string File, int line_number) {

	if (_access(File.c_str(), 0)) {
		return "FileNotExist";
	}
	int lines, i = 0;
	string temp;
	fstream file;
	file.open(File.c_str());
	lines = CountLines(File);

	if (line_number <= 0)
	{
		return "LineError";
	}
	if (file.fail())
	{
		return "ReadFailed";
	}
	if (line_number > lines)
	{
		return "overline";
	}
	while (getline(file, temp) && i < line_number - 1)
	{
		i++;
	}
	file.close();
	return temp;
}

string ReplaceChar(string info, string replaceword, string nword) {
	//cout << "New Replace :  _" << info << "_  _" << replaceword << "_  _" << nword << "_" << endl;
	int checkanti = checkChar(info, replaceword);
	if (checkanti == 1) {
		std::string dst_str = info;
		std::string::size_type pos = 0;
		while ((pos = dst_str.find(replaceword)) != std::string::npos)
		{
			dst_str.replace(pos, replaceword.length(), nword);
		}
		//cout << "Return Data :  _" << dst_str <<"_" << endl;
		return dst_str;
	}
	else {
		//cout << "Return Data :  _" << info << "_" << endl;
		return info;
	}
}

string cutlineblockA(string lines, string cutmark, int line) {
	string backapi;

	if (checkChar(lines, cutmark) == 0) {
		return "NUL";
	}

	char* readcut = NULL;

	char Texts[65535] = "a";
	char CUMark[65535] = "a";

	strcpy(Texts, lines.c_str());
	strcpy(CUMark, cutmark.c_str());

	int cutrecord = 1;
	char* token = strtok(Texts, CUMark);
	if (token == NULL) {
		backapi = "";
		return backapi;
	}

	if (cutrecord == line) {

		//cout << "CUTLINEBLOCK CHECK OK, RETURN :  _" << token << "_" << endl;
		backapi = token;
		return backapi;
	}

NextRollCR:
	if (cutrecord == line) {
		//cout << "CUTLINEBLOCK CHECK OK, RETURN :  _" << token << "_" << endl;
		backapi = token;
		return backapi;
	}
	if (token == NULL) {
		backapi = "";
		return backapi;
	}
	cutrecord++;
	token = strtok(NULL, CUMark);
	goto NextRollCR;
}

//Read Env NEW
string PartRead(string Info, string StartMark, string EndMark) {
	int MaxInfoSize = Info.size();
	int startmarkadd, endmarkadd, readptr;
	string readbufferPR;
	readptr = 0;

	if (StartMark == "$FROMSTART$") {
		startmarkadd = 0;
		goto SKIPGETMARKSTART;
	}

	//GetStart
	for (; readbufferPR != StartMark; readptr++) {
		if (readptr > MaxInfoSize) {
			//cout << "Message :  " << Info << endl;
			return "notfoundstart";
		}
		readbufferPR = Info[readptr];
	}

	startmarkadd = readptr;

SKIPGETMARKSTART:
	readbufferPR = "";
	//GetEnd
	if (EndMark == "$FROMEND$") {
		endmarkadd = MaxInfoSize;
		goto skipENDGET;
	}
	for (; readbufferPR != EndMark; readptr++) {
		if (readptr > MaxInfoSize) {
			return "notfoundEnd";
		}
		readbufferPR = Info[readptr];
	}

	endmarkadd = readptr;
	endmarkadd--;

skipENDGET:
	//cout << "Start :  " << startmarkadd << "  End :  " << endmarkadd << endl;

	//Start Process CMD

	//ReadPTR
	readbufferPR = "";
	for (readptr = startmarkadd; readptr != endmarkadd; readptr++) {
		readbufferPR = readbufferPR + Info[readptr];
	}

	return readbufferPR;
}

int numbufferC, PartSizeA;
string readbuffer,readbufferC, readbufferD;
string PartReadA(string Info, string StartMark, string EndMark, int RPartSizeA) {
	//Anti Search All
	if (RPartSizeA == 1) {
		return PartRead(Info, StartMark, EndMark);
	}

	int MAXSIZEA = Info.size();
	int readptr = 0;
	PartSizeA = RPartSizeA;
	int cbuffer = 0;

	int getStart, getEnd, getcurrent = 0;

	//FindStart
	if (StartMark == EndMark) {
		PartSizeA = PartSizeA * 2;
		PartSizeA--;
		PartSizeA--;
	}

	while (PartSizeA != getcurrent) {
		for (; readbufferC != StartMark; readptr++) {
			readbufferC = Info[readptr];
			if (readbufferC == StartMark) {
				getcurrent++;
			}
			//cout << "Read :  " << readptr << "Data :  " << readbufferC << endl;
			if (readptr > MAXSIZEA)return "pra.failed mark";
		}

		//cout << "A :  " << readbufferC << "  B :  " << getcurrent << endl;
		readbufferC = "";
	}
	//cout << "Start :  " << readptr << "  PartSA :  " << PartSizeA << endl;

	//GetStart
	for (; readbufferD != StartMark; readptr++) {
		if (readptr > MAXSIZEA) {
			return "sizeoutStart";
		}
		readbufferD = Info[readptr];
	}

	getStart = readptr;
	//cout << "Start Mark : " << getStart << endl;

SKIPGETMARKSTART:
	readbufferD = "";
	//GetEnd
	for (; readbufferD != EndMark; readptr++) {
		if (readptr > MAXSIZEA) {
			return "sizeoutEnd";
		}
		readbufferD = Info[readptr];
	}

	getEnd = readptr;

	//cout << "Start :  " << getStart<< "  End :  " << getEnd << endl;

	//Start Process CMD

	//ReadPTR
	readbufferD = "";
	getEnd--;
	for (readptr = getStart; readptr != getEnd; readptr++) {
		readbufferD = readbufferD + Info[readptr];
	}

	return readbufferD;

}

int charTotal(string info, string markchar) {
	int charsize = info.size();
	int totalget = 0;
	for (int readsize = 0; charsize != readsize; readsize++) {
		readbuffer = info[readsize];
		if (readbuffer == markchar) {
			totalget++;
			continue;
		}
		else {
			continue;
		}
	}
	return totalget;
}

string getendchar(string infos) {
	int numbuffer = infos.size();
	readbuffer = infos[numbuffer];
	return readbuffer;
}

string cutendchar(string infos) {
	int numbuffer = infos.size();
	if (numbuffer == 0) {
		return "FAILED";
	}
	numbuffer--;
	readbuffer = "";
	for (int rptr = 0; rptr != numbuffer; rptr++) {
		readbuffer = readbuffer + infos[rptr];
	}
	return readbuffer;
}
