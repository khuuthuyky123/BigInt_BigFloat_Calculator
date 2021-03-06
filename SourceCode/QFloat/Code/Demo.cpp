#include "Demo.h"


//-----------------------------------------------------------
	// Hàm quá tải toán tử nhập để tách cách tham số trong file input, các tham số cách nhau khoảng cách
	//		Hàm trả về mảng string với string[0] là số lượng tham số. Tiếp theo lần lượt là các tham số
istream& operator>>(istream& in, string tmp[])
{
	//Nhâp chuỗi vào
	string s;	
	getline(in, s);	

	//Lưu vị trí bắt đầu của mỗi tham số trong chuỗi
	int start = 0;

	//Lưu số lượng tham số
	int size = 0;

	// Gặp khoảng trắng thì tiến hành lấy chuỗi con từ vị trí start đến vị trí hiện tại 
	//		Lưu chuỗi con tách được vào mảng 
	//				Cập nhật lại start
	for (int i = 0; (unsigned int)(i + 1) < s.length(); i++)
	{
		if (s[i] == ' ')
		{
			string substr = s.substr(start, i - start);
			tmp[++size] = substr;
			start = i + 1;
		}
	}
	
	//Tách tham số cuối cùng và tăng biến đếm số lượng
	string substr = s.substr(start, s.length() - start);
	tmp[++size] = substr;

	//Gán phần tử đầu là số lượng tham số
	tmp[0] = to_string(size);
	return in;

}

//------------------------------------------------------------

	//Hàm chuyển đổi số nhị phân kiểu bool* về dạng string
	//	Input là địa chỉ trỏ đến mảng bool 128 phần tử.
	//  Output là string có các phần tử theo đúng thứ tự trong mảng ban đầu  
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

	//Hàm chuyển đổi hệ cơ số cho chuỗi số. Từ base1 sang base2
	//	Input là string của toán hạng cần chuyển đổi, hệ cơ số gốc base1 và hệ cơ số đích là base2 
	//  Output là string của toán hạng đã được chuyển đổi sang hệ cơ số đích
string ConvertBases(string _operand, short int base1, short int base2)
{
	//nếu không có dữ liệu vào thì không có dữ liệu ra
	if (_operand == "")
		return "";

	//Gán X mặc định là hằng số 0
	QFloat X = __0;

	// Trường hợp hệ cơ số gốc là 2
	//
	if (base1 == 2)
	{

		//Nếu dữ liệu truyền vào chưa đủ 128bit thì tự động fill bằng 0
		while (_operand.length() < 128)
			_operand = "0" + _operand;

		//Nếu hệ cơ số gốc và hệ cơ số đích đều là nhị phân thì không cần chuyển.
		if (base2 == 2)
			return _operand;

		// Đảo ngược thứ tự toán hạng để phù hợp với input của hàng ConvertToBinary
		reverse(_operand.begin(), _operand.end());

		//Lưu mảng đã tách các phần tử về đúng kiểu dữ liệu để dùng hàm BinToDec
		bool* tmp = ConvertToBinary(_operand);

		//Dùng hàm để khởi tạo giá trị cho biến QFloat X
		X = BinToDec(tmp,0);

		//Thu hồi vùng nhớ đã được cấp phát bởi hàm ConvertToBinary
		delete[] tmp;

		//Trả về chuỗi thể hiện giá trị thập phân của X
		return PrintQFloat(X);
	}

	//Trường hợp cơ số gốc là 10
	if (base1 == 10)
	{
		
		// Khởi tạo giá trị cho X bằng hàm ScanQFloat với chuỗi vào thập phân
		ScanQFloat(X, _operand);

		// Lưu mảng nhị phân được đọc từ X
		bool* tmp = DecToBin(X, 0);

		// Chuyển mảng nhị phân sang string để trả về
		string t = BinConvertToString(tmp);

		// Đảo ngược chuỗi do output hàm trên đã bị đảo ngược thứ tự
		reverse(t.begin(), t.end());

		// Thu hồi vùng nhớ đã được cấp phát bởi hàm DecToBin
		delete[] tmp;

		// Nếu hệ cơ số đích và hệ cơ số gốc đều là 10 thì trả về chuỗi thể hiện giá trị thập phân của X.
		if (base2 == 10)
			return PrintQFloat(X);
		return t;
	}
}

//------------------------------------------------------------

	//Hàm đọc dữ liệu từ file in và xuất ra file out
void PROCESS_FROM_FILE(istream& in, ostream& out)
{
	// Nếu con trỏ chưa đọc đến cuối file thì đọc từng dòng và xử lí
	while (!in.eof())
	{
		//Đọc từng dòng và tách thành mảng các tham số nhờ phép quá tải toán tử >>
		string request[4];
		in >> request;

		//chuyển các tham số cần sử dụng về dạng phù hợp và thực hiện xử lí, xuất ra file.
		int p1 = stoi(request[1]);
		int p2 = stoi(request[2]);
		string _operand = request[3];
		out << ConvertBases(_operand, p1, p2)<< endl;
	}
}
