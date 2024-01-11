#pragma once
#include<Windows.h> 
#include<direct.h>
#include <fstream>
#include <io.h>
#include <string>

#include<urlmon.h>
#pragma comment(lib,"URlmon.lib")
using namespace std;
LPCWSTR stringToLPCWSTR(string orig)
{
	size_t origsize = orig.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t* wcstring = new wchar_t[sizeof(wchar_t) * (orig.length() - 1)];
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);
	return wcstring;
}

//0-FAILED
//1-TRUE
bool URLDown(string URL, string Save) {
	remove(Save.c_str());

	LPCWSTR LcDsp = stringToLPCWSTR(Save);
	LPCWSTR LcURL = stringToLPCWSTR(URL);
	HRESULT applydownload = URLDownloadToFileW(
		nullptr,
		LcURL,
		LcDsp,
		0,
		nullptr
	);
	if (_access(Save.c_str(),0)) {
		return true;
	}
	else {
		return false;
	}

}
