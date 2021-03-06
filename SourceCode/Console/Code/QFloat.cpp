#include "QFloat.h"



//-----------------------------------------------------------

	//Hàm trả về giá trị nhỏ hơn trong 2 số A và B
int min(int A, int B)
{
	if (A < B)
		return A;
	return B;
}

//--------------------------------------------------------------

	//Hàm cộng chuỗi string có dạng nhị phân với 1. Hỗ trợ cho làm tròn bit thứ 113 của phần trị
	//		Input là chuỗi string có dạng nhị phân
	//		Output là chuỗi string nhị phân đã xử lí cộng 1
string AddOne(string a)
{
	bool nho = 0;
	bool a1, b1;
	string b = "";

	//Tạo b =1 nhưng gán thêm 0 để có chiều dài bằng string b 
	for (int i = 0; i < a.length() - 1; i++)
		b += "0";
	b += "1";

	//lưu kết quả và c
	string c = "";

	//tiến hành cộng có nhớ từng phần tử một
	for (int i = a.length() - 1; i >= 0; i--)
	{
		if (a[i] == '1')
			a1 = true;
		else
			a1 = false;
		if (b[i] == '1')
			b1 = true;
		else
			b1 = false;
		int x = int(a1) + int(b1) + int(nho);
		switch (x)
		{
		case 3: nho = 1; c += "1"; break;
		case 2: nho = 1; c += "0"; break;
		case 1: nho = 0; c += "1"; break;
		case 0: nho = 0; c += "0"; break;
		}
	}
	//Đảo string 
	reverse(c.begin(), c.end());
	return c;
}

//----------------------------------------------------------------

	//Hàm trừ chuỗi string có dạng nhị phân với 1. Hỗ trợ cho làm tròn bit thứ 113 của phần trị.
	//		Input là chuỗi string có dạng nhị phân
	//		Output là chuỗi string nhị phân đã xử lí trừ 1
string SubOne(string a)
{
	bool nho = 0;
	bool a1, b1;
	string b = "";

	//tạo string b thành số bù 2 của 1 có dạng n số 1 (n=chiều dài a)
	for (int i = 0; i < a.length(); i++)
		b += "1";

	// lưu kết quả vào c
	string c = "";

	//Tiến hành cộng có nhớ từng phần tử một
	for (int i = a.length() - 1; i >= 0; i--)
	{
		if (a[i] == '1')
			a1 = true;
		else
			a1 = false;
		if (b[i] == '1')
			b1 = true;
		else
			b1 = false;
		int x = int(a1) + int(b1) + int(nho);
		switch (x)
		{
		case 3: nho = 1; c += "1"; break;
		case 2: nho = 1; c += "0"; break;
		case 1: nho = 0; c += "1"; break;
		case 0: nho = 0; c += "0"; break;
		}
	}

	//Đảo string 
	reverse(c.begin(), c.end());
	return c;
}

//--------------------------------------------------------

	//	Hàm kiểm tra phần mũ là trường hợp nào trong các trường hợp theo quy ước IEEE
	//		Input là biến QFloat x
	//		Output là biến int có giá trị -1 hoặc 0 hoặc 1
	//			Trả về 0 khi phần mũ chỉ toàn bit 0.
	//			Trả về 1 khi phần mũ chỉ toàn bit 1
	//			Trả về -1 cho các trường hợp còn lại
int CheckExponent(QFloat x)
{
	int check;
	int count = 0;
	for (int i = 126; i >= 112; i--)
		count = count | (int)GetBit(x, i) << (14 - (i - 112));
	if (count == 32767)
		check = 1;
	else if (count == 0)
		check = 0;
	else check = -1;
	return check;
}

//---------------------------------------------------------

	// Hàm kiểm tra phần giá trị 112bit có bằng 0 hay không
	//		Input là biến QFloat x
	//		Output là biến bool 0 hoắc 1. Trả về 0 khi phần trị bằng 0. Và 1 khi khác 0
bool CheckSignificand(QFloat x)
{
	int check = 0;

	//Chỉ cần có 1 bit là 1 trong số 112 bit thì phần trị chắc chắn khác 0
	for (int i = 0; i < 112; i++)
		if (GetBit(x, i) == 1)
			check = 1;

	return check;
}

//------------------------------------------------------------

	// Hàm lấy giá trị bit tại một vị trí bất kì. 
	//		Input là biến QFloat x và vị trí cần lấy giá trị pos
	//		Output là biến bool thể hiện bit tại vị trí cần lấy
bool GetBit(QFloat x, short int pos)
{
	//Thực hiện bằng cách đẩy bit cần đọc đến vị trí 0 và AND với 1
	if (pos >= 128 || pos < 0)
		return 0;
	return (x.data[pos / 32] >> (pos % 32)) & 1;
}

//-----------------------------------------------------------

	// Thủ tục gán giá trị bit tại một vị trí bất kì. 
	//		Input là biến QFloat x, vị trí cần gán pos và giá trị bit muốn gán 
