#include "StringCompute.h"


//------------------------------------------------------

	// Hàm đổi kí tự số sang số 
	//		Input là kí tự số
	//		Output là số tương ứng
int Digit(char x)
{
	return (x - '0');
}

//-------------------------------------------------------

	//Hàm cộng hai chuỗi số thực lớn không âm
	//		Input là 2 string số thực
	//		Output là tổng cùa 2 string
string AdditionString(string A, string B)
{

	bool isFloat = 0;
	int posA = A.find(".");
	int posB = B.find(".");
	if (A[0] == '0' && (posA > 1 || (A.length() > 1 && posA == -1)))
	{
		A.erase(A.begin());
	}
	if (B[0] == '0' && (posB > 1 || (B.length() > 1 && posB == -1)))
	{
		B.erase(B.begin());
	}
	string result = "";
	int j = 0;
	if (posA != -1 || posB != -1)
	{
		if (posA == -1)
		{
			A += ".0";
			posA = A.length() - 2;
		}
		if (posB == -1)
		{
			B += ".0";
			posB = B.length() - 2;
		}
		isFloat = 1;
	}
	else
	{
		posA = A.length();
		posB = B.length();
	}

	while (posA < posB)
	{
		A = "0" + A;
		posA++;
	}
	while (posB < posA)
	{
		B = "0" + B;
		posB++;
	}

	if (isFloat)
	{
		while (A.length() < B.length())
		{
			A = A + "0";
		}
		while (B.length() < A.length())
		{
			B = B + "0";;
		}
	}

	for (j = 0; j < A.length(); result += "0", j++);
	for (int i = A.length() - 1; i >= 0; i--)
	{
		if (A[i] == '.')
		{
			result[i] = '.';
			continue;
		}
		int sum = Digit(result[i]) + Digit(A[i]) + Digit(B[i]);
		result[i] = (sum % 10) + '0';
		if (i > 0)
			result[i - 1] = (sum / 10) + '0';
		else
			result = to_string(sum / 10) + result;
	}
	int pos = result.find(".");
	if (result[0] == '0' && (pos > 1 || (result.length() > 1 && pos == -1)))
	{
		result.erase(result.begin());
	}
	return result;
}

//-------------------------------------------------------

	//Hàm nhân hai chuỗi số nguyên không âm
	//		Input là 2 string số nguyên không âm
	//		Output là tich cùa 2 string
string MultiplyString(string A, string B)
{
	if (A == "0" || B == "0")
		return "0";
	if (A == "1")
		return B;
	if (B == "1")
		return A;
	for (; A[0] == '0'; A.erase(0, 1));
	for (; B[0] == '0'; B.erase(0, 1));
	string result = "0";
	int sizeA = (int)A.length();
	int sizeB = (int)B.length();
	int j;
	string tmp = "0", tmp2 = "0";
	for (int iB = sizeB - 1; iB >= 0; iB--)
	{
		j = tmp.length() - 1;
		for (int iA = sizeA - 1; iA >= 0; iA--)
		{
			unsigned int mul = Digit(tmp[j]) + Digit(A[iA]) * Digit(B[iB]);
			tmp[j++] = (mul % 10) + '0';
			tmp += (mul / 10) + '0';
		}
		for (int i = 0; i < (int)tmp.length() / 2; i++)
		{
			swap(tmp[i], tmp[tmp.length() - i - 1]);
		}
		result = AdditionString(result, tmp);
		tmp = tmp2 + "0";
		tmp2 = tmp;
	}


	return result;

}

//-------------------------------------------------------

	// Hàm lũy thừa a^n số nguyên không âm với n nguyên không âm.
	//		Input là string số nguyên không âm và số mũ nguyên không âm n
	//		Output là string số nguyên không âm
string PowerString(string a, unsigned int n)
{
	for (; a[0] == '0'; a.erase(0, 1));
	if (n == 0)
		return "1";
	string result = "1";
	for (unsigned int i = 0; i < n; i++)
		result = MultiplyString(result, a);
	return result;
}

//---------------------------------------------------------

	// Hàm lũy thừa 2^n với n số nguyên.
	//		Input là số mũ nguyên n
	//		Output là string số thực với n âm hoặc string số nguyên nếu n dương
string PowerStringOfTwo(int n) {
	string res = "1";
	string temp = "2";
	if (n == 0)
		return "1";
	if (n > 0)
	{
		if (n == 1)
			return "2";
		while (n > 0)
		{
			if (n & 1)
				res = MultiplyString(res, temp);
			if (n == 1)
				return res;
			n >>= 1;
			temp = MultiplyString(temp, temp);
		}
	}
	else
	{
		if (n == 1)
			return "0.5";
		temp = "5";
		int posTemp = 1;
		int posRes = 0;
		n *= -1;
		while (n > 0)
		{
			if (n & 1)
			{
				res = MultiplyString(res, temp);
				posRes += posTemp;
			}
			if (n == 1)
				break;
			n >>= 1;
			temp = MultiplyString(temp, temp);
			posTemp *= 2;
		}

		if (posRes == res.length())
			res = "0." + res;
		else
		{
			for (int i = 0; i < res.length() - posRes; i++)
			{
				res = "0" + res;
			}
			res = "0." + res;
		}
		while (res[res.length() - 1] == '0' && res[res.length() - 2] != '.')
			res.erase(res.length() - 1, 1);
	}
	return res;
}

