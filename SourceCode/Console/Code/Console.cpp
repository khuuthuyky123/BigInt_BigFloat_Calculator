#include <iostream>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <thread>
#include <conio.h>
#include <ctime>
#include <string.h>
#include <fstream>
#include "Demo.h"
using namespace std;

int Max_Height = 120;
int Max_Width = 12;

// cố định màn hình
void Fixconsolewindow()
{
	HWND consolewindow = GetConsoleWindow();
	long style = GetWindowLong(consolewindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consolewindow, GWL_STYLE, style);
}

// tắt dấu nháy trên màn hình
void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

// di chuyển đến vị trí x , y trên màn hình với x là cột y là dòng
void GotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// tạo màn hình
void DrawBoard(int Height, int Width)
{
	int x = 177;
	GotoXY(0, 0);
	for (int i = 0; i < Height; i++)
	{
		cout << char(x);
	}
	GotoXY(0, Width);
	for (int i = 0; i < Height; i++)
	{
		cout << char(x);
	}
	for (int i = 1; i < Width; i++)
	{
		GotoXY(0, i);
		cout << char(x);
		GotoXY(Height - 1, i);
		cout << char(x);
	}
	GotoXY(0, Width + 4);
	for (int i = 0; i < Height; i++)
	{
		cout << char(x);
	}
	for (int i = 1; i < Width + 4; i++)
	{
		GotoXY(0, i);
		cout << char(x);
		GotoXY(Height - 1, i);
		cout << char(x);
	}
	GotoXY(40, Width + 2);
	cout << "Ese : Back     T : Reset";
	GotoXY(0, Width + 5);
}

// tạo menu chọn nhiệm vụ
void Menu_1()
{
	system("cls");
	DrawBoard(Max_Height, Max_Width);
	GotoXY(40, 2);
	cout << "1 : </> Programmer (QInt).     ";
	GotoXY(40, 4);
	cout << "2 : Colculate (QInt).          ";
	GotoXY(40, 6);
	cout << "3 : </> Programmer (Qfloat).   ";
	GotoXY(40, Max_Width + 2);
	cout << "Ese : Exit";
	GotoXY(0, Max_Width + 5);
}

// tạo menu chọn hệ số QInt
void Menu_2()
{
	system("cls");
	DrawBoard(Max_Height, Max_Width);
	GotoXY(40, 2);
	cout << "1 : Bin.                       ";
	GotoXY(40, 4);
	cout << "2 : Dec.                       ";
	GotoXY(40, 6);
	cout << "3 : Hex.                       ";
	GotoXY(40, Max_Width + 2);
	cout << "Ese : Back";
	GotoXY(0, Max_Width + 5);
}

// tạo menu chọn hệ số QFloat
void Menu_3()
{
	system("cls");
	DrawBoard(Max_Height, Max_Width);
	GotoXY(40, 2);
	cout << "1 : Bin.                       ";
	GotoXY(40, 4);
	cout << "2 : Dec.                       ";
	GotoXY(40, 6);
	cout << "                               ";
	GotoXY(40, Max_Width + 2);
	cout << "Ese : Back";
	GotoXY(0, Max_Width + 5);
}

// ghi các phần tử hoặc kết quả
void PrintS(string S, int k)
{
	int d; // dòng để in
	if (k == 0)
		d = 2;
	else
		if (k == 1)
			d = 6;
		else
			d = 10;
	for (int i = 1; i < 119; i++)
	{
		GotoXY(i, d);
		cout << " ";
		GotoXY(i, d - 1);
		cout << " ";
	}
	int j = 2;
	for (int i = S.size() - 1; i >= 0; i--)
	{
		GotoXY(Max_Height - j, d);
		j++;
		if (j == 120) // khi j == 120 tức là đã ghi tới rìa màn hình nên dời lên trên để ghi tiếp
		{
			d--;
			j = 2;
		}
		cout << S[i];
	}
	GotoXY(0, Max_Width + 5);
}

// ghi toán tử và dấu =
void PrintD(string S, int k)
{
	int d;
	if (k == 0)
		d = 4;
	else
		d = 8;
	for (int i = 2; i < 119; i++)
	{
		GotoXY(i, d);
		cout << " ";
	}
	int j = 5;
	for (int i = S.size() - 1; i >= 0; i--)
	{
		GotoXY(Max_Height - j, d);
		j++;
		cout << S[i];
	}
	GotoXY(0, Max_Width + 5);
}

// ghi lựa chọn chuyển đổi hệ số
void PrintF(int LC)
{
	GotoXY(80, 4);
	if (LC == 1)
		cout << "X: Bin    Y: Dec   Z: Hex";
	else if (LC == 3)
		cout << "         X: Bin    Y: Dec";

}

//chuyển chuỗi S ít ký tự thành số nguyên
int ToInt(string S)
{
	int t = 0;
	for (int i = 0; i < S.size(); i++)
	{
		t = t * 10 + int(S[i]) - 48;
	}
	return t;
}

