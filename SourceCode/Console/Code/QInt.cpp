#include "QInt.h"

//-----------------------------------------------------------

	// Hàm lấy giá trị bit tại một vị trí bất kì. 
	//		Input là biến QInt x và vị trí cần lấy giá trị pos.
	//		Output là biến bool 0 hoặc 1 là giá bị bit tại vị trí cần lấy
bool GetBit(QInt x, short int pos)
{
	if (pos >= N * NBIT || pos < 0)
		return 0;
	return (x.data[pos / NBIT] >> (pos % NBIT)) & 1;
}

//-----------------------------------------------------------

	// Thủ tục gán giá trị bit tại một vị trí bất kì. 
	//		Input là biến QInt x, vị trí cần gán pos và giá trị bit gán bit.
	//				bit = 1 Gán bit bằng phép OR với 1, không quan tâm giá trị cũ.
	//				bit = 0 Lật bit bằng phép XOR với 1, chỉ thực hiện khi giá trị cũ là 1.
void SetBit(QInt& x, short int pos, bool bit)
{
	if (bit == 1)
		x.data[pos / NBIT] = x.data[pos / NBIT] | (1 << (pos % NBIT));
	else
		if (GetBit(x, pos) == 1)
			x.data[pos / NBIT] = x.data[pos / NBIT] ^ (1 << (pos % NBIT));
}

//-----------------------------------------------------------

	//Hàm chuyển chuỗi kiểu char sang chuỗi kiểu string
	//		Input là con trỏ trỏ đến mảng chuỗi char
	//		Output trả về chuỗi string có cùng dữ liệu
string convertToString(char* a)
{
	if (a == NULL)
		return " ";
	int i;
	string s = "";
	for (i = 0; a[i] != '\0'; i++) {
		s = s + a[i];
	}
	return s;
}

//-----------------------------------------------------------

	// Hàm quá tải toán tử nhập để tách cách tham số trong file input, các tham số cách nhau khoảng cách
	//		Hàm trả về mảng string với string[0] là số lượng tham số. Tiếp theo lần lượt là các tham số
istream& operator>>(istream& in, string tmp[])
{
	string s;
	getline(in, s);
	int start = 0;
	int size = 0;
	for (int i = 0; (unsigned int)(i + 1) < s.length(); i++)
	{
		if (s[i] == ' ')
		{
			string substr = s.substr(start, i - start);
			tmp[++size] = substr;
			start = i + 1;
		}
	}
	string substr = s.substr(start, s.length() - start);
	tmp[++size] = substr;
	tmp[0] = to_string(size);
	return in;

}

//-----------------------------------------------------------

	//Hàm quá tải toán tử AND hai số QInt. 
	//		Input là 2 biến QInt a và b
	//		Output là một biến QInt kết quả
QInt operator&(QInt a, QInt b)
{
	QInt result = _0;
	for (int i = N * NBIT - 1; i >= 0; i--)
	{
		SetBit(result, i, GetBit(a, i) & GetBit(b, i));
	}
	return result;
}

//-----------------------------------------------------------

	//Hàm quá tải toán tử OR hai số QInt.
	//		Input là 2 biến QInt a và b
	//		Output là một biến QInt kết quả
QInt operator|(QInt a, QInt b)
{
	QInt res = _0;
	for (int i = 0; i < N * NBIT; i++)
		SetBit(res, i, (GetBit(a, i) | GetBit(b, i)));
	return res;
}

//-----------------------------------------------------------

	//Hàm quá tải toán tử XOR hai số QInt.
	//		Input là 2 biến QInt a và b
	//		Output là một biến QInt kết quả
QInt operator^(QInt A, QInt B)
{
	QInt C = _0; // QInt ket qua
	for (int i = 0; i < N * NBIT; i++)
	{
		int x = GetBit(A, i); // lay bit tai vi tri i cua A
		int y = GetBit(B, i); // lay bit tai vi tri i cua B
		SetBit(C, i, (x + y) % 2);  // thuc hien xor bit tai vi tri i va gan vao C
	}
	return C;
}

//-----------------------------------------------------------

	//Hàm quá tải toán tử NOT số QInt.
	//		Input là 2 biến QInt a
	//		Output là một biến QInt kết quả
