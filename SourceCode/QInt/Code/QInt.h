
		//Thư viện mô tả CTDL lưu trữ số nguyên lớn 128bit và một số phép tính cơ bản

#ifndef _QINT_H_
#define _QINT_H_
#define NBIT 32	// Kích thước bit của một phần tử mảng QInt
#define N 4		// Số phần tử mảng QInt.
#include <iostream>
#include <string>
#include "StringCompute.h"

using namespace std;

//-----------------------------------------------------------
	
	//CTDL lưu trữ số nguyên lớn 128 bits với ý tưởng dùng 4 số nguyên 32bits để lưu trữ 128 bits. 
	//Các bit sẽ được nhập xuất bằng các hàm GetBit và SetBit. 
	//Với cách lưu trữ này có thể lưu trữ số lớn nhất là (2^127)-1 và số nhỏ nhất là -(2^177)
	//Có thể dễ dàng nâng số kích thước dữ liệu bằng cách thay đổi Hằng số N và NBit trên define
struct QInt
{
	unsigned int data[N];				// Mảng chứa các phần tử của QInt. 
	//QInt& operator=(char * dec);		// Hàm quá tải toán tử toán tử gán dùng cho việc gán cho QInt một mảng chuỗi số nguyên kiểu kí tự
	QInt& operator=(const string dec);  // Hàm quá tải toán tử toán tử gán dùng cho việc gán cho QInt một mảng chuỗi số nguyên kiểu string
};

//-----------------------------------------------------------
	
	//Hằng số thường dùng là 0, 1 và giá trị lớn nhất, giá trị nhỏ nhất
const QInt _0 = { 0,0,0,0 };
const QInt _1 = { 1,0,0,0 };
const QInt MAX_QINT = { UINT_MAX, UINT_MAX ,UINT_MAX ,UINT_MAX- pow(2,31)};
const string MAX_QInt_str = "170141183460469231731687303715884105727";
const string MIN_QInt_str = "-170141183460469231731687303715884105728";

//-----------------------------------------------------------

	// Hàm lấy giá trị bit tại một vị trí bất kì. 
	//		Input là biến QInt x và vị trí cần lấy giá trị pos.
	//		Output là biến bool 0 hoặc 1 là giá bị bit tại vị trí cần lấy
bool GetBit(QInt x, short int pos);

//-----------------------------------------------------------

	// Thủ tục gán giá trị bit tại một vị trí bất kì. 
	//		Input là biến QInt x, vị trí cần gán pos và giá trị bit gán bit.
	//				bit = 1 Gán bit bằng phép OR với 1, không quan tâm giá trị cũ.
	//				bit = 0 Lật bit bằng phép XOR với 1, chỉ thực hiện khi giá trị cũ là 1.
void SetBit(QInt& x, short int pos, bool bit);

//-----------------------------------------------------------

	//Hàm chuyển chuỗi kiểu char sang chuỗi kiểu string
	//		Input là con trỏ trỏ đến mảng chuỗi char
	//		Output trả về chuỗi string có cùng dữ liệu
string convertToString(char* a);

//-----------------------------------------------------------

	// Hàm quá tải toán tử nhập để tách cách tham số trong file input, các tham số cách nhau khoảng cách
	//		Hàm trả về mảng string với string[0] là số lượng tham số. Tiếp theo lần lượt là các tham số
istream& operator>>(istream& in, string tmp[]);

//-----------------------------------------------------------

	//Hàm quá tải toán tử AND hai số QInt. 
	//		Input là 2 biến QInt a và b
	//		Output là một biến QInt kết quả
QInt operator & (QInt a, QInt b);

//-----------------------------------------------------------

	//Hàm quá tải toán tử OR hai số QInt.
	//		Input là 2 biến QInt a và b
	//		Output là một biến QInt kết quả
QInt operator | (QInt a, QInt b);

//-----------------------------------------------------------

	//Hàm quá tải toán tử XOR hai số QInt.
	//		Input là 2 biến QInt a và b
	//		Output là một biến QInt kết quả
QInt operator^(QInt a, QInt b);

//-----------------------------------------------------------

	//Hàm quá tải toán tử NOT số QInt.
	//		Input là 2 biến QInt a
	//		Output là một biến QInt kết quả
QInt operator~(QInt a);

//-----------------------------------------------------------

	//Hàm quá tải toán tử dịch trái số QInt k lần
	//		Input là 2 biến QInt a và số lần k
	//		Output là một biến QInt kết quả
QInt operator << (QInt a, int k);

