#ifndef _DEMO_H_
#define _DEMO_H_
#include <fstream>
#include <iostream>
#include <string>
#include "QFloat.h"
using namespace std;

//-----------------------------------------------------------

	// Hàm quá tải toán tử nhập để tách cách tham số trong file input, các tham số cách nhau khoảng cách
	//		Hàm trả về mảng string với string[0] là số lượng tham số. Tiếp theo lần lượt là các tham số
istream& operator>>(istream& in, string tmp[]);

//------------------------------------------------------------

	//Hàm chuyển đổi số nhị phân kiểu bool* về dạng string
string BinConvertToString(bool* x);

//------------------------------------------------------------

	//Hàm chuyển đổi chuổi nhị phân kiểu string về dạng bool* 
bool* ConvertToBinary(string x);

//------------------------------------------------------------

	//Hàm chuyển đổi hệ cơ số cho chuỗi số. Từ base1 sang base2
string ConvertBases(string _operand, short int base1, short int base2);

//------------------------------------------------------------

	//Hàm đọc dữ liệu từ file in và xuất ra file out
void PROCESS_FROM_FILE(istream& in, ostream& out);

#endif // !_DEMO_H_