QInt operator~(QInt A)
{
	for (int i = 0; i < N * NBIT; i++)
	{
		SetBit(A, i, 1 - GetBit(A, i)); // dao bit o vi tri i;
	}
	return A;
}

//-----------------------------------------------------------

	//Hàm quá tải toán tử dịch trái số QInt k lần
	//		Input là 2 biến QInt a và số lần k
	//		Output là một biến QInt kết quả
QInt operator<<(QInt a, int k)
{
	QInt result = _0;
	for (int i = 0; i < N * NBIT; i++)
	{
		SetBit(result, N * NBIT - 1 - i, GetBit(a, N * NBIT - 1 - i - k));
	}
	return result;
}

//-----------------------------------------------------------

	//Hàm quá tải toán tử dịch phải số QInt k lần
	//		Input là 2 biến QInt a và số lần k
	//		Output là một biến QInt kết quả
QInt operator>>(QInt a, int k)
{
	QInt res = _0;
	for (int i = 0; i < N * NBIT; i++)
	{
		SetBit(res, i, GetBit(a, i + k));
	}
	return res;
}

//-----------------------------------------------------------

	//Hàm quá tải toán tử cộng hai số QInt
	//		Input là 2 biến QInt a và b
	//		Output là một biến QInt kết quả
QInt operator + (QInt A, QInt B)
{
	bool nho = 0;
	QInt C;
	for (int i = 0; i <= N * NBIT - 1; i++)
	{
		bool a = GetBit(A, i);
		bool b = GetBit(B, i);
		int x = int(a) + int(b) + int(nho);
		switch (x)
		{
		case 3: nho = 1; SetBit(C, i, 1); break;
		case 2: nho = 1; SetBit(C, i, 0); break;
		case 1: nho = 0; SetBit(C, i, 1); break;
		case 0: nho = 0; SetBit(C, i, 0); break;
		}
	}
	return C;
}

//-----------------------------------------------------------

	//Hàm quá tải toán tử trừ hai số QInt.
	//		Input là 2 biến QInt a và b
	//		Output là một biến QInt kết quả
QInt operator - (QInt A, QInt B)
{
	OppositeTranform(B);
	QInt C = A + B;
	return C;
}

//-----------------------------------------------------------

	//Hàm quá tải toán tử nhân hai số QInt.
	//		Input là 2 biến QInt a và b
	//		Output là một biến QInt kết quả
QInt operator * (QInt Q, QInt M)
{
	QInt A = _0;
	bool Q1 = 0;

	for (int i = 0; i < N * NBIT; i++)
	{
		bool Q0 = GetBit(Q, 0);
		if (Q0 == 1 && Q1 == 0)
			A = A - M;
		else
			if (Q0 == 0 && Q1 == 1)
				A = A + M;
		Q1 = Q0;
		bool a = GetBit(A, 0);
		bool a1 = GetBit(A, N * NBIT - 1);
		Q = Q >> 1;
		A = A >> 1;
		SetBit(Q, N * NBIT - 1, a);
		SetBit(A, N * NBIT - 1, a1);
	}
	return Q;
}

//-----------------------------------------------------------

	//Hàm quá tải toán tử chia hai số QInt.
	//		Input là 2 biến QInt a và b
	//		Output là một biến QInt kết quả
QInt operator / (QInt Q, QInt M)
{
	QInt A = _0;
	if (Q < _0)
		A = ~A;
	for (int i = 0; i < N * NBIT; i++)
	{
		bool q = GetBit(Q, N * NBIT - 1);
		Q = Q << 1;
		A = A << 1;
		SetBit(A, 0, q);
		A = A - M;
		if (A < _0)
		{
			SetBit(Q, 0, 0);
			A = A + M;
		}
		else
			SetBit(Q, 0, 1);
	}
	return Q;
}

//-----------------------------------------------------------

	//Hàm quá tải toán tử só sánh lớn hơn
	//		Input là 2 biến QInt a và b
	//		Output là một biến bool kết quả
	//			Nếu A > B trả về true và ngược lại
