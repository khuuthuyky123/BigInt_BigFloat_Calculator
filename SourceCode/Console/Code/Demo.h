#ifndef _DEMO_H_
#define _DEMO_H_
#include <fstream>
#include <iostream>
#include <string>
#include "QInt.h"
#include "QFloat.h"
using namespace std;

//------------------------------------------------------------

	// Hàm kiểm tra chuỗi nhập vào có nằm trong giới hạn biểu diễn hay không
	//		Input là chuỗi string thập phân cần kiểm tra
	//		Output là biến bool. Trả về 0 nếu số có thể biểu diễn được. Trả về 1 nếu không thể
bool isOverFlowDec(string x);

//------------------------------------------------------------

	//Hàm cộng hai toán hạng ở hệ cơ số base và trả về kết quả cũng ở hệ cơ số base
	//		Input là hai string toán hạng và giá trị của hệ cơ số của toán  hạng
	//		Output là string kết quả ở hệ cơ số tương ứng
string Add(string _operand1, string _operand2, short int base);

//------------------------------------------------------------

	//Hàm trừ hai toán hạng ở hệ cơ số base và trả về kết quả cũng ở hệ cơ số base
	//		Input là hai string toán hạng và giá trị của hệ cơ số của toán  hạng
	//		Output là string kết quả ở hệ cơ số tương ứng
string Subtract(string _operand1, string _operand2, short int base);

//------------------------------------------------------------

	//Hàm nhân hai toán hạng ở hệ cơ số base và trả về kết quả cũng ở hệ cơ số base
	//		Input là hai string toán hạng và giá trị của hệ cơ số của toán  hạng
	//		Output là string kết quả ở hệ cơ số tương ứng
string Multiply(string _operand1, string _operand2, short int base);

//------------------------------------------------------------

	//Hàm chia hai toán hạng ở hệ cơ số base và trả về kết quả cũng ở hệ cơ số base
	//		Input là hai string toán hạng và giá trị của hệ cơ số của toán  hạng
	//		Output là string kết quả ở hệ cơ số tương ứng
string Divide(string _operand1, string _operand2, short int base);

//------------------------------------------------------------

	//Hàm dịch bit của toán hạng sang phải k lần ở hệ cơ số base và trả về kết quả cũng ở hệ cơ số base
	//		Input là string toán hạng, số lần dịch phải và giá trị của hệ cơ số của toán hạng
	//		Output là string kết quả ở hệ cơ số tương ứng
string ShiftRight(string _operand, int k, short int base);

//------------------------------------------------------------

	//Hàm dịch bit của toán hạng sang trái k lần ở hệ cơ số base và trả về kết quả cũng ở hệ cơ số base
	//		Input là string toán hạng, số lần dịch trái và giá trị của hệ cơ số của toán hạng
	//		Output là string kết quả ở hệ cơ số tương ứng
string ShiftLeft(string _operand, int k, short int base);

//------------------------------------------------------------

	//Hàm xoay phải bit của toán hạng k lần ở hệ cơ số base và trả về kết quả cũng ở hệ cơ số base
	//		Input là string toán hạng, số lần xoay phải và giá trị của hệ cơ số của toán hạng
	//		Output là string kết quả ở hệ cơ số tương ứng
string ROR(string _operand, int k, short int base);

//------------------------------------------------------------

	//Hàm xoay trái bit của toán hạng k lần ở hệ cơ số base và trả về kết quả cũng ở hệ cơ số base
	//		Input là string toán hạng, số lần xoay trái và giá trị của hệ cơ số của toán hạng
	//		Output là string kết quả ở hệ cơ số tương ứng
string ROL(string _operand, int k, short int base);

//------------------------------------------------------------

	//Hàm thực hiện AND hai toán hạng ở hệ cơ số base và trả về kết quả cũng ở hệ cơ số base
	//		Input là hai string toán hạng và giá trị của hệ cơ số của toán hạng
	//		Output là string kết quả ở hệ cơ số tương ứng
string AND(string _operand1, string _operand2, short int base);

