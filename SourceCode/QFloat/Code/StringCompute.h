
//Thư viện chưa các hàm tính toán chuỗi kí tự số nguyên


#ifndef _STRING_COMPUTE_H_
#define _STRING_COMPUTE_H_

#include <iostream>
#include <string>
using namespace std;


//------------------------------------------------------
	
	// Hàm đổi kí tự số sang số 
	//		Input là kí tự số
	//		Output là số tương ứng
int Digit(char x);

//-------------------------------------------------------
	
	//Hàm cộng hai chuỗi số thực lớn không âm
	//		Input là 2 string số thực
	//		Output là tổng cùa 2 string
string AdditionString(string A, string B);

//-------------------------------------------------------
	
	//Hàm nhân hai chuỗi số nguyên không âm
	//		Input là 2 string số nguyên không âm
	//		Output là tich cùa 2 string
string MultiplyString(string A, string B);

//-------------------------------------------------------
	
	// Hàm lũy thừa a^n số nguyên không âm với n nguyên không âm.
	//		Input là string số nguyên không âm và số mũ nguyên không âm n
	//		Output là string số nguyên không âm
string PowerString(string a,unsigned int n);

//-------------------------------------------------------

	// Hàm lũy thừa 2^n với n số nguyên.
	//		Input là số mũ nguyên n
	//		Output là string số thực với n âm hoặc string số nguyên nếu n dương
string PowerStringOfTwo(int n);

//-------------------------------------------------------
	
	// Hàm chia chuỗi số thực không âm cho 2 
	//		Inpput là srting a có thể là nguyên hoặc thực, số dư remainder và biến bool isFloat cho biết kết quả cần có là số thực hay số nguyên
	//		Output là string kết quả
string DivisionStringByTwo(string a, bool& remainder, bool isFloat = 0);

//-------------------------------------------------------

#endif // !_STRING_COMPUTE_H_