bool operator >(QInt A, QInt B)
{
	bool x = GetBit(A, N * NBIT - 1); // lay bit dau cua A
	bool y = GetBit(B, N * NBIT - 1); // lay bit dau cua B
	if (x == 1 && y == 0) // neu A < 0 , B > 0 thi A < B
		return 0;
	if (x == 0 && y == 1) // neu A > 0 , B < 0 thi A > B
		return 1;
	for (int i = N * NBIT - 2; i >= 0; i--)
		if (GetBit(A, i) > GetBit(B, i)) // neu truoc do cac bit cua A va B bang nhau thi tai bit i, bit nao lon hon thi lon hon
			return 1; // Neu tai i, bit cua A lon hon thi A > B ( thoa yeu cau, dung )
		else
			if (GetBit(A, i) < GetBit(B, i))
				return 0; // nguoc lai, bit i cua A < bit i cua B thi A < B ( khong thoa yeu cau, sai )
			//A>B
	return 0;
}

//-----------------------------------------------------------

	//Hàm quá tải toán tử só sánh nhỏ hơn.
	//		Input là 2 biến QInt a và b
	//		Output là một biến bool kết quả
	//			Nếu A < B trả về true và ngược lại
bool operator <(QInt A, QInt B)
{
	bool x = GetBit(A, N * NBIT - 1); // lay bit dau cua A
	bool y = GetBit(B, N * NBIT - 1); // lay bit dau cua B
	if (x == 1 && y == 0) // neu A < 0 , B > 0 thi A < B
		return 1;
	if (x == 0 && y == 1) // neu A > 0 , B < 0 thi A > B
		return 0;
	for (int i = N * NBIT - 2; i >= 0; i--)
		if (GetBit(A, i) < GetBit(B, i)) // neu truoc do cac bit cua A va B bang nhau thi tai bit i, bit nao lon hon thi lon hon
			return 1; // Neu tai i, bit cua B lon hon thi B > A ( thoa yeu cau, dung )
		else
			if (GetBit(A, i) > GetBit(B, i))
				return 0; // nguoc lai, bit i cua A > bit i cua B thi A > B ( khong thoa yeu cau, sai )
			//A>B
	return 0;
}

//-----------------------------------------------------------

	//Hàm quá tải toán tử só sánh lớn hơn hoặc bằng.
	//		Input là 2 biến QInt a và b
	//		Output là một biến bool kết quả
	//			Nếu A >= B trả về true và ngược lại
bool operator >= (QInt A, QInt B)
{
	bool x = GetBit(A, N * NBIT - 1); // lay bit dau cua A
	bool y = GetBit(B, N * NBIT - 1); // lay bit dau cua B
	if (x == 1 && y == 0) // neu A < 0 , B > 0 thi A < B
		return 0;
	if (x == 0 && y == 1) // neu A > 0 , B < 0 thi A > B
		return 1;
	for (int i = N * NBIT - 2; i >= 0; i--)
		if (GetBit(A, i) < GetBit(B, i)) // neu truoc do cac bit cua A va B bang nhau thi tai bit i, bit nao lon hon thi lon hon
			return 0; //Neu tai i, bit cua B lon hon thi B > A ( khong thoa yeu cau, sai )
		else
			if (GetBit(A, i) > GetBit(B, i))
				return 1; // nguoc lai, bit i cua A > bit i cua B thi A > B ( thoa yeu cau, dung )
			// A >= B
	return 1;
}

//-----------------------------------------------------------

	//Hàm quá tải toán tử só sánh nhỏ hơn hoặc bằng hai.
	//		Input là 2 biến QInt a và b
	//		Output là một biến bool kết quả
	//			Nếu A <= B trả về true và ngược lại
bool operator <= (QInt A, QInt B)
{
	bool x = GetBit(A, N * NBIT - 1); // lay bit dau cua A
	bool y = GetBit(B, N * NBIT - 1); // lay bit dau cua B
	if (x == 0 && y == 1) // neu A > 0 , B < 0 thi A > B
		return 0;
	if (x == 1 && y == 0) // neu A < 0 , B > 0 thi A < B
		return 1;
	for (int i = N * NBIT - 2; i >= 0; i--)
		if (GetBit(A, i) > GetBit(B, i)) // neu truoc do cac bit cua A va B bang nhau thi tai bit i, bit nao lon hon thi lon hon
			return 0; //Neu tai i, bit cua A lon hon thi A > B( khong thoa yeu cau, sai )
		else
			if (GetBit(A, i) < GetBit(B, i))
				return 1; // nguoc lai, bit i cua A < bit i cua B thi A < B ( thoa yeu cau, dung )
			// A<=B
	return 1;
}

