#include "Demo.h"

//------------------------------------------------------------

	// Hàm kiểm tra chuỗi nhập vào có nằm trong giới hạn biểu diễn hay không
	//		Input là chuỗi string thập phân cần kiểm tra
	//		Output là biến bool. Trả về 0 nếu số có thể biểu diễn được. Trả về 1 nếu không thể
bool isOverFlowDec(string x)
{
	if (x[0] != '-')
	{
		if (x.length() > MAX_QInt_str.length())
			return true;
		if (x.length() < MAX_QInt_str.length())
			return false;
		if (x > MAX_QInt_str)
			return true;
	}
	if (x[0] == '-')
	{
		if (x.length() > MIN_QInt_str.length())
			return true;
		if (x.length() < MIN_QInt_str.length())
			return false;
		if (x > MIN_QInt_str)
			return true;
	}
	return false;
}

//------------------------------------------------------------

	//Hàm cộng hai toán hạng ở hệ cơ số base và trả về kết quả cũng ở hệ cơ số base
	//		Input là hai string toán hạng và giá trị của hệ cơ số của toán  hạng
	//		Output là string kết quả ở hệ cơ số tương ứng
string Add(string _operand1, string _operand2, short int base)
{
	if (base == 10 && (isOverFlowDec(_operand1) || isOverFlowDec(_operand2)))
	{
		return "Invalid Input ";
	}
	QInt operand1 = _0, operand2= _0;
	char* hex1, *hex2, *hex;
	bool* bin1, * bin2, * bin;
	string res = "";

	QInt tmp;
	if (base == 2)
	{
		bin1 = ConvertToBinary(_operand1);
		bin2 = ConvertToBinary(_operand2);
		for (int i = 0; i < 128; i++)
		{
			SetBit(operand1, i, bin1[i]);
			SetBit(operand2, i, bin2[i]);
		}
		delete[] bin1; delete[] bin2;
		bin = new bool[128];
		tmp = operand1 + operand2;
		for (int i = 0; i < 128; i++)
			bin[i] = GetBit(tmp, i);
		res = BinConvertToString(bin);
		delete[] bin;
	}
	if (base == 10)
	{
		ScanQInt(operand1, _operand1);
		ScanQInt(operand2, _operand2);
		tmp = operand1 + operand2;
		res = PrintQInt(tmp);
	}
	if (base == 16)
	{
		hex1 = StringHexConvertToChar(_operand1);
		hex2 = StringHexConvertToChar(_operand2);
		bin1 = HexToBin(hex1);
		bin2 = HexToBin(hex2);
		delete[]hex1, delete[] hex2;
		for (unsigned int i = 0; i < _operand1.length() * 4; i++)
			SetBit(operand1, i, bin1[_operand1.length() * 4 - 1 - i]);
		for (unsigned int i = _operand1.length() * 4; i < 128; i++)
			SetBit(operand1, i, false);

		for (unsigned int i = 0; i < _operand2.length() * 4; i++)
			SetBit(operand2, i, bin2[_operand2.length() * 4 - 1 - i]);
		for (unsigned int i = _operand2.length() * 4; i < 128; i++)
			SetBit(operand2, i, false);
		delete[]bin1, delete[] bin2;
		tmp = operand1 + operand2;

		hex = DecToHex(tmp);

		res = convertToString(hex);
		delete[] hex;
	}
	while (res[0] == '0' && res.length() > 1)
		res.erase(0, 1);
	return res;
}

//------------------------------------------------------------

	//Hàm trừ hai toán hạng ở hệ cơ số base và trả về kết quả cũng ở hệ cơ số base
	//		Input là hai string toán hạng và giá trị của hệ cơ số của toán  hạng
	//		Output là string kết quả ở hệ cơ số tương ứng
string Subtract(string _operand1, string _operand2, short int base)
{
	if (base == 10 && (isOverFlowDec(_operand1) || isOverFlowDec(_operand2)))
	{
		return "Invalid Input ";
	}
	QInt operand1 = _0, operand2 = _0;
	char* hex1, * hex2, * hex;
	bool* bin1, * bin2, * bin;
	string res = "";

	QInt tmp;
	if (base == 2)
	{
		bin1 = ConvertToBinary(_operand1);
		bin2 = ConvertToBinary(_operand2);
		for (int i = 0; i < 128; i++)
		{
			SetBit(operand1, i, bin1[i]);
			SetBit(operand2, i, bin2[i]);
		}
		delete[] bin1; delete[] bin2;
		bin = new bool[128];
		tmp = operand1 - operand2;
		for (int i = 0; i < 128; i++)
			bin[i] = GetBit(tmp, i);
		res = BinConvertToString(bin);
		delete[] bin;
	}
	if (base == 10)
	{
		ScanQInt(operand1, _operand1);
		ScanQInt(operand2, _operand2);
		tmp = operand1 - operand2;
		res = PrintQInt(tmp);
	}
	if (base == 16)
	{
		hex1 = StringHexConvertToChar(_operand1);
		hex2 = StringHexConvertToChar(_operand2);
		bin1 = HexToBin(hex1);
		bin2 = HexToBin(hex2);
		delete[]hex1, delete[] hex2;
		for (int i = 0; i < _operand1.length() * 4; i++)
			SetBit(operand1, i, bin1[_operand1.length() * 4 - 1 - i]);
		for (int i = _operand1.length() * 4; i < 128; i++)
			SetBit(operand1, i, false);
		
		for (int i = 0; i < _operand2.length() * 4; i++)
			SetBit(operand2, i, bin2[_operand2.length() * 4 - 1 - i]);
		for (int i = _operand2.length() * 4; i < 128; i++)
			SetBit(operand2, i, false);
		delete[] bin1, delete[] bin2;
		tmp = operand1 - operand2;
		hex = DecToHex(tmp);
		res = convertToString(hex);
		delete[] hex;
	}
	while (res[0] == '0' && res.length() > 1)
		res.erase(0, 1);
	return res;
}