//-------------------------------------------------------

	// Hàm chia chuỗi số thực không âm cho 2 
	//		Inpput là srting a có thể là nguyên hoặc thực, số dư remainder và biến bool isFloat cho biết kết quả cần có là số thực hay số nguyên
	//		Output là string kết quả
string DivisionStringByTwo(string a, bool& remainder, bool isFloat)
{
	if (a[0] == '0' && (a.find('0') > 1 || (a.length() > 1 && a.find('0') == -1)))
	{
		a.erase(a.begin());
	}
	string temp = "";
	string result = "";
	int pos = a.length();
	if (isFloat)
	{
		pos = a.find(".");
		if (pos == -1)
		{
			a += ".0";
			pos = a.length() - 2;
		}
	}

	for (int i = 0; i < (int)a.length(); i++)
	{
		if (i == pos)
		{
			result += ".";
			continue;
		}
		temp += a[i];
		result += (stoi(temp) / 2) + '0';
		temp = (stoi(temp) % 2) + '0';
		if (temp == "0")
			temp = "";
	}
	while (temp != "" && isFloat)
	{
		temp += "0";
		result += (stoi(temp) / 2) + '0';
		temp = (stoi(temp) % 2) + '0';
		if (temp == "0")
			temp = "";
	}
	if (temp == "")
		remainder = 0;
	else
		remainder = 1;
	if (result[0] == '0' && pos > 1)
	{
		result.erase(result.begin());
	}
	return result;
}




















/*//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
//		Đây là phần code back up
//string PowerStringOfTwo(int n)
//{
//	if (n == 0)
//		return "1";
//	string result = "1";
//	if (n > 0)
//	{
//		for (int i = 0; i < n; i++)
//			result = MultiplyString(result, "2");
//	}
//	else
//	{
//		bool remain = 0;
//		for (int i = 0; i > n; i--)
//			result = DivisionStringByTwo(result,remain,1);
//	}
//	return result;
//}

if (A == "0" || B == "0" || A=="0.0" || B=="0.0")
		return "0";
	if (A == "1" || A=="1.0")
		return B;
	if (B == "1" || B=="1.0")
		return A;


	int posA = A.find('.');
	int posB = B.find('.');
	int pos = 0, isFloat = 0;
	if (posA != -1 || posB != -1)
	{
		if (posA == -1)
		{
			A += ".0";
			posA = A.length()-1;
		}
		if (posB == -1)
		{
			B += ".0";
			posB = B.length()-1;
		}
		isFloat = 1;
	}
	else
		if (posA == -1 && posB == -1)
		{
			posA = A.length()-1; posB = B.length()-1;
		}

	pos = (A.length() - 1 - posA) + (B.length() - 1 - posB);
	while (A[A.length() - 1] == '0')
		A.erase(A.length() - 1, 1);

	while (A[0] == '0' || A[0] == '.')
		A.erase(0, 1);

	posA = A.find('.');
	if (posA != -1)
		A.erase(posA, 1);

	while (B[B.length() - 1] == '0')
		B.erase(B.length() - 1, 1);

	while (B[0] == '0' || B[0] == '.')
		B.erase(0, 1);

	posB = B.find('.');
	if (posB != -1)
		B.erase(posB, 1);

	string result = "0";
	int sizeA = (int)A.length();
	int sizeB = (int)B.length();
	int j;
	string tmp = "0", tmp2 = "0";
	for (int iB = sizeB - 1; iB >= 0; iB--)
	{
		j = tmp.length() - 1;
		for (int iA = sizeA - 1; iA >= 0; iA--)
		{
			unsigned int mul = Digit(tmp[j]) + Digit(A[iA]) * Digit(B[iB]);
			tmp[j++] = (mul % 10) + '0';
			tmp += (mul / 10) + '0';
		}
		for (int i = 0; i < (int)tmp.length() / 2; i++)
		{
			swap(tmp[i], tmp[tmp.length() - i - 1]);
		}
		result = AdditionString(result, tmp);
		tmp = tmp2 + "0";
		tmp2 = tmp;
	}
	int q;
	if (pos > 0)
	{
		if (pos < result.length())
			result.insert(result.begin() + result.length() - pos, '.');
		else
			if (pos == result.length())
				result = "0." + result;
			else
			{
				for (int i = 0; i < result.length() - pos; i++)
				{
					result = "0" + result;
				}
				result = "0." + result;
			}
		while (result[result.length() - 1] == '0' && result[result.length() - 2] != '.')
			result.erase(result.length() - 1, 1);

	}
	return result;*/