void main()
{
	int temp;
	int Status = 0;
	int LC = 0;
	string Operator = "";
	string S[2] = { "", "" };
	int Coefficient;
	string Str = "";
	int HT = 0;
	Fixconsolewindow();
	ShowConsoleCursor(false);
	DrawBoard(Max_Height, Max_Width);
	Menu_1();
	while (1)
	{
		temp = toupper(_getch());
		if (Status == 0)
		{
			if (temp < 52 && temp > 48)
			{
				LC = temp - 48;
				Status = 1;
				if (temp < 51)
					Menu_2();
				else
					Menu_3();
			}
			else if (temp == 27)
				break;
		}
		else
			if (Status == 1)
			{
				if (temp == 49)
				{
					Coefficient = 2;
					system("cls");
					DrawBoard(Max_Height, Max_Width);
					Status = 2;
				}
				if (temp == 50)
				{
					Coefficient = 10;
					system("cls");
					DrawBoard(Max_Height, Max_Width);
					Status = 2;
				}
				if (temp == 51 && LC != 3)
				{
					Coefficient = 16;
					system("cls");
					DrawBoard(Max_Height, Max_Width);
					Status = 2;
				}
				if (temp == 27)
				{
					Menu_1();
					Status = 0;
					LC = 0;
				}
				if (Status == 2 && LC != 2)
					PrintF(LC);
			}
			else
				if (Status == 2)
				{
					if (temp == 8)
					{
						if (S[HT].size() > 0)
						{
							int n = S[HT].size();
							S[HT].erase(n - 1, 1);
							PrintS(S[HT], HT);
						}
						else
						{
							if (HT == 1)
							{
								int n = Operator.size();
								Operator.erase(n - 1, 1);
								PrintD(Operator, 0);
								if (Operator == "")
									HT = 0;
							}
						}
					}
					if (temp == 27)
					{
						if (LC == 3)
							Menu_3();
						else
							Menu_2();
						Status = 1;
						S[0] = "";
						S[1] = "";
						Operator = "";
						Coefficient = 0;
					}
					if (temp == 'T')
					{
						system("cls");
						DrawBoard(Max_Height, Max_Width);
						S[0] = "";
						S[1] = "";
						Operator = "";
						HT = 0;
						Str = "";
					}
					if (Operator == "<" || Operator == ">" || Operator == "R" || Operator == "RO")
					{
						if (Operator == "<")
							if (temp == '<')
							{
								Operator = "<<";
								PrintD(Operator, 0);
							}
						if (Operator == ">")
							if (temp == '>')
							{
								Operator = ">>";
								PrintD(Operator, 0);
							}
						if (Operator == "R")
							if (temp == 'O')
							{
								Operator = "RO";
								PrintD(Operator, 0);
							}
						if (Operator == "RO")
						{
							if (temp == 'L')
							{
								Operator = "ROL";
								PrintD(Operator, 0);
							}
							if (temp == 'R')
							{
								Operator = "ROR";
								PrintD(Operator, 0);
							}
						}
					}
					else
					{
						if (Coefficient == 2 && (Str != "" || HT == 0 || (HT == 1 && LC == 2 && Operator != ">>" && Operator != "<<" && Operator != "ROR" && Operator != "ROL")))
						{
							if (temp == 48 || temp == 49)
							{
								if (Str != "")
								{
									system("cls");
									DrawBoard(Max_Height, Max_Width);
									S[0] = "";
									S[1] = "";
									Operator = "";
									HT = 0;
									Str = "";
									if (Status == 2 && LC != 2)
										PrintF(LC);
								}
								if (S[HT].size() < 128)
								{
									S[HT] = S[HT] + char(temp);
									PrintS(S[HT], HT);
								}
							}
						}
						if ((Coefficient == 10 || Operator == ">>" || Operator == "<<" || Operator == "ROR" || Operator == "ROL") && (Str != "" || HT == 0 || (HT == 1 && LC == 2)))
						{
							if (temp >= 48 && temp <= 57)
							{
								if (Str != "")
								{
									system("cls");
									DrawBoard(Max_Height, Max_Width);
									S[0] = "";
									S[1] = "";
									Operator = "";
									HT = 0;
									Str = "";
									if (Status == 2 && LC != 2)
										PrintF(LC);
								}
								if ((Operator != ">>" && Operator != "<<" && Operator != "ROR" && Operator != "ROL") || HT == 0 || S[HT].size() < 3)
								{
									S[HT] = S[HT] + char(temp);
									PrintS(S[HT], HT);
								}
							}
							if (temp == '.' && LC == 3)
							{
								if (Str != "")
								{
									system("cls");
									DrawBoard(Max_Height, Max_Width);
									S[0] = "";
									S[1] = "";
									HT = 0;
									Operator = "";
									Str = "";
								}
								int n = 0;
								for (int u = 0; u < S[HT].size(); u++)
									if (S[HT][u] == '.')
										n = 1;
								if (n == 0)
								{
									if (S[HT].size() == 0)
										S[HT] = "0";
									S[HT] = S[HT] + char(temp);
									PrintS(S[HT], HT);
								}
							}
						}
						if (Coefficient == 16 && (Str != "" || HT == 0 || (HT == 1 && LC == 2)))
						{
							if ((temp >= 48 && temp <= 57) || (temp >= 65 && temp <= 70))
							{
								if (Str != "")
								{
									system("cls");
									DrawBoard(Max_Height, Max_Width);
									S[0] = "";
									S[1] = "";
									Operator = "";
									Str = "";
									HT = 0;
									if (Status == 2 && LC != 2)
										PrintF(LC);
								}
								if (S[HT].size() < 32)
								{
									S[HT] = S[HT] + char(temp);
									PrintS(S[HT], HT);
								}
							}
						}
						if (LC != 2)
						{
							if (temp == 'X')
							{
								Str = ConvertBases(S[0], Coefficient, 2, LC == 3);
								PrintS(Str, 1);
							}
							if (temp == 'Y')
							{
								Str = ConvertBases(S[0], Coefficient, 10, LC == 3);
								PrintS(Str, 1);
							}
							if (temp == 'Z' && LC != 3)
							{
								Str = ConvertBases(S[0], Coefficient, 16, 0);
								PrintS(Str, 1);
							}
						}
						if (temp == '-')
						{
							if (S[HT] == "" && Coefficient == 10)
							{
								S[HT] = "-";
								PrintS(S[HT], HT);
							}
							else
								if (LC == 2)
								{
									if (Str != "")
									{
										system("cls");
										DrawBoard(Max_Height, Max_Width);
										S[0] = Str;
										S[1] = "";
										Str = "";
										Operator = "";
										PrintS(S[0], 0);
										Operator = char(temp);
										HT = 1;
										PrintD(Operator, 0);
									}
									else
									{
										if (S[0] == "")
										{
											S[0] = "0";
											PrintS(S[0], 0);
										}
										else 
											if (Operator == "")
											{
												Operator = char(temp);
												HT = 1;
												PrintD(Operator, 0);
											}
									}
								}
						}
						if (LC == 2)
						{
							if ((Operator == "" && HT == 0 && S[0] != "-") || Str != "")
								if (temp == '+' || temp == '*' || temp == '/' || temp == 'R' || temp == '>' || temp == '<' || temp == '|' || temp == '&' || temp == '^')
								{
									if (Str != "")
									{
										system("cls");
										DrawBoard(Max_Height, Max_Width);
										S[0] = Str;
										S[1] = "";
										Str = "";
										Operator = "";
										PrintS(S[0], 0);
										Operator = char(temp);
										HT = 1;
										PrintD(Operator, 0);
									}
									else
									{
										if (S[0] == "")
										{
											S[0] = "0";
											PrintS(S[0], 0);
										}
										Operator = char(temp);
										HT = 1;
										PrintD(Operator, 0);
									}
								}
							if (temp == '~' && HT == 0)
							{
								Str = NOT(S[0], Coefficient);
								PrintS(Str, 1);
							}
							if ((temp == '=' || temp == 13) && HT == 1 && S[1] != "" && S[1] != "-")
							{
								PrintD("=", 1);
								Str = "0";
								if (Operator == "+")
								{
									//Str = S[0]+S[1];
									Str = Add(S[0], S[1], Coefficient);
								}
								if (Operator == "-")
								{
									//Str=S[0]-S[1];
									Str = Subtract(S[0], S[1], Coefficient);
								}
								if (Operator == "*")
								{
									//Str=S[0]*S[1];
									Str = Multiply(S[0], S[1], Coefficient);
								}
								if (Operator == "/")
								{
									//Str = S[0]/S[1];
									Str = Divide(S[0], S[1], Coefficient);
								}
								if (Operator == "&")
								{
									//Str = S[0]&S[1];
									Str = AND(S[0], S[1], Coefficient);
								}
								if (Operator == "^")
								{
									//Str = S[0]^S[1];
									Str = XOR(S[0], S[1], Coefficient);
								}
								if (Operator == "|")
								{
									//Str = S[0]|S[1];
									Str = OR(S[0], S[1], Coefficient);
								}
								if (Operator == ">>")
								{
									//Str = S[0] >> ToInt(S[1]);
									Str = ShiftRight(S[0], stoi(S[1]), Coefficient);
								}
								if (Operator == "<<")
								{
									//Str = S[0] << ToInt(S[1]);
									Str = ShiftLeft(S[0], stoi(S[1]), Coefficient);
								}
								if (Operator == "ROR")
								{
									//Str = ROR(S[0],ToInt(S[1]));
									Str = ROR(S[0], stoi(S[1]), Coefficient);
								}
								if (Operator == "ROL")
								{
									//Str = ROL(S[0],ToInt(S[1]));
									Str = ROL(S[0], stoi(S[1]), Coefficient);
								}

								PrintS(Str, 2);
							}
						}
					}
				}
	}
}