//------------------------------------------------------------

	//Hàm nhân hai toán hạng ở hệ cơ số base và trả về kết quả cũng ở hệ cơ số base
	//		Input là hai string toán hạng và giá trị của hệ cơ số của toán  hạng
	//		Output là string kết quả ở hệ cơ số tương ứng
string Multiply(string _operand1, string _operand2, short int base)
{
	if (base == 10 && (isOverFlowDec(_operand1) || isOverFlowDec(_operand2)))
	{
		return "Invalid Input ";
	}
	QInt operand1=_0, operand2=_0;
	char* hex1, * hex2, * hex;
	bool* bin1, * bin2, * bin;
	string res = "";

	QInt tmp;
	if (base == 2)
	{
		bin1 = ConvertToBinary(_operand1);
		bin2 = ConvertToBinary(_operand2);
		for (int i = 0; i < 128; i++)
		{
			SetBit(operand1, i, bin1[i]);
			SetBit(operand2, i, bin2[i]);
		}
		delete[] bin1; delete[] bin2;
		bin = new bool[128];
		tmp = operand1 * operand2;
		for (int i = 0; i < 128; i++)
			bin[i] = GetBit(tmp, i);
		res = BinConvertToString(bin);
		delete[] bin;
	}
	if (base == 10)
	{
		ScanQInt(operand1, _operand1);
		ScanQInt(operand2, _operand2);
		tmp = operand1 * operand2;
		res = PrintQInt(tmp);
	}
	if (base == 16)
	{
		hex1 = StringHexConvertToChar(_operand1);
		hex2 = StringHexConvertToChar(_operand2);
		bin1 = HexToBin(hex1);
		bin2 = HexToBin(hex2);
		for (int i = 0; i < _operand1.length() * 4; i++)
			SetBit(operand1, i, bin1[_operand1.length() * 4 - 1 - i]);
		for (int i = _operand1.length() * 4; i < 128; i++)
			SetBit(operand1, i, false);

		for (int i = 0; i < _operand2.length() * 4; i++)
			SetBit(operand2, i, bin2[_operand2.length() * 4 - 1 - i]);
		for (int i = _operand2.length() * 4; i < 128; i++)
			SetBit(operand2, i, false);
		tmp = operand1 * operand2;

		hex = DecToHex(tmp);

		res = convertToString(hex);
		delete[] bin1, delete[] bin2, delete[] hex1, delete[] hex2, delete[]hex;
	}
	while (res[0] == '0' && res.length() > 1)
		res.erase(0, 1);
	return res;
}

//------------------------------------------------------------

	//Hàm chia hai toán hạng ở hệ cơ số base và trả về kết quả cũng ở hệ cơ số base
	//		Input là hai string toán hạng và giá trị của hệ cơ số của toán  hạng
	//		Output là string kết quả ở hệ cơ số tương ứng
string Divide(string _operand1, string _operand2, short int base)
{
	if (base == 10 && (isOverFlowDec(_operand1) || isOverFlowDec(_operand2)))
	{
		return "Invalid Input ";
	}
	if (_operand2 == "0")
		return "##DIV/0";
	QInt operand1=_0, operand2=_0;
	char* hex1, * hex2, * hex;
	bool* bin1, * bin2, * bin;
	string res = "";

	QInt tmp;
	if (base == 2)
	{
		bin1 = ConvertToBinary(_operand1);
		bin2 = ConvertToBinary(_operand2);
		for (int i = 0; i < 128; i++)
		{
			SetBit(operand1, i, bin1[i]);
			SetBit(operand2, i, bin2[i]);
		}
		
		tmp = operand1 / operand2;
		bin = new bool[128];
		for (int i = 0; i < 128; i++)
			bin[i] = GetBit(tmp, i);
		res = BinConvertToString(bin);
		delete[] bin1, delete[] bin2, delete[]bin;
	}
	if (base == 10)
	{
		ScanQInt(operand1, _operand1);
		ScanQInt(operand2, _operand2);
		tmp = operand1 / operand2;
		res = PrintQInt(tmp);
	}
	if (base == 16)
	{
		hex1 = StringHexConvertToChar(_operand1);
		hex2 = StringHexConvertToChar(_operand2);
		bin1 = HexToBin(hex1);
		bin2 = HexToBin(hex2);
		delete[]hex1, delete[] hex2;
		for (int i = 0; i < _operand1.length() * 4; i++)
			SetBit(operand1, i, bin1[_operand1.length() * 4 - 1 - i]);
		for (int i = _operand1.length() * 4; i < 128; i++)
			SetBit(operand1, i, false);

		for (int i = 0; i < _operand2.length() * 4; i++)
			SetBit(operand2, i, bin2[_operand2.length() * 4 - 1 - i]);
		for (int i = _operand2.length() * 4; i < 128; i++)
			SetBit(operand2, i, false);
		delete[] bin1, delete[] bin2;
		tmp = operand1 / operand2;
	
		hex = DecToHex(tmp);

		res = convertToString(hex);
		delete[] hex;
	}
	while (res[0] == '0' && res.length() > 1)
		res.erase(0, 1);
	return res;
}

