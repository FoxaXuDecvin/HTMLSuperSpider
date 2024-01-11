#include"NetworkAPI.h"
#include"LineReader.h"
#include"Include.h"
#include"api_autospider.h"



//FORMAT
//   HSS.exe <savepath> <urlspider>
//  AGRC = 3

using namespace std;

//MAINs
int main(int argc, char* argv[]) {
	int arlng = 1;
	if (argc != 2) {
	    printf("HTML Super Spider .\n");
		printf("FORMAT BY FoxaXu\n");
		printf("         HSS.exe <urlspider>\n");
		printf("Copyright FoxaXu 2024\n");
		cout << endl;
		cout << "Type URL :  >";
		getline(cin, spdurl);
		goto SKIPPARAMTR;
	}

	savepath = ".\\";

	spdurl = argv[arlng];

	SKIPPARAMTR:

	cout << "Save Path on :  " << savepath << endl;
	CreateDirectory(savepath.c_str(), 0);

	cout << "Check Access " << endl;

	if (ExistFolder_check(savepath)) {
		printf("Failed, Directory Access Denied");
		return 0;
	}
	else {
		autospider(spdurl);
	}
	cout << "HTML Super Spider" << endl;
	cout << "Complete Task...   " << endl;
	getline(cin, readbuffer);
	return 0;
}