//-----------------------------------------------------------

	//Hàm quá tải toán tử dịch phải số QInt k lần
	//		Input là 2 biến QInt a và số lần k
	//		Output là một biến QInt kết quả
QInt operator >> (QInt a, int k);

//-----------------------------------------------------------

	//Hàm quá tải toán tử cộng hai số QInt
	//		Input là 2 biến QInt a và b
	//		Output là một biến QInt kết quả
QInt operator+(QInt A, QInt B);

//-----------------------------------------------------------

	//Hàm quá tải toán tử trừ hai số QInt.
	//		Input là 2 biến QInt a và b
	//		Output là một biến QInt kết quả
QInt operator-(QInt A, QInt B);

//-----------------------------------------------------------

	//Hàm quá tải toán tử nhân hai số QInt.
	//		Input là 2 biến QInt a và b
	//		Output là một biến QInt kết quả
QInt operator*(QInt A, QInt B);

//-----------------------------------------------------------

	//Hàm quá tải toán tử chia hai số QInt.
	//		Input là 2 biến QInt a và b
	//		Output là một biến QInt kết quả
QInt operator/(QInt A, QInt B);

//-----------------------------------------------------------

	//Hàm quá tải toán tử só sánh lớn hơn
	//		Input là 2 biến QInt a và b
	//		Output là một biến bool kết quả
	//			Nếu A > B trả về true và ngược lại
bool operator>(QInt A, QInt B);

//-----------------------------------------------------------

	//Hàm quá tải toán tử só sánh nhỏ hơn.
	//		Input là 2 biến QInt a và b
	//		Output là một biến bool kết quả
	//			Nếu A < B trả về true và ngược lại
bool operator<(QInt A, QInt B);

//-----------------------------------------------------------

	//Hàm quá tải toán tử só sánh lớn hơn hoặc bằng.
	//		Input là 2 biến QInt a và b
	//		Output là một biến bool kết quả
	//			Nếu A >= B trả về true và ngược lại
bool operator>=(QInt A, QInt B);

//-----------------------------------------------------------

	//Hàm quá tải toán tử só sánh nhỏ hơn hoặc bằng hai.
	//		Input là 2 biến QInt a và b
	//		Output là một biến bool kết quả
	//			Nếu A <= B trả về true và ngược lại
bool operator<=(QInt A, QInt B);

//-----------------------------------------------------------

	//Hàm quá tải toán tử só sánh bằng hai số.
	//		Input là 2 biến QInt a và b
	//		Output là một biến bool kết quả
	//			Nếu A = B trả về true và ngược lại
bool operator==(QInt A, QInt B);

//-----------------------------------------------------------

	// Hàm quá tải toán tử  so sánh 2 số.
	//		Input là 2 biến QInt a và b
	//		Output là một biến bool kết quả
	//			Nếu A!=B trả về true và ngược lại
bool operator != (QInt A, QInt B);

//-----------------------------------------------------------

	//Hàm thực hiện phép xoay trái bit
	//		Input là biến QInt a
	//		Output là một biến QInt kết quả
QInt RoL(QInt a);

//-----------------------------------------------------------

	//Hàm thực hiện phép xoay phải bit
	//		Input là biến QInt a
	//		Output là một biến QInt kết quả
QInt RoR(QInt a);

//-----------------------------------------------------------

	//Hàm nhập dữ liệu cho số QInt a. Có thể nhập vào mảng nhị phân hoặc hoặc mảng chuỗi số nguyên hoặc nhập từ bàn phím.
	//		Nếu gọi hàm ScanQInt(x) sẽ nhập từ bàn phím.
	//		Nếu gọi hàm ScanQInt(x, bits) sẽ nhập từ mảng nhị phân. với bits là mảng bool.
	//		Nếu gọi hàm ScanQInt(x, dec) sẽ nhập từ mảng chuỗi. với dec là string số nguyên.
void ScanQInt(QInt& x, bool* bits);

//-----------------------------------------------------------

	//Hàm nhập dữ liệu cho số QInt a. Có thể nhập vào mảng nhị phân hoặc hoặc mảng chuỗi số nguyên hoặc nhập từ bàn phím.
	//		Nếu gọi hàm ScanQInt(x) sẽ nhập từ bàn phím.
	//		Nếu gọi hàm ScanQInt(x, bits) sẽ nhập từ mảng nhị phân. với bits là mảng bool.
	//		Nếu gọi hàm ScanQInt(x, dec) sẽ nhập từ mảng chuỗi. với dec là string số nguyên.