//------------------------------------------------------------

	//Hàm dịch bit của toán hạng sang phải k lần ở hệ cơ số base và trả về kết quả cũng ở hệ cơ số base
	//		Input là string toán hạng, số lần dịch phải và giá trị của hệ cơ số của toán hạng
	//		Output là string kết quả ở hệ cơ số tương ứng
string ShiftRight(string _operand, int k, short int base)
{
	if (base == 10 && (isOverFlowDec(_operand)))
	{
		return "Invalid Input ";
	}
	QInt operand1 = _0;
	char* hex;
	bool* bin;
	string res = "";

	QInt tmp;
	if (base == 2)//Nhập là bin
	{
		bin = ConvertToBinary(_operand);//Chuyển string bin thành bool bin
		for (int i = 0; i < 128; i++)//Gán bin vào QInt
			SetBit(operand1, i, bin[i]);
		tmp = operand1 >> k;//Dịch bit
		for (int i = 0; i < 128; i++)
			bin[i] = GetBit(tmp, i);
		res = BinConvertToString(bin);//Chuyển bool bin thành string bin
		delete[]bin;
	}
	if (base == 10)//Nhập là dec
	{
		ScanQInt(operand1, _operand);//Nhập string vào QInt
		tmp = operand1 >> k;
		res = PrintQInt(tmp);//Chuyển về string 
	}
	if (base == 16)//Nhập là hex
	{
		hex = StringHexConvertToChar(_operand);
		bin = HexToBin(hex);//Chuyển string sang bool
		delete[] hex;
		for (int i = 0; i < _operand.length() * 4; i++)
			SetBit(operand1, i, bin[_operand.length() * 4 - 1 - i]);
		for (int i = _operand.length() * 4; i < 128; i++)
			SetBit(operand1, i, false);
		tmp = operand1 >> k;
		hex = DecToHex(tmp);
		res = convertToString(hex); //Chuyển về string
		delete[] bin, delete[] hex;
	}
	while (res[0] == '0' && res.length() > 1)
		res.erase(0, 1);
	return res;
}

//------------------------------------------------------------

	//Hàm dịch bit của toán hạng sang trái k lần ở hệ cơ số base và trả về kết quả cũng ở hệ cơ số base
	//		Input là string toán hạng, số lần dịch trái và giá trị của hệ cơ số của toán hạng
	//		Output là string kết quả ở hệ cơ số tương ứng
string ShiftLeft(string _operand, int k, short int base)
{
	if (base == 10 && (isOverFlowDec(_operand)))
	{
		return "Invalid Input ";
	}
	QInt operand =_0;//biến khi lưu trữ kiểu QInt
	char* hex;//biến khi lưu trữ kiểu hexa
	bool* bin;//biến khi lưu trữ kiểu binary
	string res = "";//kết quả đầu ra

	QInt tmp;//kết quả dạng QInt
	if (base == 2)
	{
		//chuyển đổi string sang bool*
		bin = ConvertToBinary(_operand);
		//Thực hiện tính toán
		for (int i = 0; i < 128; i++)
			SetBit(operand, i, bin[i]);
		
		tmp = operand << k;
		for (int i = 0; i < 128; i++)
			bin[i] = GetBit(tmp, i);
		//chuyển về string kết quả
		res = BinConvertToString(bin);
		delete[] bin;
	}
	else if (base == 10)
	{
		//chuyển đổi string sang QInt
		operand = _operand;
		//Tính toán
		tmp = operand << k;
		//chuyển về string kết quả
		res =DecConvertToString(tmp);
	}
	else if (base == 16)
	{
		hex = StringHexConvertToChar(_operand);
		//chuyển đổi string hexa sang bool* binary
		bin = HexToBin(hex);
		delete[] hex;
		//Tính toán
		for (int i = 0; i < _operand.length() * 4; i++)
			SetBit(operand, i, bin[_operand.length() * 4 - 1 - i]);
		for (int i = _operand.length() * 4; i < 128; i++)
			SetBit(operand, i, false);
		tmp = operand << k;
		hex = DecToHex(tmp);
		//chuyển về string kết quả
		res = convertToString(hex);
		delete[]bin; delete[]hex;
	}
	else
		return "Nhap sai he so";
	while (res[0] == '0' && res.length() > 1)
		res.erase(0, 1);
	return res;
}

//------------------------------------------------------------

	//Hàm xoay phải bit của toán hạng k lần ở hệ cơ số base và trả về kết quả cũng ở hệ cơ số base
	//		Input là string toán hạng, số lần xoay phải và giá trị của hệ cơ số của toán hạng
	//		Output là string kết quả ở hệ cơ số tương ứng