//-----------------------------------------------------------

	//Hàm quá tải toán tử só sánh bằng hai số.
	//		Input là 2 biến QInt a và b
	//		Output là một biến bool kết quả
	//			Nếu A = B trả về true và ngược lại
bool operator == (QInt A, QInt B)
{
	for (int i = 0; i < N * NBIT; i++)
		if (GetBit(A, i) != GetBit(B, i))
			return 0; // Neu co 1 bit i cua A khac bit i cua B thi A!=B ( Khong thoa yeu cau, sai)
	return 1;
}

//-----------------------------------------------------------

	// Hàm quá tải toán tử  so sánh 2 số.
	//		Input là 2 biến QInt a và b
	//		Output là một biến bool kết quả
	//			Nếu A!=B trả về true và ngược lại
bool operator != (QInt A, QInt B)
{
	for (int i = 0; i < N * NBIT; i++)
		if (GetBit(A, i) != GetBit(B, i))
			return 1; // Neu co 1 bit i cua A khac bit i cua B thi A!=B ( thoa yeu cau, dung)
	return 0;
}

//-----------------------------------------------------------

	//Hàm thực hiện phép xoay trái bit
	//		Input là biến QInt a
	//		Output là một biến QInt kết quả
QInt RoL(QInt a)
{
	//Gan bit nho nhat
	bool bit = GetBit(a, N * NBIT - 1);
	QInt b = _0;
	//Quay bit
	for (int i = 0; i < N * NBIT - 1; i++)
	{
		bool x = GetBit(a, i);
		SetBit(b, i + 1, x);
	}
	SetBit(b, 0, bit);
	return b;
}

//-----------------------------------------------------------

	//Hàm thực hiện phép xoay phải bit
	//		Input là biến QInt a
	//		Output là một biến QInt kết quả
QInt RoR(QInt a)
{
	//Gan bit lon nhat
	bool bit = GetBit(a, 0);
	QInt b = _0;
	//Quay bit
	for (int i = 0; i < N * NBIT - 1; i++)
	{
		bool x = GetBit(a, i + 1);
		SetBit(b, i, x);
	}
	SetBit(b, N * NBIT - 1, bit);
	return b;
}

//-----------------------------------------------------------

	//Hàm nhập dữ liệu cho số QInt a. Có thể nhập vào mảng nhị phân hoặc hoặc mảng chuỗi số nguyên hoặc nhập từ bàn phím.
	//		Nếu gọi hàm ScanQInt(x) sẽ nhập từ bàn phím.
	//		Nếu gọi hàm ScanQInt(x, bits) sẽ nhập từ mảng nhị phân. với bits là mảng bool.
	//		Nếu gọi hàm ScanQInt(x, dec) sẽ nhập từ mảng chuỗi. với dec là string số nguyên.
void ScanQInt(QInt& x, bool* bits)
{
	x = _0;
	for (int i = 0; i < N * NBIT; i++)
	{
		SetBit(x, i, bits[N * NBIT - i - 1]);
		//SetBit(x, i, bits[i]);
	}
}

//-----------------------------------------------------------

	//Hàm nhập dữ liệu cho số QInt a. Có thể nhập vào mảng nhị phân hoặc hoặc mảng chuỗi số nguyên hoặc nhập từ bàn phím.
	//		Nếu gọi hàm ScanQInt(x) sẽ nhập từ bàn phím.
	//		Nếu gọi hàm ScanQInt(x, bits) sẽ nhập từ mảng nhị phân. với bits là mảng bool.
	//		Nếu gọi hàm ScanQInt(x, dec) sẽ nhập từ mảng chuỗi. với dec là string số nguyên.
void ScanQInt(QInt& x, string dec)
{
	x = _0;
	if (dec == " ")
	{
		cout << "Nhap so nguyen lon: ";
		cin >> dec;
	}
	if (dec != " ")
	{
		bool sign = 0;

		if (dec[0] == '-')
		{
			sign = 1;
			dec.erase(dec.begin());
		}
		int i = 0;
		bool remain = 0;
		while (dec != "0")
		{
			dec = DivisionStringByTwo(dec, remain);
			SetBit(x, i++, remain);
		}
		if (sign)
			OppositeTranform(x);
	}
}

