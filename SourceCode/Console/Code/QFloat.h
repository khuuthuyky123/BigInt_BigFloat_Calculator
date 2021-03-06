
//Thư viện thể hiện CTDL cho số thập phân phẩy động Quadruple-precision theo chuẩn IEEE754. Không minh họa các phép tính.

#ifndef _QFLOAT_H_
#define _QFLOAT_H_

#include <iostream>
#include <string>
#include "StringCompute.h"

using namespace std;

//-----------------------------------------------------------

	//CTDL lưu trữ số chấm động độ chính xác Quadruple-precision với ý tưởng dùng 4 số nguyên 32bits để lưu trữ 128 bits.
	// Trong đó có 1 bit dấu, 15 bit exponent và 112 bit fraction
	//Các bit sẽ được nhập xuất bằng các hàm GetBit và SetBit. 
	//Với cách lưu trữ này có thể lưu trữ số lớn nhất là .............. và số nhỏ nhất là ................
	//Tuy nhiên không thể nâng cấp CTDL do tính phức tạp của các tham số.
struct QFloat
{
	unsigned int data[4];		 // Mảng chứa các phần tử của QInt. 	
};

//-----------------------------------------------------------

	//Các hằng số 

const QFloat __0 = { 0,0,0,0 };			//Hằng số 0
const int bias = pow(2, 15 - 1) - 1;	// Số quá K để đưa exponent về số dương

//------------------------------------------------------------

	// Hàm lấy giá trị bit tại một vị trí bất kì. 
	//		Input là biến QFloat x và vị trí cần lấy giá trị pos
	//		Output là biến bool thể hiện bit tại vị trí cần lấy
bool GetBit(QFloat x, short int pos);

//-----------------------------------------------------------

	// Thủ tục gán giá trị bit tại một vị trí bất kì. 
	//		Input là biến QFloat x, vị trí cần gán pos và giá trị bit muốn gán 
void SetBit(QFloat& x, short int pos, bool bit);

//-----------------------------------------------------------

	//Hàm chuyển chuỗi string thập phân sang chuỗi string nhị phân
	//		Input là chuỗi string thập phân
	//		Output là chuỗi string nhị phân
string strDecToStrBin(string& in);

//-----------------------------------------------------------

	//Hàm đọc QFloat a thành mảng nhị phân kiểu bool
	//		Input là biến QFloat a và tham số kiểu int để phân biệt với hàm cùng tên của CTDL QInt
	//		Output là con trỏ trỏ đến địa chỉ mảng bool được cấp phát trong chương trình
bool* DecToBin(QFloat a, int);

//-----------------------------------------------------------

	//Hàm lưu mảng nhị phân bits thành số kiểu QInt
	//		Input là mảng bool bits và tham số kiểu int để phân biệt với hàm cùng tên của CTDL QInt
	//		Output là biến kiểu dữ liệu QFloat.
QFloat BinToDec(bool* bits, int);

//-----------------------------------------------------------
	// Thủ tục khởi tạo giá trị cho biến QFloat x
	//		Input vào là tham chiếu biến QFloat x và string dec được khởi tạo mặc định là rỗng
void ScanQFloat(QFloat& x, string dec = "");

//-----------------------------------------------------------

	//Hàm trả về giá trị chuỗi thập phân của biến QFloat x
	//		Input là biến QFloat x
	//		Output là string chưa giá trị thập phân của x
string PrintQFloat(QFloat x);


#endif // !_QINT_H_