string ROR(string _operand, int k, short int base)
{
	if (base == 10 && (isOverFlowDec(_operand)))
	{
		return "Invalid Input ";
	}
	QInt A = _0;
	string result = "";
	if (base == 10)
	{
		A = _operand;
		for (int i = 0; i < k; i++)
			A = RoR(A);
		result = PrintQInt(A);
	}
	if (base == 2)
	{
		bool* temp = ConvertToBinary(_operand);
		for (int i = 0; i < 128; i++)
			SetBit(A, i, temp[i]);
		delete[] temp;
		for (int i = 0; i < k; i++)
			A = RoR(A);
		temp = DecToBin(A);
		string t = BinConvertToString(temp);
		reverse(t.begin(), t.end());
		delete[]temp;
		result = t;
	}
	if (base == 16)
	{
		char* temp1 = StringHexConvertToChar(_operand);
		bool* temp2 = HexToBin(temp1);
		for (unsigned int i = 0; i < _operand.length() * 4; i++)
			SetBit(A, i, temp2[_operand.length() * 4 - 1 - i]);
		delete[]temp1;delete[]temp2;
		for (int i = 0; i < k; i++)
			A = RoR(A);
		temp1 = DecToHex(A);
		string t = convertToString(temp1);
		delete[]temp1;
		result = t;
	}
	while (result[0] == '0' && result.length() > 1)
		result.erase(0, 1);
	return result;
}

//------------------------------------------------------------

	//Hàm xoay trái bit của toán hạng k lần ở hệ cơ số base và trả về kết quả cũng ở hệ cơ số base
	//		Input là string toán hạng, số lần xoay trái và giá trị của hệ cơ số của toán hạng
	//		Output là string kết quả ở hệ cơ số tương ứng
string ROL(string _operand, int k, short int base)
{
	if (base == 10 && (isOverFlowDec(_operand)))
	{
		return "Invalid Input ";
	}
	QInt A = _0;
	string result = "";
	if (base == 10)
	{
		A = _operand;
		for (int i = 0; i < k; i++)
			A = RoL(A);
		result = PrintQInt(A);
	}
	if (base == 2)
	{
		bool* temp = ConvertToBinary(_operand);
		for (int i = 0; i < 128; i++)
			SetBit(A, i, temp[i]);
		delete[] temp;
		for (int i = 0; i < k; i++)
			A = RoL(A);
		temp = DecToBin(A);
		string t = BinConvertToString(temp);
		reverse(t.begin(), t.end());
		delete[]temp;
		result = t;
	}
	if (base == 16)
	{
		char* temp1 = StringHexConvertToChar(_operand);
		bool* temp2 = HexToBin(temp1);
		for (unsigned int i = 0; i < _operand.length() * 4; i++)
			SetBit(A, i, temp2[_operand.length() * 4 - 1 - i]);
		delete[]temp1; 	delete[]temp2;
		for (int i = 0; i < k; i++)
			A = RoL(A);
		temp1 = DecToHex(A);
		string t = convertToString(temp1);
		delete[]temp1;
		result = t;
	}
	while (result[0] == '0' && result.length() > 1)
		result.erase(0, 1);
	return result;
}

//------------------------------------------------------------

	//Hàm thực hiện AND hai toán hạng ở hệ cơ số base và trả về kết quả cũng ở hệ cơ số base
	//		Input là hai string toán hạng và giá trị của hệ cơ số của toán hạng
	//		Output là string kết quả ở hệ cơ số tương ứng
string AND(string _operand1, string _operand2, short int base)
{
	if (base == 10 && (isOverFlowDec(_operand1) || isOverFlowDec(_operand2)))
	{
		return "Invalid Input ";
	}
	QInt operand1=_0, operand2=_0;//biến khi lưu trữ kiểu QInt của _operand1,_operand2
	char* hex, *hex1, *hex2;//biến khi lưu trữ hex
	bool* bin1;//biến khi lưu trữ kiểu bool* của _operand1
	bool* bin2;//biến khi lưu trữ kiểu bool* của _operand2
	bool* bin = new bool[128];//Biến lưu trữ bool* kết quả
	string res = "";//kết quả
	QInt tmp;//kết quả dạng Qint
	if (base == 2)
	{
		//chuyển đổi string sang bool*
		bin1 = ConvertToBinary(_operand1);
		bin2 = ConvertToBinary(_operand2);
		//Thực hiện tính toán
		for (int i = 0; i < 128; i++)
		{
			SetBit(operand1, i, bin1[i]);
			SetBit(operand2, i, bin2[i]);
		}
		tmp = operand1 & operand2;
		for (int i = 0; i < 128; i++)
			bin[i] = GetBit(tmp, i);
		//kết quả
		res = BinConvertToString(bin);

		delete[] bin1, delete[] bin2, delete[]bin;
	}
	else if (base == 10)
	{
		//chuyển đổi string sang QInt
		operand1 = _operand1;
		operand2 = _operand2;
		//Thực hiện tính toán
		tmp = operand1 & operand2;
		//kết quả
		res = DecConvertToString(tmp);
	}
	else if (base == 16)
	{
		//chuyển đổi string hexa sang bool* binary
		hex1 = StringHexConvertToChar(_operand1);
		hex2 = StringHexConvertToChar(_operand2);
		bin1 = HexToBin(hex1);
		bin2 = HexToBin(hex2);
		//Thực hiện tính toán
		for (int i = 0; i < _operand1.length() * 4; i++)
			SetBit(operand1, i, bin1[_operand1.length() * 4 - 1 - i]);
		for (int i = _operand1.length() * 4; i < 128; i++)
			SetBit(operand1, i, false);

		for (int i = 0; i < _operand2.length() * 4; i++)
			SetBit(operand2, i, bin2[_operand2.length() * 4 - 1 - i]);
		for (int i = _operand2.length() * 4; i < 128; i++)
			SetBit(operand2, i, false);
		tmp = operand1 & operand2;
		hex = DecToHex(tmp);
		//kết quả
		res = convertToString(hex);
		delete[] bin1, delete[] bin2, delete[] hex1, delete[] hex2, delete[]hex;
	}
	else
		return "Nhap sai he so";
	while (res[0] == '0' && res.length() > 1)
		res.erase(0, 1);
	return res;
}