//-----------------------------------------------------------

	//Thủ tục xuất giá trị nhị phân của QInt a.
	//		Input là biến QInt 
void PrintBinaQInt(QInt x)
{
	bool o, flag = 0;
	if (x.data[0] == 0 && x.data[1] == 0 && x.data[2] == 0 && x.data[3] == 0)
		cout << 0;
	else
		for (int i = N * NBIT - 1; i >= 0; i--)
		{
			o = GetBit(x, i);
			if (o == 1 && flag == 0)
				flag = 1;
			if (flag == 1)
				cout << o;
		}
	cout << endl;
}

//-----------------------------------------------------------

	//Thủ tục chuyển X thành số đối của nó trong cách biểu diễn bù 2. 
	//		Input là tham chiếu biến QInt x
	//			Thực hiện bằng cách đảo tất cả các bit và cộng 1
void OppositeTranform(QInt& x)
{
	x = ((~x) + _1);
}

//-----------------------------------------------------------

	//Hàm kiểm tra xem QInt x có phải số âm không. 
	//		Trả về true nếu x<0. Và false nếu x>=0
bool isNegative(QInt x)
{
	return GetBit(x, N * NBIT - 1);
}

//-----------------------------------------------------------

	//Hàm xuất giá trị thập phân của QInt a
	//		Thực hiện bằng cách áp dụng công thức hệ cơ số q tổng quát. 
	//				VD: 1101 = 1*(2^3) + 1*(2^2) + 0*(2^1) + 1*(2^0)
	//		Nhưng thay vì đọc từng bit, ta sử dụng giá trị của từng phần tử của mảng data trong kiểu QInt. 
	//				vì giá trị data[i] đã là tổng của 32 bit trong chính nó. Ta chỉ việc nhân thêm một lượng 2^(32*i) là vị trí của nó
string PrintQInt(QInt x)
{
	bool sign = isNegative(x);
	if (sign)
		OppositeTranform(x);
	string result = "0";
	/*
	bool bit
	for (int i = 0; i < N * NBIT; i++)
	{
		bit = GetBit(x, i);
		if (bit==1)
			result = AdditionString(result, PowerString("2", i));
	}*/
	for (int i = 0; i < N; i++)
	{
		result = AdditionString(result, MultiplyString(to_string(x.data[i]), PowerString("2", NBIT * i)));
	}
	if (sign)
		result = "-" + result;
	return result;
}

//-----------------------------------------------------------

	//Hàm chuyển đổi QInt thành mảng nhị phân
	//		Input là biến QInt a
	//		Output là con trỏ trỏ đến mảng bool được cấp phát động lưu giá trị nhị phân được chuyển
bool* DecToBin(QInt a)
{
	bool* res = new bool[N * NBIT];
	for (int i = N - 1; i >= 0; i--)
	{
		for (int j = NBIT - 1; j >= 0; j--)
		{
			int k = a.data[i] >> j;
			if (k & 1)
				res[N * NBIT - 1 - (NBIT * i + j)] = 1;
			else
				res[N * NBIT - 1 - (NBIT * i + j)] = 0;
		}
	}
	return res;
}

//-----------------------------------------------------------

	//Hàm lưu mảng nhị phân thành số kiểu QInt
	//		Input là con trỏ trỏ đến mảng nhị phân kiểu bool
	//		Output là biến QInt
QInt BinToDec(bool* bit)
{
	QInt Dec;
	for (int i = 0; i < N; i++)
		Dec.data[i] = 0;
	for (int i = 0; i < N * NBIT; i++)
	{
		int pos = i / NBIT;
		//ap dụng công thức dịch trái
		Dec.data[N - 1 - pos] = Dec.data[N - 1 - pos] | ((unsigned int)bit[i] << (NBIT - 1 - (i - pos * NBIT)));
	}
	return Dec;
}

//-----------------------------------------------------------

	//Hàm chuyển đổi QInt a thành mảng thập lục phân kiểu char
	//		Input là biến QInt a
	//		Output là con trỏ trỏ đến mảng char được cấp phát động lưu giá trị thập lục phân được chuyển