void SetBit(QFloat& x, short int pos, bool bit)
{

	// bit = 1 Gán bit bằng phép OR bit tại đó với 1, không quan tâm giá trị cũ. Do dù giá trị cũ là gì khi OR với 1 sẽ ra 1. Các vị trí khác không ảnh hưởng
	// bit = 0 Lật bit bằng phép XOR bit tại đó với 1, chỉ thực hiện khi giá trị cũ là 1. Do khi bit cũ là 0 sẵn thì không cần lật. Còn khi bit cũ là 1 thì XOR sẽ là 0 và giúp các vị trí khác không ảnh hưởng
	if (bit == 1)
		x.data[pos / 32] = x.data[pos / 32] | (1 << (pos % 32));
	else
		if (GetBit(x, pos) == 1)
			x.data[pos / 32] = x.data[pos / 32] ^ (1 << (pos % 32));
}

//-----------------------------------------------------------

	//Hàm chuyển chuỗi dec sang chuỗi nhị phân
string strDecToStrBin(string& in)
{

	//Nếu chuỗi vào là 0 thì chuỗi ra là 0
	if (in == "0")
		return "0";

	//Thực hiện đổi bằng cách thực hiện phương pháp chia lấy phần dư giá trị thập phân cho 2 và đảo ngược thứ tự dãy bit nhận dược
	bool remain = 0;
	string res = "", t = "";
	while (in != "0")
	{
		in = DivisionStringByTwo(in, remain);
		if (remain == false)
			t = "0";
		else
			t = "1";
		res += t;
	}
	reverse(res.begin(), res.end());

	return res;
}

//-----------------------------------------------------------

	//Hàm đọc QFloat a thành mảng nhị phân kiểu bool
	//		Input là biến QFloat a và tham số kiểu int để phân biệt với hàm cùng tên của CTDL QInt
	//		Output là con trỏ trỏ đến địa chỉ mảng bool được cấp phát trong chương trình
bool* DecToBin(QFloat a, int)
{
	//Khởi tạo mảng bool 128 phần tử
	bool* res = new bool[128];

	//Đọc từng bit của a bằng cách đẩy bit cần đọc về vị trí 0 và AND với 1. Tương tự hàm GetBit
	//Sau đó gán phần tử tại vị trí tương ứng của mảng bool là bit đọc được
	for (int i = 4 - 1; i >= 0; i--)
	{
		for (int j = 32 - 1; j >= 0; j--)
		{
			int k = a.data[i] >> j;
			if (k & 1)
				res[128 - 1 - (32 * i + j)] = 1;
			else
				res[128 - 1 - (32 * i + j)] = 0;
		}
	}
	return res;
}

//-----------------------------------------------------------

	//Hàm lưu mảng nhị phân bits thành số kiểu QInt
	//		Input là mảng bool bits và tham số kiểu int để phân biệt với hàm cùng tên của CTDL QInt
	//		Output là biến kiểu dữ liệu QFloat.
QFloat BinToDec(bool* bit, int)
{

	//Khởi tạo biến QFloat có giá trị 0
	QFloat Dec = __0;

	//Đọc từng phần tử trong mảng truyền vảo và gán cho bit ở vị trí tương ứng của biến QFloat. Thuật toán tương tự SetBit
	for (int i = 0; i < 128; i++)
	{
		int pos = i / 32;
		//ap dụng công thức dịch trái
		Dec.data[4 - 1 - pos] = Dec.data[4 - 1 - pos] | ((unsigned int)bit[i] << (32 - 1 - (i - pos * 32)));
	}
	return Dec;
}

//-----------------------------------------------------------

	// Thủ tục khởi tạo giá trị cho biến QFloat x
	//		Input vào là tham chiếu biến QFloat x và string dec được khởi tạo mặc định là rỗng