//------------------------------------------------------------

	//Hàm thực hiện OR hai toán hạng ở hệ cơ số base và trả về kết quả cũng ở hệ cơ số base
	//		Input là hai string toán hạng và giá trị của hệ cơ số của toán hạng
	//		Output là string kết quả ở hệ cơ số tương ứng
string OR(string _operand1, string _operand2, short int base)
{
	if (base == 10 && (isOverFlowDec(_operand1) || isOverFlowDec(_operand2)))
	{
		return "Invalid Input ";
	}
	QInt operand1=_0, operand2=_0;//biến khi lưu trữ kiểu QInt của _operand1,_operand2
	char* hex, *hex1, *hex2;//biến khi lưu trữ hex
	bool* bin1;//biến khi lưu trữ kiểu bool* của _operand1
	bool* bin2;//biến khi lưu trữ kiểu bool* của _operand2
	bool* bin;//Biến lưu trữ bool* kết quả
	string res = "";//kết quả
	QInt tmp;//kết quả dạng Qint
	if (base == 2)
	{
		//chuyển string sang bool*
		bin1 = ConvertToBinary(_operand1);
		bin2 = ConvertToBinary(_operand2);
		//Tính toán
		for (int i = 0; i < 128; i++)
		{
			SetBit(operand1, i, bin1[i]);
			SetBit(operand2, i, bin2[i]);
		}
		tmp = operand1 | operand2;
		bin = new bool[128];
		for (int i = 0; i < 128; i++)
			bin[i] = GetBit(tmp, i);
		//kết quả
		res = BinConvertToString(bin);
		delete[] bin1, delete[] bin2, delete[]bin;
	}
	else if (base == 10)
	{
		//chuyển string sang Qint
		operand1 = _operand1;
		operand2 = _operand2;
		//tính toán
		tmp = operand1 | operand2;
		//kết quả
		res = DecConvertToString(tmp);
	}
	else if (base == 16)
	{
		//chuyển thành bin
		hex1 = StringHexConvertToChar(_operand1);
		hex2 = StringHexConvertToChar(_operand2);
		bin1 = HexToBin(hex1);
		bin2 = HexToBin(hex2);
		//tính toán
		for (int i = 0; i < _operand1.length() * 4; i++)
			SetBit(operand1, i, bin1[_operand1.length() * 4 - 1 - i]);
		for (int i = _operand1.length() * 4; i < 128; i++)
			SetBit(operand1, i, false);

		for (int i = 0; i < _operand2.length() * 4; i++)
			SetBit(operand2, i, bin2[_operand2.length() * 4 - 1 - i]);
		for (int i = _operand2.length() * 4; i < 128; i++)
			SetBit(operand2, i, false);

		tmp = operand1 | operand2;
		hex = DecToHex(tmp);
		//kết quả
		res = convertToString(hex);
		delete[] bin1, delete[] bin2, delete[] hex1, delete[] hex2, delete[]hex;
	}
	else
		return "Nhap sai he so";
	while (res[0] == '0' && res.length() > 1)
		res.erase(0, 1);
	return res;
}

//------------------------------------------------------------

	//Hàm thực hiện XOR hai toán hạng ở hệ cơ số base và trả về kết quả cũng ở hệ cơ số base
	//		Input là hai string toán hạng và giá trị của hệ cơ số của toán hạng
	//		Output là string kết quả ở hệ cơ số tương ứng