char* DecToHex(QInt A)
{
	char* S = new char[(N * NBIT) / 4 + 1]; // tao chuoi chua xau Hex. Gioi han la 128 bit nen co do dai cua chuoi Hex la 32 them dau ('-') la 33.
	int n = 0;
	// tao xau S la chuoi Hex tu Qint cho san
	for (int u = 0; u < N; u++)
	{
		unsigned int k = A.data[u];
		for (int i = 0; i < (NBIT / 4); i++)  // 4bit binary -> 1bit hex
		{
			unsigned int t = k % 16;
			k = k / 16;
			if (t < 10)
				S[n] = char(t + 48);
			else
				S[n] = char(t + 55);
			n++;
		}
	}
	// dao nguoc chuoi vi xau S duoc tao thanh bi nguoc.
	char* str = new char[n + 1];
	for (int i = 0; i < n; i++)
		str[i] = S[n - i - 1];
	str[n] = '\0';
	delete[] S;
	return str;
}

//-----------------------------------------------------------

	//Hàm chuyển đổi mảng thập lục phân thành mảng nhị phân
	//		Input là con trỏ trỏ đến mảng thập lục phân kiểu char
	//		Output là con trỏ trỏ đến mảng char được cấp phát động lưu giá trị thập lục phân được chuyển
bool* HexToBin(char* A)
{
	int m;
	if (A[0] != NULL) m = 1;
	else m = 0;
	while (A[m] != NULL) m++;
	bool* bit = new bool[m * 4];
	int i = 0;
	while (i < m * 4)
	{
		int num;
		if (A[i / 4] == 'A') num = 10;
		else if (A[i / 4] == 'B') num = 11;
		else if (A[i / 4] == 'C') num = 12;
		else if (A[i / 4] == 'D') num = 13;
		else if (A[i / 4] == 'E') num = 14;
		else if (A[i / 4] == 'F') num = 15;
		else num = int(A[i / 4]) - 48;
		switch (num)
		{
		case 0:   bit[i] = 0;   bit[i + 1] = 0;   bit[i + 2] = 0;   bit[i + 3] = 0; break;
		case 1:   bit[i] = 0;   bit[i + 1] = 0;   bit[i + 2] = 0;   bit[i + 3] = 1; break;
		case 2:   bit[i] = 0;   bit[i + 1] = 0;   bit[i + 2] = 1;   bit[i + 3] = 0; break;
		case 3:   bit[i] = 0;   bit[i + 1] = 0;   bit[i + 2] = 1;   bit[i + 3] = 1; break;
		case 4:   bit[i] = 0;   bit[i + 1] = 1;   bit[i + 2] = 0;   bit[i + 3] = 0; break;
		case 5:   bit[i] = 0;   bit[i + 1] = 1;   bit[i + 2] = 0;   bit[i + 3] = 1; break;
		case 6:   bit[i] = 0;   bit[i + 1] = 1;   bit[i + 2] = 1;   bit[i + 3] = 0; break;
		case 7:   bit[i] = 0;   bit[i + 1] = 1;   bit[i + 2] = 1;   bit[i + 3] = 1; break;
		case 8:   bit[i] = 1;   bit[i + 1] = 0;   bit[i + 2] = 0;   bit[i + 3] = 0; break;
		case 9:   bit[i] = 1;   bit[i + 1] = 0;   bit[i + 2] = 0;   bit[i + 3] = 1; break;
		case 10:  bit[i] = 1;   bit[i + 1] = 0;   bit[i + 2] = 1;   bit[i + 3] = 0; break;
		case 11:  bit[i] = 1;   bit[i + 1] = 0;   bit[i + 2] = 1;   bit[i + 3] = 1; break;
		case 12:  bit[i] = 1;   bit[i + 1] = 1;   bit[i + 2] = 0;   bit[i + 3] = 0; break;
		case 13:  bit[i] = 1;   bit[i + 1] = 1;   bit[i + 2] = 0;   bit[i + 3] = 1; break;
		case 14:  bit[i] = 1;   bit[i + 1] = 1;   bit[i + 2] = 1;   bit[i + 3] = 0; break;
		case 15:  bit[i] = 1;   bit[i + 1] = 1;   bit[i + 2] = 1;   bit[i + 3] = 1; break;
		default: break;
		}
		i += 4;
	}
	return bit;
}