void ScanQFloat(QFloat& x, string dec)
{
	//gán giá trị cho 128 bit là 0
	x = __0;
	string str;

	if (dec != "")
		str = dec;
	else
	{
		cout << "Nhap so thuc: ";
		cin >> str;
	}

	string Sign = "0";
	if (str[0] == 45)//so am 
	{
		Sign = "1";
		SetBit(x, 127, 1);//do số âm nên set lại bit 0 là 1
		str.erase(0, 1);//xoa dấu trừ của chuỗi
	}
	else
		SetBit(x, 127, 0);
	//Nếu số nhập không có phần thập phần ta phải thêm phần thập phân 
	if (str.find(".") == -1)
		str += ".0";
	//Chia chuỗi vừa nhập thành phần nguyên và thập phân 
	string nguyen = "", thapPhan = "";
	int viTri = str.find('.', 0);//Tìm vị trí dấu chấm
	nguyen = str.substr(0, viTri);
	thapPhan = str.substr(viTri + 1, str.length() - viTri - 1);
	// chuyển phần nguyên sang nhị phân 
	string res = "";
	string t = "";
	bool remain = 0;
	// khi số nguyên khác 0/
	nguyen = strDecToStrBin(nguyen);
	//chuyển phần thập phân sang nhị phân 
	int lenNguyen = nguyen.length() - 1;
	int lenThapPhan = thapPhan.length();
	res = "";
	int i = 0;
	int dieuKien;
	bool flag;
	if (nguyen == "0")
	{
		dieuKien = 115;
		flag = 0;
	}
	else
	{
		dieuKien = 112 - lenNguyen + 1;
		flag = 1;
	}
	if (thapPhan != "0")
	{
		while (i < dieuKien)
		{
			thapPhan = MultiplyString(thapPhan, "2");
			if (thapPhan.length() > lenThapPhan)
			{
				thapPhan.erase(0, 1);
				t = "1";
				flag = 1;
			}
			else
			{
				t = "0";
			}
			res += t;
			if (flag)
				i++;
		}

	}
	else
	{
		while (i < dieuKien)
		{
			res += "0";
			i++;
		}

	}
	thapPhan = res;

	//Tìm số mũ
	int E;
	if (nguyen == "0")//khi số nguyên bằng 0
		E = -(int)thapPhan.find("1") - 1;
	else
		E = (int)nguyen.length() - 1;

	//Tìm exponent
	res = "";
	string exponent;
	int exp = E + 16383;
	if (str == "0.0")
		exp = 0;
	exponent = to_string(exp);
	exponent = strDecToStrBin(exponent);
	if (exponent.length() < 15)
	{
		while (exponent.length() < 15)
			exponent = "0" + exponent;
	}


	//Kết hợp 3 phần lại 
	string significand = "";

	if (nguyen == "0")
	{
		significand = thapPhan;//Significand
		significand.erase(0, -E);
		significand.erase(113);

	}
	else
	{
		significand = nguyen + thapPhan;//Significand
		significand.erase(0, 1);
	}

	//Lam tron
	if (Sign == "0")//So Dương
	{
		if (significand[112] == '1')//Neu duoi du la 1 thi lam tron
		{
			significand.erase(112);
			significand = AddOne(significand);
		}
		else
			significand.erase(112);
	}
	else//Số âm 
	{
		if (significand[112] == '1')//Neu duoi du la 1 thi lam tron
		{
			significand.erase(112);
			significand = SubOne(significand);
		}
		else
			significand.erase(112);
	}

	string SEF = "";

	SEF = Sign + exponent + significand;


	for (int i = 0; i <= 127; i++)
	{
		int bit = 0;
		if (SEF[i] == '1')
			bit = 1;
		SetBit(x, 127 - i, bit);
	}

}

//-----------------------------------------------------------

	//Hàm trả về giá trị chuỗi thập phân của biến QFloat x
	//		Input là biến QFloat x
	//		Output là string chưa giá trị thập phân của x
string PrintQFloat(QFloat x)
{
	string result = "";
	//các trường hợp đặc biệt
	if (CheckExponent(x) == 0 && CheckSignificand(x) == 0)//số 0
		result = "0.0";
	else if (CheckExponent(x) == 1 && CheckSignificand(x) == 0)//số vô cùng
		result = "Infinity";
	else if (CheckExponent(x) == 1 && CheckSignificand(x))//số báo lỗi
		result = "NaN";
	else if (CheckExponent(x) == 0 && CheckSignificand(x))//số không thể chuẩn hóa
	{
		result = "Denormalized";
	}
	//cách tính tổng quát
	else {
		// Tìm số mũ E
		int exp = 0;
		for (int i = 126; i >= 112; i--)
		{
			exp = exp | (int)GetBit(x, i) << (14 - (126 - i));
		}
		exp = exp - (pow(2, 14) - 1);//K=(pow(2, 14) - 1)
		string phan_nguyen = "";
		string phan_thap_phan = "";
		string tmp = "";//dùng khi tính phần thập phân
		if (exp >= 0)
		{
			//công thức tính phần nguyên
			for (int i = 0; i < min(exp, 112); i++)
			{
				if ((int)GetBit(x, 111 - i))
					phan_nguyen = AdditionString(phan_nguyen, PowerStringOfTwo(exp - 1 - i));
			}
			phan_nguyen = AdditionString(phan_nguyen, PowerStringOfTwo(exp));

			//Công thức tính phần thập phân
			for (int i = 111 - exp; i >= 0; i--)
			{
				if (GetBit(x, i))
					tmp = AdditionString(tmp, PowerStringOfTwo(i - (112 - exp)));
			}
		}
		else
		{
			phan_nguyen = "0";
			for (int i = 111; i >= 0; i--)
			{
				if (GetBit(x, i))
					tmp = AdditionString(tmp, PowerStringOfTwo(i - (112 - exp)));
			}
			tmp = AdditionString(tmp, PowerStringOfTwo(exp));
		}


		phan_thap_phan = tmp;
		if (phan_thap_phan != "")
			phan_thap_phan.erase(0, 2);
		else
			phan_thap_phan = "0";
		//Xét trường hợp số âm hoặc dương

		if (GetBit(x, 127))
			result = "-" + phan_nguyen + "." + phan_thap_phan;
		else
			result = phan_nguyen + "." + phan_thap_phan;

	}
	return result;
}