string XOR(string _operand1, string _operand2, short int base)
{
	if (base == 10 && (isOverFlowDec(_operand1) || isOverFlowDec(_operand2)))
	{
		return "Invalid Input ";
	}
	QInt operand1=_0, operand2=_0;//biến khi lưu trữ kiểu QInt của _operand1,_operand2
	char* hex, *hex1,*hex2;//biến khi lưu trữ hex
	bool* bin1;//biến khi lưu trữ kiểu bool* của _operand1
	bool* bin2;//biến khi lưu trữ kiểu bool* của _operand2
	bool* bin;//Biến lưu trữ bool* kết quả
	string res = "";//kết quả
	QInt tmp;//kết quả dạng Qint

	if (base == 2)
	{
		bin1 = ConvertToBinary(_operand1);
		bin2 = ConvertToBinary(_operand2);
		for (int i = 0; i < 128; i++)
		{
			SetBit(operand1, i, bin1[i]);
			SetBit(operand2, i, bin2[i]);
		}
		tmp = operand1 ^ operand2;
		bin = new bool[128];
		for (int i = 0; i < 128; i++)
			bin[i] = GetBit(tmp, i);
		res = BinConvertToString(bin);
		delete[] bin1, delete[] bin2, delete[]bin;
	}
	else if (base == 10)
	{
		operand1 = _operand1;
		operand2 = _operand2;
		tmp = operand1 ^ operand2;
		res = DecConvertToString(tmp);
	}
	else if (base == 16)
	{
		hex1 = StringHexConvertToChar(_operand1);
		hex2 = StringHexConvertToChar(_operand2);
		bin1 = HexToBin(hex1);
		bin2 = HexToBin(hex2);
		for (int i = 0; i < _operand1.length() * 4; i++)
			SetBit(operand1, i, bin1[_operand1.length() * 4 - 1 - i]);
		for (int i = _operand1.length() * 4; i < 128; i++)
			SetBit(operand1, i, false);

		for (int i = 0; i < _operand2.length() * 4; i++)
			SetBit(operand2, i, bin2[_operand2.length() * 4 - 1 - i]);
		for (int i = _operand2.length() * 4; i < 128; i++)
			SetBit(operand2, i, false);
		tmp = operand1 ^ operand2;
		hex = DecToHex(tmp);
		res = convertToString(hex);
		delete[] bin1, delete[] bin2, delete[] hex1, delete[] hex2, delete[]hex;
	}
	else
		return "Nhap sai he so";
	while (res[0] == '0' && res.length() > 1)
		res.erase(0, 1);
	return res;
}

//------------------------------------------------------------

	//Hàm thực hiện NOT toán hạng ở hệ cơ số base và trả về kết quả cũng ở hệ cơ số base
	//		Input là string của toán hạng và giá trị của hệ cơ số của toán hạng
	//		Output là string kết quả ở hệ cơ số tương ứng
string NOT(string _operand, short int base)
{
	if (base == 10 && (isOverFlowDec(_operand)))
	{
		return "Invalid Input ";
	}
	QInt operand=_0;//biến khi lưu trữ kiểu QInt
	char* hex;//biến khi lưu trữ kiểu hexa
	bool* bin;//biến khi lưu trữ kiểu binary
	string res = "";//kết quả đầu ra

	QInt tmp;//kết quả dạng QInt
	if (base == 2)
	{
		bin = ConvertToBinary(_operand);
		for (int i = 0; i < 128; i++)
			SetBit(operand, i, bin[i]);
		tmp = ~operand;
		for (int i = 0; i < 128; i++)
			bin[i] = GetBit(tmp, i);
		res = BinConvertToString(bin);
		delete[] bin;
	}
	else if (base == 10)
	{
		operand = _operand;
		tmp = ~operand;
		res = DecConvertToString(tmp);
	}
	else if (base == 16)
	{
		hex = StringHexConvertToChar(_operand);
		bin = HexToBin(hex);
		for (int i = 0; i < _operand.length() * 4; i++)
			SetBit(operand, i, bin[_operand.length() * 4 - 1 - i]);
		for (int i = _operand.length() * 4; i < 128; i++)
			SetBit(operand, i, false);
		tmp = ~operand;
		hex = DecToHex(tmp);
		res = convertToString(hex);
		delete[] bin, delete[]hex;
	}
	else
		return "Nhap sai he so";
	while (res[0] == '0' && res.length() > 1)
		res.erase(0, 1);
	return res;
}

//------------------------------------------------------------

	//Hàm thực hiện so sánh bằng hai toán hạng ở hệ cơ số base và trả về kết quả là string "true", "false"
	//		Input là hai string toán hạng và giá trị của hệ cơ số của toán hạng
	//		Output là string kết quả "true" hoặc "false".
	//			"true" nếu hai toán hạng bằng nhau. "false" nếu ngược lại
string isEqual(string _operand1, string _operand2, short int base)
{
	if (base == 10 && (isOverFlowDec(_operand1) || isOverFlowDec(_operand2)))
	{
		return "Invalid Input ";
	}
	QInt A=_0, B=_0;
	if (base == 10)
	{
		A = _operand1;
		B = _operand2;
	}
	if (base == 2)
	{
		bool* temp = ConvertToBinary(_operand1);
		for (int i = 0; i < 128; i++)
			SetBit(A, i, temp[i]);
		delete[] temp;
		temp = ConvertToBinary(_operand2);
		for (int i = 0; i < 128; i++)
			SetBit(B, i, temp[i]);
		delete[] temp;
	}
	if (base == 16)
	{
		char* temp1 = StringHexConvertToChar(_operand1);
		bool* temp2 = HexToBin(temp1);
		A = BinToDec(temp2);
		delete[]temp1;
		delete[]temp2;
		
		temp1 = StringHexConvertToChar(_operand2);
		temp2 = HexToBin(temp1);
		B = BinToDec(temp2);
		delete[]temp1;
		delete[]temp2;
	}
	if (A == B)
		return "true";
	return "false";
}

