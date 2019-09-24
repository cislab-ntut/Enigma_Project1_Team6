#include <iostream>
#include <string>
#include <time.h>
using namespace std;

struct Rotor
{
	string a;
	int pin, current;
};

Rotor rotor1 = { "EKMFLGDQVZNTOWYHXUSPAIBRCJ", 'Q' - 'A', 'H' - 'A' };
Rotor rotor2 = { "AJDKSIRUXBLHWTMCQGZNPYFVOE", 'E' - 'A', 'D' - 'A' };
Rotor rotor3 = { "BDFHJLCPRTXVZNYEIWGAKMUSQO", 'V' - 'A', 'X' - 'A' };
Rotor rotor4 = { "ESOVPZJAYQUIRHXLNFTGKDCMWB", 'J' - 'A', 'R' - 'A' };
Rotor rotor5 = { "VZBRGITYUPSDNHLXAWMJQOFECK", 'Z' - 'A', 'H' - 'A' };

Rotor rotor[3];

string reflector = "YRUHQSLDPXNGOKMIEBFZCWVJAT";

int change1[6] = { -1, -1,-1 ,-1 ,-1 ,-1 }, change2[6] = { -1,-1 ,-1 ,-1 ,-1 ,-1 };

int input, output;

//選盤子
void set()
{
	int plate[3];
	string starting[3];
	do {
		cout << "輸入第一個盤子(1~5): ";
		cin >> plate[0];
		cout << "輸入第一個起始位置(A~Z): ";
		cin >> starting[0];
		cout << endl;
	} while (plate[0] < 1 || plate[0] > 5);
	do {
		cout << "輸入第二個盤子(1~5): ";
		cin >> plate[1];
		cout << "輸入第二個起始位置(A~Z): ";
		cin >> starting[1];
		cout << endl;
	} while (plate[1] < 1 || plate[1] > 5 || plate[1] == plate[0]);
	do {
		cout << "輸入第三個盤子(1~5): ";
		cin >> plate[2];
		cout << "輸入第三個起始位置(A~Z): ";
		cin >> starting[2];
		cout << endl;
	} while (plate[2] < 1 || plate[2] > 5 || plate[2] == plate[0] || plate[2] == plate[1]);
	
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			if (plate[i] == 1)
			{
				rotor1.current = starting[i][0] - 'A';
				rotor[i] = rotor1;
			}
			else if (plate[i] == 2)
			{
				rotor2.current = starting[i][0] - 'A';
				rotor[i] = rotor2;
			}
			else if (plate[i] == 3)
			{
				rotor3.current = starting[i][0] - 'A';
				rotor[i] = rotor3;
			}
			else if (plate[i] == 4)
			{
				rotor4.current = starting[i][0] - 'A';
				rotor[i] = rotor4;
			}
			else
			{
				rotor5.current = starting[i][0] - 'A';
				rotor[i] = rotor5;
			}
		}
	}

	string temp;
	for (int i = 0; i < 6; i++)
	{
		cout << "請輸入第" << i + 1 << "組交換(輸入0結束):";
		cin >> temp;
		if (temp == "0")
			break;
		change1[i] = temp[0] - 'A';
		change2[i] = temp[1] - 'A';
	}

	/*
	//隨機產生change，從 0~26， 0為不交換
	srand(time(NULL));
	change1 = rand() % 27;
	if (change1 == 0)
		change2 = 0;
	else
		do {
			change2 = rand() % 27;
		} while (change2 == 0);
		//cout << change1 << "  " << change2 << endl;
	*/
}

//加密
void encrypt()
{
	/*------------------------------------對應插座------------------------------------------*/
	for (int i = 0; i < 6; i++)
	{
		if (change1 < 0 || change2 < 0)
			break;
		if (input == change1[i])
			input = change2[i];
		else if (input == change2[i])
			input = change1[i];
	}

	/*------------------------------------設定加密方法------------------------------------------*/
	//如果第二個指針碰到藍藍，第二、三個藍藍轉一個
	if (rotor[1].current == rotor[1].pin)
	{
		rotor[1].current = (rotor[1].current + 1) % 26;
		rotor[2].current = (rotor[2].current + 1) % 26;
	}

	//如果第一個指針碰到藍藍，第二個藍藍轉一個
	if (rotor[0].current == rotor[0].pin)
		rotor[1].current = (rotor[1].current + 1) % 26;

	//第一個藍藍轉一個
	rotor[0].current = (rotor[0].current + 1) % 26;

	/*------------------------------------找到加密文字------------------------------------------*/
	//第一外圈的字母本人
	int outRotor1 = (rotor[0].current + input) % 26;
	//第一內圈的字母對應位置(第二外圈的字母對應位置)
	int inRotor1 = rotor[0].a[outRotor1] - 'A' - rotor[0].current;
	if (inRotor1 < 0)
		inRotor1 += 26;

	//第二外圈的字母本人
	int outRotor2 = (rotor[1].current + inRotor1) % 26;
	//第二內圈的字母對應位置(第三外圈的字母對應位置)
	int inRotor2 = rotor[1].a[outRotor2] - 'A' - rotor[1].current;
	if (inRotor2 < 0)
		inRotor2 += 26;

	//第三外圈的字母本人
	int outRotor3 = (rotor[2].current + inRotor2) % 26;
	//第三內圈的字母對應位置(反射圈的字母本人及對應位置)
	int inRotor3 = rotor[2].a[outRotor3] - 'A' - rotor[2].current;
	if (inRotor3 < 0)
		inRotor3 += 26;

	//反射的字母本人及對應位置(第三內圈的字母對應位置)
	int refl = reflector[inRotor3] - 'A';

	//反射到第三內圈的字母本人
	inRotor3 = (rotor[2].current + refl) % 26;
	//反射第三外圈的字母對應位置(第二內圈的字母對應位置)
	for (int i = 0; i <= 25; i++)
	{
		if (inRotor3 == rotor[2].a[i] - 'A')
		{
			outRotor3 = (26 - rotor[2].current + i) % 26;
			break;
		}
	}

	//反射到第二內圈的字母本人
	inRotor2 = (rotor[1].current + outRotor3) % 26;
	//反射第二外圈的字母對應位置(第一內圈的字母對應位置)
	for (int i = 0; i <= 25; i++)
	{
		if (inRotor2 == rotor[1].a[i] - 'A')
		{
			outRotor2 = (26 - rotor[1].current + i) % 26;
			break;
		}
	}

	//反射到第一內圈的字母本人
	inRotor1 = (rotor[0].current + outRotor2) % 26;
	//反射第一外圈的字母對應位置(插座字母對應位置)
	for (int i = 0; i <= 25; i++)
	{
		if (inRotor1 == rotor[0].a[i] - 'A')
		{
			outRotor1 = (26 - rotor[0].current + i) % 26;
			break;
		}
	}

	output = outRotor1;

	/*------------------------------------對應插座------------------------------------------*/
	for (int i = 0; i < 6; i++)
	{
		if (change1 < 0 || change2 < 0)
			break;
		if (output == change1[i])
			output = change2[i];
		else if (output == change2[i])
			output = change1[i];
	}
}

//測試
void test()
{

}


int main() {
	set();

	string user_input;
	string user_output = "";

	//user輸入一大串字母
	cout << endl;
	cout << "輸入大寫字母:";
	cin >> user_input;

	for (int i = 0; i < user_input.size(); i++)
	{
		input = int(user_input[i]) - 'A';
		encrypt();
		output += 'A';
		user_output += (char)output;
	}
	cout << endl;
	cout << user_output;
	cout << endl;

	return 0;
}
