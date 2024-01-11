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
    if (url == "") {
        return;
    }

    if (checkChar(url, "?")) {
        url = cutpathheadQ(url);
    }

    savebuffer = savepath + "\\" + ReplaceChar(url, "https://", "");
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
        
        //RollCommand
        int maxsmqt = charTotal(getbufferdata, "\'");
        for (int cmdreader = 1; maxsmqt > 1;cmdreader++) {
            tempbufferA = PartReadA(getbufferdata, "\'", "\'", cmdreader);
            maxsmqt--;
            maxsmqt--;
            int tbaBuffer = 0;
            if (checkChar(tempbufferA, "https://")) {
                tbaBuffer = 1;
            }
            if (checkChar(tempbufferA, "http://")) {
                tbaBuffer = 1;
            }
            if (tempbufferA == "pra.failed mark") {
                continue;
            }
            if (tempbufferA == "notfoundstart") {
                continue;
            }
            if (tempbufferA == "sizeoutStart") {
                continue;
            }
            if (tempbufferA == "sizeoutEnd") {
                continue;
            }

            if (tbaBuffer == 1) {
                autospider(tempbufferA);
                continue;
            }
            else {
                continue;
            }
        }
        //RollSmallQT
        int maxbgqt = charTotal(getbufferdata, "\"");
        for (int cmdreader = 1; maxbgqt > 1; cmdreader++) {
            tempbufferA = PartReadA(getbufferdata, "\"", "\"", cmdreader);
            maxbgqt--;
            maxbgqt--;
            int tbaBuffer = 0;
            if (checkChar(tempbufferA, "https://")) {
                tbaBuffer = 1;
            }
            if (checkChar(tempbufferA, "http://")) {
                tbaBuffer = 1;
            }
            if (tempbufferA == "pra.failed mark") {
                continue;
            }
            if (tempbufferA == "notfoundstart") {
                continue;
            }
            if (tempbufferA == "sizeoutStart") {
                continue;
            }
            if (tempbufferA == "sizeoutEnd") {
                continue;
            }

            if (tbaBuffer == 1) {
                autospider(tempbufferA);
                continue;
            }
            else {
                continue;
            }
        }
    }
    return;
}