//------------------------------------------------------------

	//Hàm thực hiện so sánh bé hơn hai toán hạng ở hệ cơ số base và trả về kết quả là string "true", "false"
	//		Input là hai string toán hạng và giá trị của hệ cơ số của toán hạng
	//		Output là string kết quả "true" hoặc "false".
	//			"true" nếu toán hạng thứ 1 bé hơn toán hạng thứ 2. "false" nếu ngược lại
string isLess(string _operand1, string _operand2, short int base)
{
	if (base == 10 && (isOverFlowDec(_operand1) || isOverFlowDec(_operand2)))
	{
		return "Invalid Input ";
	}
	QInt A = _0, B = _0;
	if (base == 10)
	{
		A = _operand1;
		B = _operand2;
	}
	if (base == 2)
	{
		bool* temp = ConvertToBinary(_operand1);
		for (int i = 0; i < 128; i++)
			SetBit(A, i, temp[i]);
		delete[] temp;
		temp = ConvertToBinary(_operand2);
		for (int i = 0; i < 128; i++)
			SetBit(B, i, temp[i]);
		delete[] temp;
	}
	if (base == 16)
	{
		char* temp1 = StringHexConvertToChar(_operand1);
		bool* temp2 = HexToBin(temp1);
		A = BinToDec(temp2);
		delete[]temp1;
		delete[]temp2;

		temp1 = StringHexConvertToChar(_operand2);
		temp2 = HexToBin(temp1);
		B = BinToDec(temp2);
		delete[]temp1;
		delete[]temp2;
	}
	if (A < B)
		return "true";
	return "false";
}

//------------------------------------------------------------

	//Hàm thực hiện so sánh lớn hơn hai toán hạng ở hệ cơ số base và trả về kết quả là string "true", "false"
	//		Input là hai string toán hạng và giá trị của hệ cơ số của toán hạng
	//		Output là string kết quả "true" hoặc "false".
	//			"true" nếu toán hạng thứ 1 lớn hơn toán hạng thứ 2. "false" nếu ngược lại
string isGreater(string _operand1, string _operand2, short int base)
{
	if (base == 10 && (isOverFlowDec(_operand1) || isOverFlowDec(_operand2)))
	{
		return "Invalid Input ";
	}
	QInt A = _0, B = _0;
	if (base == 10)
	{
		A = _operand1;
		B = _operand2;
	}
	if (base == 2)
	{
		bool* temp = ConvertToBinary(_operand1);
		for (int i = 0; i < 128; i++)
			SetBit(A, i, temp[i]);
		delete[] temp;
		temp = ConvertToBinary(_operand2);
		for (int i = 0; i < 128; i++)
			SetBit(B, i, temp[i]);
		delete[] temp;
	}
	if (base == 16)
	{
		char* temp1 = StringHexConvertToChar(_operand1);
		bool* temp2 = HexToBin(temp1);
		A = BinToDec(temp2);
		delete[]temp1;
		delete[]temp2;

		temp1 = StringHexConvertToChar(_operand2);
		temp2 = HexToBin(temp1);
		B = BinToDec(temp2);
		delete[]temp1;
		delete[]temp2;
	}
	if (A > B)
		return "true";
	return "false";
}

//------------------------------------------------------------

	//Hàm thực hiện so sánh bé hơn hoặc bằng hai toán hạng ở hệ cơ số base và trả về kết quả là string "true", "false"
	//		Input là hai string toán hạng và giá trị của hệ cơ số của toán hạng
	//		Output là string kết quả "true" hoặc "false".
	//			"true" nếu toán hạng thứ 1 bé hơn hoặc bằng toán hạng thứ 2. "false" nếu ngược lại
string isLessOrEqual(string _operand1, string _operand2, short int base)
{
	if (base == 10 && (isOverFlowDec(_operand1) || isOverFlowDec(_operand2)))
	{
		return "Invalid Input ";
	}
	QInt A = _0, B = _0;
	if (base == 10)
	{
		A = _operand1;
		B = _operand2;
	}
	if (base == 2)
	{
		bool* temp = ConvertToBinary(_operand1);
		for (int i = 0; i < 128; i++)
			SetBit(A, i, temp[i]);
		delete[] temp;
		temp = ConvertToBinary(_operand2);
		for (int i = 0; i < 128; i++)
			SetBit(B, i, temp[i]);
		delete[] temp;
	}
	if (base == 16)
	{
		char* temp1 = StringHexConvertToChar(_operand1);
		bool* temp2 = HexToBin(temp1);
		A = BinToDec(temp2);
		delete[]temp1;
		delete[]temp2;

		temp1 = StringHexConvertToChar(_operand2);
		temp2 = HexToBin(temp1);
		B = BinToDec(temp2);
		delete[]temp1;
		delete[]temp2;
	}
	if (A <= B)
		return "true";
	return "false";
}

//------------------------------------------------------------

	//Hàm thực hiện so sánh lớn hơn hoặc bằng hai toán hạng ở hệ cơ số base và trả về kết quả là string "true", "false"
	//		Input là hai string toán hạng và giá trị của hệ cơ số của toán hạng
	//		Output là string kết quả "true" hoặc "false".
	//			"true" nếu toán hạng thứ 1 lớn hơn hoặc bằng toán hạng thứ 2. "false" nếu ngược lại