//-----------------------------------------------------------

	//Hàm chuyển đổi mảng nhị phân thành mảng thập lục phân
	//		Input là con trỏ trỏ đến mảng nhị phân kiểu bool
	//		Output là con trỏ trỏ đến mảng char được cấp phát động lưu giá trị thập lục phân được chuyển
char* BinToHex(bool* bit)
{
	int Mu2[4] = { 8, 4, 2, 1 };
	char* A = new char[(N * NBIT) / 4+1];
	int i = 0;
	while (i < N * NBIT)
	{
		int ketqua = 0;
		for (int j = i; j < i + 4; j++)
			if (bit[j] == true)
				ketqua += Mu2[j - i];
		if (ketqua < 10)
			A[i / 4] = char(ketqua + 48);
		else switch (ketqua)
		{
		case 10: A[i / 4] = 'A'; break;
		case 11: A[i / 4] = 'B'; break;
		case 12: A[i / 4] = 'C'; break;
		case 13: A[i / 4] = 'D'; break;
		case 14: A[i / 4] = 'E'; break;
		default: A[i / 4] = 'F'; break;
		}
		i += 4;
	}
	A[(N * NBIT) / 4] = '\0';
	return A;
}

//-----------------------------------------------------------

	//Hàm chuyển đổi số nhị phân kiểu bool* về dạng string
	//		Input là địa chỉ trỏ đến mảng bool 128 phần tử.
	//		Output là string có các phần tử bị đảo ngược thứ tự so với mảng ban đầu  
string BinConvertToString(bool* x)
{
	string res;
	for (int i = 0; i < 128; i++)
	{
		res.insert(0, 1, (int)x[i] + '0');
	}
	return res;
}

//------------------------------------------------------------

	//Hàm chuyển đổi chuổi nhị phân kiểu string về dạng bool* 
	//	Input là string có dạng 01
	//	Output là con trỏ trỏ đến mảng bool 128 phần tử được cấp phát động. Tự động thêm 0 vào cho đủ dữ liệu 128bit
	//		Các phần tử trong mảng bool bị đảo ngược lại so với thứ tự trong string. phần tử cuối của string là thành phần tử đầu của bool
bool* ConvertToBinary(string x)
{
	bool* res = new bool[128];
	for (int i = x.length() - 1; i >= 0; i--)
	{
		res[x.length() - i - 1] = x[i] - '0';
	}
	for (int i = 127; i >= x.length(); i--)
	{
		res[i] = 0;
	}
	return res;
}

//------------------------------------------------------------

	//Hàm chuyển đổi chuổi thập lục phân kiểu string về dạng char* 
	//	Input là string có dạng hex
	//	Output là con trỏ trỏ đến mảng char 32 phần tử được cấp phát động.
	//		Các phần tử theo đúng thứ tự như trong string
char* StringHexConvertToChar(string x)
{
	char* res = new char[x.length() + 1];
	for (int i = 0; i < x.length(); i++)
		res[i] = x[i];
	res[x.length()] = '\0';
	return res;
}

//------------------------------------------------------------

	//Hàm chuyển đổi số thập phân kiểu QInt về chuỗi String
	//		Input vào là biến QInt và trả về string chứa giá trị thập phân. Hàm tương tự như PrintQInt
string DecConvertToString(QInt x)
{
	bool sign = isNegative(x);
	if (sign)
		OppositeTranform(x);
	string result = "0";
	for (int i = 0; i < N; i++)
	{
		result = AdditionString(result, MultiplyString(to_string(x.data[i]), PowerString("2", NBIT * i)));
	}
	if (sign)
		result = "-" + result;
	return result;
}
//-----------------------------------------------------------

//QInt& QInt::operator=(char* dec)
//{
//	QInt* tmp = new QInt;
//	ScanQInt(*tmp, 0, convertToString(dec));
//	for (int i = 0; i < N; i++)
//	{
//		this->data[i] = tmp->data[i];
//	}
//	return *this;
//}

//-----------------------------------------------------------

	// Toán tử gán dùng cho việc gán cho QInt một mảng chuỗi số nguyên kiểu string
QInt& QInt::operator=(const string dec)
{
	QInt tmp = _0;
	ScanQInt(tmp, dec);
	for (int i = 0; i < N; i++)
	{
		this->data[i] = tmp.data[i];
	}
	return *this;
}

//-----------------------------------------------------------