//------------------------------------------------------------

	//Hàm thực hiện OR hai toán hạng ở hệ cơ số base và trả về kết quả cũng ở hệ cơ số base
	//		Input là hai string toán hạng và giá trị của hệ cơ số của toán hạng
	//		Output là string kết quả ở hệ cơ số tương ứng
string OR(string _operand1, string _operand2, short int base);

//------------------------------------------------------------

	//Hàm thực hiện XOR hai toán hạng ở hệ cơ số base và trả về kết quả cũng ở hệ cơ số base
	//		Input là hai string toán hạng và giá trị của hệ cơ số của toán hạng
	//		Output là string kết quả ở hệ cơ số tương ứng
string XOR(string _operand1, string _operand2, short int base);

//------------------------------------------------------------

	//Hàm thực hiện NOT toán hạng ở hệ cơ số base và trả về kết quả cũng ở hệ cơ số base
	//		Input là string của toán hạng và giá trị của hệ cơ số của toán hạng
	//		Output là string kết quả ở hệ cơ số tương ứng
string NOT(string _operand, short int base);

//------------------------------------------------------------

	//Hàm thực hiện so sánh bằng hai toán hạng ở hệ cơ số base và trả về kết quả là string "true", "false"
	//		Input là hai string toán hạng và giá trị của hệ cơ số của toán hạng
	//		Output là string kết quả "true" hoặc "false".
	//			"true" nếu hai toán hạng bằng nhau. "false" nếu ngược lại
string isEqual(string _operand1, string _operand2, short int base);

//------------------------------------------------------------

	//Hàm thực hiện so sánh bé hơn hai toán hạng ở hệ cơ số base và trả về kết quả là string "true", "false"
	//		Input là hai string toán hạng và giá trị của hệ cơ số của toán hạng
	//		Output là string kết quả "true" hoặc "false".
	//			"true" nếu toán hạng thứ 1 bé hơn toán hạng thứ 2. "false" nếu ngược lại
string isLess(string _operand1, string _operand2, short int base);

//------------------------------------------------------------

	//Hàm thực hiện so sánh lớn hơn hai toán hạng ở hệ cơ số base và trả về kết quả là string "true", "false"
	//		Input là hai string toán hạng và giá trị của hệ cơ số của toán hạng
	//		Output là string kết quả "true" hoặc "false".
	//			"true" nếu toán hạng thứ 1 lớn hơn toán hạng thứ 2. "false" nếu ngược lại
string isGreater(string _operand1, string _operand2, short int base);

//------------------------------------------------------------

	//Hàm thực hiện so sánh bé hơn hoặc bằng hai toán hạng ở hệ cơ số base và trả về kết quả là string "true", "false"
	//		Input là hai string toán hạng và giá trị của hệ cơ số của toán hạng
	//		Output là string kết quả "true" hoặc "false".
	//			"true" nếu toán hạng thứ 1 bé hơn hoặc bằng toán hạng thứ 2. "false" nếu ngược lại
string isLessOrEqual(string _operand1, string _operand2, short int base);

//------------------------------------------------------------

	//Hàm thực hiện so sánh lớn hơn hoặc bằng hai toán hạng ở hệ cơ số base và trả về kết quả là string "true", "false"
	//		Input là hai string toán hạng và giá trị của hệ cơ số của toán hạng
	//		Output là string kết quả "true" hoặc "false".
	//			"true" nếu toán hạng thứ 1 lớn hơn hoặc bằng toán hạng thứ 2. "false" nếu ngược lại
string isGreaterOrEqual(string _operand1, string _operand2, short int base);

//------------------------------------------------------------

	//Hàm chuyển đổi hệ cơ số cho chuỗi số. Từ base1 sang base2
	//		Input là string toán hạng, hệ cơ số gốc base1 và hệ cơ số đích base2, và biến bool cho biết làm việc trên QInt hay QFloat
	//		Output là string kết quả đã được chuyển sang hệ cơ số đích
string ConvertBases(string _operand, short int base1, short int base2, bool isFloat);

#endif // !_DEMO_H_