string isGreaterOrEqual(string _operand1, string _operand2, short int base)
{
	if (base == 10 && (isOverFlowDec(_operand1) || isOverFlowDec(_operand2)))
	{
		return "Invalid Input ";
	}
	if (base == 10 && (isOverFlowDec(_operand1) || isOverFlowDec(_operand2)))
	{
		return "Invalid Input ";
	}
	QInt A = _0, B = _0;
	if (base == 10)
	{
		A = _operand1;
		B = _operand2;
	}
	if (base == 2)
	{
		bool* temp = ConvertToBinary(_operand1);
		for (int i = 0; i < 128; i++)
			SetBit(A, i, temp[i]);
		delete[] temp;
		temp = ConvertToBinary(_operand2);
		for (int i = 0; i < 128; i++)
			SetBit(B, i, temp[i]);
		delete[] temp;
	}
	if (base == 16)
	{
		char* temp1 = StringHexConvertToChar(_operand1);
		bool* temp2 = HexToBin(temp1);
		A = BinToDec(temp2);
		delete[]temp1;
		delete[]temp2;

		temp1 = StringHexConvertToChar(_operand2);
		temp2 = HexToBin(temp1);
		B = BinToDec(temp2);
		delete[]temp1;
		delete[]temp2;
	}
	if (A >= B)
		return "true";
	return "false";
}

//------------------------------------------------------------

	//Hàm chuyển đổi hệ cơ số cho chuỗi số. Từ base1 sang base2
	//		Input là string toán hạng, hệ cơ số gốc base1 và hệ cơ số đích base2, và biến bool cho biết làm việc trên QInt hay QFloat
	//		Output là string kết quả đã được chuyển sang hệ cơ số đích
string ConvertBases(string _operand, short int base1, short int base2, bool isFloat)
{
	if (_operand == "")
		return "";
	if (base1 == 10 && (isOverFlowDec(_operand) && !isFloat))
	{
		return "Invalid Input ";
	}
	if (!isFloat)
	{	
		if (base1 == base2)
			return _operand;
		QInt A = _0;
		if (base1 == 2)
		{
			while (_operand.length() < 128)
				_operand = "0" + _operand;
			reverse(_operand.begin(), _operand.end());
			bool* bin = ConvertToBinary(_operand);
			if (base2 == 10)
			{
				A = BinToDec(bin);
				delete[] bin;
				return PrintQInt(A);
			}
			if (base2 == 16)
			{
				char* hex;
				bool flag = false;
				hex = BinToHex(bin);
				delete[] bin;
				string t = "";
				for (int i = 0; i < (N * NBIT) / 4; i++)
				{
					if (hex[i] != '0')
						flag = true;
					if (flag)
						t += hex[i];
				}
				if (!flag)
					t = "0";
				delete[]hex;
				return t;
			}
		}
		if (base1 == 10)
		{
			A = _operand;
			if (base2 == 2)
			{
				string t = "";
				bool* bin;
				bool flag = false;
				bin = DecToBin(A);
				for (int i = 0; i < N * NBIT; i++)
				{
					if (bin[i] != 0)
						flag = true;
					if (flag)
						t += to_string(bin[i]);
				}
				if (!flag)
					t = "0";
				delete[] bin;
				return t;
			}
			if (base2 == 16)
			{
				string t = "";
				char* hex;
				bool flag = false;
				hex = DecToHex(A);
				for (int i = 0; i < (N * NBIT) / 4; i++)
				{
					if (hex[i] != '0')
						flag = true;
					if (flag)
						t += hex[i];
				}
				if (!flag)
					t = "0";
				delete[] hex;
				return t;
			}
		}
		if (base1 == 16)
		{
			while (_operand.length() < 32)
				_operand = "0" + _operand;
			char* hex = StringHexConvertToChar(_operand);
			if (base2 == 10)
			{
				bool* tmp = HexToBin(hex);
				A = BinToDec(tmp);
				delete[] tmp; delete[] hex;
				return PrintQInt(A);

			}
			if (base2 == 2)
			{
				string t = "";
				bool* bin;
				bool flag = false;
				bin = HexToBin(hex);
				for (int i = 0; i < N * NBIT; i++)
				{
					if (bin[i] != 0)
						flag = true;
					if (flag)
						t += to_string(bin[i]);
				}
				if (!flag)
					t = "0";
				delete[] bin; delete[] hex;
				return t;
			}

		}
	}
	else
	{
		QFloat X = __0;
		if (base1 == 2)
		{
			while (_operand.length() < 128)
				_operand = "0" + _operand;
			if (base2 == 2)
				return _operand;
			reverse(_operand.begin(), _operand.end());
			bool* tmp = ConvertToBinary(_operand);
			X = BinToDec(tmp,0);
			delete[] tmp;
			return PrintQFloat(X);
		}
		if (base1 == 10)
		{
			ScanQFloat(X, _operand);
			bool* tmp = DecToBin(X, 0);
			string t = BinConvertToString(tmp);
			reverse(t.begin(), t.end());
			delete[] tmp;
			if (base2 == 10)
				return PrintQFloat(X);
			return t;
		}
	}
}

//------------------------------------------------------------