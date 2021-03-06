#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#pragma warning(disable : 4996)
#include "Demo.h"

using namespace std;

void test()
{
	///*QInt x,y,z;
	//x="122345667887654322345678765432";
	//y = "546221456787";
	//z = "1";
	//cout << PrintQInt(x/y);*/
	///*char h[4] = "1AF";
	//bool* bin = HexToBin(h);
	//for (int i = 0; i < 128; i++)
	//{
	//	cout << bin[i];
	//}
	//cout << endl;*/
	//QInt x; 
	//bool s[N * NBIT] = { 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,1 ,0 ,1 ,1 ,0 ,1 ,0 ,1 ,1 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,1 ,0 ,1 ,1 ,1 ,0 ,1 ,1 ,0 ,1 ,1 ,1 ,1 ,1 ,0 ,0 ,1 ,0 };
	//x = BinToDec(s);
	////bool s[128];
	////string a;
	////cin >> a;
	////for (int i = 0; i < a.length(); i++)
	////	if (a[i] == '1')
	////		s[i] = 1;
	////	else
	////		s[i] = 0;
	//////ScanQInt(x, s);
	//cout << PrintQInt(x);
	//	QFloat x;
	//ScanQFloat(x);
	//for (int i = 128 - 1; i >= 0; i--)
	//{
	//	cout << GetBit(x, i);
	//}
	//cout << endl;
	//PrintQFloat(x);
	//cout << endl << endl;
//}
}

int main(int argc, char* argv[])
{
	//test();
	//Code này đọc file theo dạng tham số dòng lệnh
	//argc = 3;
	if (argc == 3)
	{
		fstream in,out;
		in.open(argv[1], ios::in);
		//in.open("input.txt", ios::in);
		
		//freopen("output.txt", "w", stdout);
		out.open(argv[2], ios::out);
		PROCESS_FROM_FILE(in,out);
	}
	else
	{
		cout << "Vui long nhap tham so" << endl;
	}
	//fflush(stdout);
	//freopen("CON", "w", stdout);
	

//-----------------------------------------------------------
	//Chờ người dùng kết thúc chương trình
	system("pause");
	return 0;
}