void ScanQInt(QInt& x, string dec = " ");

//-----------------------------------------------------------

	//Thủ tục xuất giá trị nhị phân của QInt a.
	//		Input là biến QInt 
void PrintBinaQInt(QInt x);

//-----------------------------------------------------------

	//Thủ tục chuyển X thành số đối của nó trong cách biểu diễn bù 2. 
	//		Input là tham chiếu biến QInt x
	//			Thực hiện bằng cách đảo tất cả các bit và cộng 1
void OppositeTranform(QInt& x);

//-----------------------------------------------------------

	//Hàm kiểm tra xem QInt x có phải số âm không. 
	//		Trả về true nếu x<0. Và false nếu x>=0
bool isNegative(QInt x);

//-----------------------------------------------------------

	//Hàm xuất giá trị thập phân của QInt a
	//		Thực hiện bằng cách áp dụng công thức hệ cơ số q tổng quát. 
	//				VD: 1101 = 1*(2^3) + 1*(2^2) + 0*(2^1) + 1*(2^0)
	//		Nhưng thay vì đọc từng bit, ta sử dụng giá trị của từng phần tử của mảng data trong kiểu QInt. 
	//				vì giá trị data[i] đã là tổng của 32 bit trong chính nó. Ta chỉ việc nhân thêm một lượng 2^(32*i) là vị trí của nó
string PrintQInt(QInt x);

//-----------------------------------------------------------

	//Hàm chuyển đổi QInt thành mảng nhị phân
	//		Input là biến QInt a
	//		Output là con trỏ trỏ đến mảng bool được cấp phát động lưu giá trị nhị phân được chuyển
bool* DecToBin(QInt a);

//-----------------------------------------------------------

	//Hàm lưu mảng nhị phân thành số kiểu QInt
	//		Input là con trỏ trỏ đến mảng nhị phân kiểu bool
	//		Output là biến QInt
QInt BinToDec(bool* bits);

//-----------------------------------------------------------

	//Hàm chuyển đổi QInt a thành mảng thập lục phân kiểu char
	//		Input là biến QInt a
	//		Output là con trỏ trỏ đến mảng char được cấp phát động lưu giá trị thập lục phân được chuyển
char* DecToHex(QInt A);

//-----------------------------------------------------------

	//Hàm chuyển đổi mảng thập lục phân thành mảng nhị phân
	//		Input là con trỏ trỏ đến mảng thập lục phân kiểu char
	//		Output là con trỏ trỏ đến mảng char được cấp phát động lưu giá trị thập lục phân được chuyển
bool* HexToBin(char* A);

//-----------------------------------------------------------
	
	//Hàm chuyển đổi mảng nhị phân thành mảng thập lục phân
	//		Input là con trỏ trỏ đến mảng nhị phân kiểu bool
	//		Output là con trỏ trỏ đến mảng char được cấp phát động lưu giá trị thập lục phân được chuyển
char* BinToHex(bool* bit);

//-----------------------------------------------------------

	//Hàm chuyển đổi số nhị phân kiểu bool* về dạng string
	//		Input là địa chỉ trỏ đến mảng bool 128 phần tử.
	//		Output là string có các phần tử bị đảo ngược thứ tự so với mảng ban đầu  
string BinConvertToString(bool* x);

//------------------------------------------------------------
	
	//Hàm chuyển đổi chuổi nhị phân kiểu string về dạng bool* 
	//	Input là string có dạng 01
	//	Output là con trỏ trỏ đến mảng bool 128 phần tử được cấp phát động. Tự động thêm 0 vào cho đủ dữ liệu 128bit
	//		Các phần tử trong mảng bool bị đảo ngược lại so với thứ tự trong string. phần tử cuối của string là thành phần tử đầu của bool
bool* ConvertToBinary(string x);

//------------------------------------------------------------
	
	//Hàm chuyển đổi chuổi thập lục phân kiểu string về dạng char* 
	//	Input là string có dạng hex
	//	Output là con trỏ trỏ đến mảng char 32 phần tử được cấp phát động.
	//		Các phần tử theo đúng thứ tự như trong string
char* StringHexConvertToChar(string x);

//------------------------------------------------------------

	//Hàm chuyển đổi số thập phân kiểu QInt về chuỗi String
	//		Input vào là biến QInt và trả về string chứa giá trị thập phân. Hàm tương tự như PrintQInt
string DecConvertToString(QInt x);

//------------------------------------------------------------

#endif // !_QINT_H_

