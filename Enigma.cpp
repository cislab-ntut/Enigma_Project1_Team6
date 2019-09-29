#include <iostream>
#include <string>
#include <time.h>
#define N 4
#define SIZE 10395
using namespace std;

int cc = 0;
int a[N];
int group[SIZE][12];

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

int PB_testCase[12];

int change1[6] = { -1, -1,-1 ,-1 ,-1 ,-1 }, change2[6] = { -1,-1 ,-1 ,-1 ,-1 ,-1 };

int input, output;

//選盤子
void set(int plate[], int starting[])
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			if (plate[i] == 1)
			{
				rotor1.current = starting[i];
				rotor[i] = rotor1;
			}
			else if (plate[i] == 2)
			{
				rotor2.current = starting[i];
				rotor[i] = rotor2;
			}
			else if (plate[i] == 3)
			{
				rotor3.current = starting[i];
				rotor[i] = rotor3;
			}
			else if (plate[i] == 4)
			{
				rotor4.current = starting[i];
				rotor[i] = rotor4;
			}
			else
			{
				rotor5.current = starting[i];
				rotor[i] = rotor5;
			}
		}
	}
}

void shift()
{
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
}

//加密
void encrypt()
{
	/*------------------------------------對應插座------------------------------------------*/
	for (int i = 0; i < 6; i++)
	{
		if (input == change1[i])
			input = change2[i];
		else if (input == change2[i])
			input = change1[i];
	}

	shift();

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
		if (output == change1[i])
			output = change2[i];
		else if (output == change2[i])
			output = change1[i];
	}
}

//測試
void test()
{
	for (int index = 0; index < 10395; index++)
	{
		for (int ch = 0; ch < 12; ch += 2)
		{
			change1[ch / 2] = PB_testCase[group[index][ch]];
			change2[ch / 2] = PB_testCase[group[index][ch + 1]];
		}

		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!大家改這裡喔!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		int plate[3] = { 1, 3, 4 };
		int starting[3];
		for (int i = 0; i < 26; i++)
		{
			starting[0] = i;
			for (int j = 0; j < 26; j++)
			{
				starting[1] = j;
				for (int k = 0; k < 26; k++)
				{
					starting[2] = k;
					set(plate, starting);

					string user_input = "IPQHUGCXZM";
					string answer = "HEILHITLER";
					string user_output = "";

					for (int m = 0; m < 138; m++)
						shift();

					for (int n = 0; n < 10; n++)
					{
						input = int(user_input[n]) - 'A';
						encrypt();
						output += 'A';
						if (output != answer[n])
							break;
						user_output += (char)output;
					}
					if (user_output == answer)
					{
						cout << "--------------------------------------------------------\n";
						cout << "Rotor：" << plate[0] << "\t" << plate[1] << "\t" << plate[2] << endl;
						cout << "Starting：" << char(starting[0] + 'A') << "\t" << char(starting[1] + 'A') << "\t" << char(starting[2] + 'A') << endl;
						cout << "Plug Board：";
						for (int i = 0; i < 6; i++)
						{
							cout << char(change1[i] + 'A') << char(change2[i] + 'A') << "\t";
						}
						cout << endl;
						cout << "--------------------------------------------------------\n";
						system("pause");
					}
				}
			}
		}
	}
}

void swap(int i, int offset) {

	int temp;

	temp = a[offset];

	a[offset] = a[i];

	a[i] = temp;

}

void printnum(int pre[]) {
	int i;
	for (i = 0; i < 8; i++)
		group[cc][i] = pre[i];

	for (i = 0; i < N; i++)
		group[cc][i + 8] = a[i];
	cc++;
}

void perm(int pre[], int offset)
{
	int i;

	if (offset == N / 2)
	{  // BaseCase
		printnum(pre);
		return;
	}
	else
	{
		for (i = offset; i < N; i++)
		{
			swap(i, offset);//交換字首
			perm(pre, offset + 1);//遞迴
			swap(i, offset);//將字首換回來，繼續做前一次排列
		}
	}
}

void go(int pre[], bool* b)
{
	int index = 0;
	for (int i = 0; i < 12; i++)
		if (b[i])
			a[index++] = i;
	perm(pre, 1);
}

void get_group()
{
	for (int i = 10; i >= 0; i--)
	{
		for (int j = 10; j >= 0; j--)
		{
			if (i != j)
			{
				for (int k = 10; k >= 0; k--)
				{
					if (k != i && k != j)
					{
						for (int l = 10; l >= 0; l--)
						{
							if (l != i && l != j && l != k)
							{
								for (int m = 10; m >= 0; m--)
								{
									if (m != i && m != j && m != k && m != l)
									{
										for (int n = 10; n >= 0; n--)
										{
											if (n != i && n != j && n != k && n != l && n != m)
											{
												for (int o = 10; o >= 0; o--)
												{
													if (o != i && o != j && o != k && o != l && o != m && o != n)
													{
														bool b[12] = { true,true,true,true,true,true,true,true,true,true,true,false };
														b[i] = false;
														b[j] = false;
														b[k] = false;
														b[l] = false;
														b[m] = false;
														b[n] = false;
														b[o] = false;

														int pre[8] = { 11,i,j,k,l,m,n,o };
														go(pre, b);
													}
												}
												break;
											}
										}
									}
								}
								break;
							}
						}
					}
				}
				break;
			}
		}
	}
}

void Combi(int text[], int reqLen, int s, int currLen, bool check[], int l)
{
	if (currLen > reqLen)
		return;
	else if (currLen == reqLen) {
		int index = 0;
		for (int i = 0; i < l; i++) {
			if (check[i] == true) {
				PB_testCase[index++] = text[i];
			}
		}
		test();
		return;
	}
	if (s == l) {
		return;
	}
	check[s] = true;
	Combi(text, reqLen, s + 1, currLen + 1, check, l);
	check[s] = false;
	Combi(text, reqLen, s + 1, currLen, check, l);
}


int main() {
	get_group();
	int text[26];
	bool check[26];
	for (int i = 0; i < 26; ++i)
	{
		text[i] = i;
		check[i] = false;
	}
	Combi(text, 12, 0, 0, check, 26);

	return 0;
}
