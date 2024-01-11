#pragma once
#include"Include.h"

using namespace std;

string pathbuffer,getbufferdata;
string urltempbuffer;
string savebuffer = "failed";

string cutpathhead(string DATA) {
    string tempdata,outdata;
    int numbuffer = DATA.size();
    int baseNum = -1;

    while (true) {
        tempdata = DATA[numbuffer];
        if (tempdata == "/") break;
        numbuffer--;
        if (numbuffer < 0) {
            return DATA;
        }
    }
    numbuffer--;
    while (baseNum != numbuffer) {
        baseNum++;
        outdata = outdata + DATA[baseNum];
    };

    return outdata;
}

string cutpathheadQ(string DATA) {
    string tempdata, outdata;
    int numbuffer = DATA.size();
    int baseNum = -1;

    while (true) {
        tempdata = DATA[numbuffer];
        if (tempdata == "?") break;
        numbuffer--;
        if (numbuffer < 0) {
            return DATA;
        }
    }
    numbuffer--;
    while (baseNum != numbuffer) {
        baseNum++;
        outdata = outdata + DATA[baseNum];
    };

    return outdata;
}


void autospider(string url) {
    if (checkChar(url, "?")) {
        url = cutpathheadQ(url);
    }

    savebuffer = ReplaceChar(url, "https://", "");
    savebuffer = ReplaceChar(savebuffer, "http://", "");

    pathbuffer = cutpathhead(savebuffer);

    cout << "-----New URL :   <" << savebuffer << ">" << endl;

    winapi_mkdir(pathbuffer.c_str());
    
    if (check_file_existence(savebuffer.c_str()) == true) {
        return;
    }
    
    URLDown(url, savebuffer);

    if (check_file_existence(savebuffer.c_str()) == false) {
        savebuffer = savebuffer + "\\index.html";
        if (check_file_existence(savebuffer.c_str()) == true) {
            return;
        }
        URLDown(url, savebuffer);
    }

    if (check_file_existence(savebuffer.c_str()) == false) {
        cout << "-----Get Failed :  " << url << endl;
        cout << "-----Save on    :  " << savebuffer << endl;
        return;
    }

    //ROLL SAVEBUFFER
	for (int docroll = 1;1;docroll++) {
        //cout << "Start Read SB: " << savebuffer << "  --- docroll :  " << docroll << endl;
        getbufferdata = LineReader(savebuffer, docroll);

        if (getbufferdata == "ReadFailed") break;
        if (getbufferdata == "overline") break;
        if (getbufferdata == "FileNotExist") {
            cout << "Analysis Error :  File Not Exist :   " << savebuffer << endl;
            return;
        }

        string tempbufferA, tempbufferB;
        //Mutil Spider
        int maxquos = charTotal(getbufferdata, "\'");
        if (maxquos == 0) goto checkquo2;

        maxquos = maxquos / 2;

        for (int currentProcess = 1;currentProcess < maxquos;currentProcess++) {
            tempbufferA = PartReadA(getbufferdata, "\'", "\'", currentProcess);
            urltempbuffer = "nullurl";
            if (checkChar(tempbufferA, "https://") == 1) {
                urltempbuffer = "1";
            }
            if (checkChar(tempbufferA, "http://") == 1) {
                urltempbuffer = "1";
            }
            if (checkChar(tempbufferA, "\'//") == 1) {
                tempbufferA = "https:" + tempbufferA;
                urltempbuffer = "1";
            }
            if (urltempbuffer == "nullurl")continue;
            autospider(tempbufferA);
            continue;
        }

    checkquo2:
        maxquos = charTotal(getbufferdata, "\"");
        if (maxquos == 0)  continue;

        maxquos = maxquos / 2;

        for (int currentProcess = 1; currentProcess < maxquos; currentProcess++) {
            tempbufferA = PartReadA(getbufferdata, "\"", "\"", currentProcess);
            urltempbuffer = "nullurl";
            if (checkChar(tempbufferA, "https://") == 1) {
                urltempbuffer = "1";
            }
            if (checkChar(tempbufferA, "http://") == 1) {
                urltempbuffer = "1";
            }
            if (checkChar(tempbufferA, "\"//") == 1) {
                tempbufferA = "https:" + tempbufferA;
                urltempbuffer = "1";
            }
            if (urltempbuffer == "nullurl")continue;
            autospider(tempbufferA);
            continue;
        }
	}
    return;
}