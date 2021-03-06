#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#pragma warning(disable : 4996)
#include "Demo.h"

using namespace std;


int main(int argc, char* argv[])
{
	
	if (argc == 3)
	{
		fstream in,out;
		in.open(argv[1], ios::in);
		out.open(argv[2], ios::out);
		PROCESS_FROM_FILE(in,out);
	}
	else
	{
		cout << "Vui long nhap tham so" << endl;
	}
	

//-----------------------------------------------------------
	//Chờ người dùng kết thúc chương trình
	system("pause");
	return 0;
}