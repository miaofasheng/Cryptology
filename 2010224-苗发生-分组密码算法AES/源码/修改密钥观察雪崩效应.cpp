#include<iostream>
#include<bitset>
#include"AES.h"
using namespace std;
//密钥扩展
void keyExpansion(int Key[4][4], int W[11][4][4])
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; j++)
		{
			W[0][i][j] = Key[j][i];   //key读进来的时候是竖着存的，现在要横着存

		}
	}
	for (int i = 1; i < 11; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			int temp[4];
			if (j == 0)    //即mod4==0
			{
				//先进行字节为单位的循环左移位
				temp[0] = W[i - 1][3][1];
				temp[1] = W[i - 1][3][2];
				temp[2] = W[i - 1][3][3];
				temp[3] = W[i - 1][3][0];
				for (int k = 0; k < 4; ++k)
				{
					int m = temp[k];
					int row = m / 16;
					int col = m % 16;
					temp[k] = S[row][col];
					if (k == 0)
					{
						//与轮常量异或
						temp[k] = temp[k] ^ rC[i - 1];
					}
				}
			}
			else     //mod4!=0
			{
				temp[0] = W[i][j - 1][0];
				temp[1] = W[i][j - 1][1];
				temp[2] = W[i][j - 1][2];
				temp[3] = W[i][j - 1][3];
			}
			//mod!=4时，下面的结果为：W[i]=W[i-4]⨁W[i-1] 
			//mod==4时，下面的结果为：W[i-4]⨁T(W[i-1]) 
			for (int x = 0; x < 4; x++)
			{
				W[i][j][x] = W[i - 1][j][x] ^ temp[x];
			}
		}
	}
}

void byteSub(int in[4][4], int type)//解密type=0，加密type=1
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int temp = in[i][j];
			int row = temp / 16;
			int col = temp % 16;
			if (type == 1)
			{
				in[i][j] = S[row][col];
			}
			if (type == 0)
			{
				in[i][j] = rS[row][col];
			}
		}
	}
}

// 行移位，Nb=4时用三角的方式实现移位结果
void shiftRow(int txt[4][4], int type) //解密type=0，加密type=1
{
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < row; col++)
		{
			if (type == 1)
			{
				int temp = txt[row][0];
				txt[row][0] = txt[row][1];
				txt[row][1] = txt[row][2];
				txt[row][2] = txt[row][3];
				txt[row][3] = temp;
			}
			else    //type == 0
			{
				int temp = txt[row][3];
				txt[row][3] = txt[row][2];
				txt[row][2] = txt[row][1];
				txt[row][1] = txt[row][0];
				txt[row][0] = temp;
			}
		}
	}
}

void mixColumn(int txt[4][4], int type)
{
	for (int col = 0; col < 4; col++)
	{
		int t0 = txt[0][col];
		int t1 = txt[1][col];
		int t2 = txt[2][col];
		int t3 = txt[3][col];
		if (type == 1) //加密
		{
			txt[0][col] = Mult(t0, 2) ^ Mult(t1, 3) ^ t2 ^ t3;
			txt[1][col] = t0 ^ Mult(t1, 2) ^ Mult(t2, 3) ^ t3;
			txt[2][col] = t0 ^ t1 ^ Mult(t2, 2) ^ Mult(t3, 3);
			txt[3][col] = Mult(t0, 3) ^ t1 ^ t2 ^ Mult(t3, 2);
		}
		else //type==0 解密
		{
			txt[0][col] = Mult(t0, 14) ^ Mult(t1, 11) ^ Mult(t2, 13) ^ Mult(t3, 9);
			txt[1][col] = Mult(t0, 9) ^ Mult(t1, 14) ^ Mult(t2, 11) ^ Mult(t3, 13);
			txt[2][col] = Mult(t0, 13) ^ Mult(t1, 9) ^ Mult(t2, 14) ^ Mult(t3, 11);
			txt[3][col] = Mult(t0, 11) ^ Mult(t1, 13) ^ Mult(t2, 9) ^ Mult(t3, 14);
		}
	}
}

void addRoundKey(int txt[4][4], int key[4][4])
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; j++)
		{
			txt[i][j] = txt[i][j] ^ key[j][i];
		}
	}
}





int main()
{
	int txt[4][4];
	int txt_new[4][4];
	int key[4][4];
	int key_new[4][4];
	int subKey[11][4][4];
	double ans = 0;  //总的修改位数
	cout << "第一组样例：                    KeySize=128" << endl;
	cout << "明文（16进制）：{00 01 00 01 01 a1 98 af da 78 17 34 86 15 35 66}" << endl;
	cout << "密钥（16进制）：{00 01 20 01 71 01 98 ae da 79 17 14 60 15 35 94}" << endl;
	cout << "密文（16进制）：{6c dd 59 6b 8f 56 42 cb d2 3b 47 98 1a 65 42 2a}" << endl;
	cout << "第二组样例：                    KeySize=128" << endl;
	cout << "明文（16进制）：{32 43 f6 a8 88 5a 30 8d 31 31 98 a2 e0 37 07 34}" << endl;
	cout << "密钥（16进制）：{2b 7e 15 16 28 ae d2 a6 ab f7 15 88 09 cf 4f 3c}" << endl;
	cout << "密文（16进制）：{39 25 84 1d 02 dc 09 fb dc 11 85 97 19 6a 0b 32}" << endl;
	cout << "请输入128位的明文" << endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cin >> (hex) >> txt[j][i];
			txt_new[j][i] = txt[j][i];
		}
	}
	cout << "请输入128位的密钥: " << endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cin >> (hex) >> key[j][i];
			key_new[j][i]= key[j][i];
		}
	}
	keyExpansion(key, subKey);
	addRoundKey(txt, subKey[0]);     //轮密钥加
	for (int i = 1; i <= 10; ++i)
	{
		byteSub(txt, 1);
		shiftRow(txt, 1);
		if (i != 10)      //最后一次计算不需要列混合
		{
			mixColumn(txt, 1);
		}
		addRoundKey(txt, subKey[i]);
	}
	cout << "雪崩测试：修改密钥~" << endl;
	string result = NumtoString(key_new);
	for (int i = 0; i < 128; i++) {
		if (i % 4 == 1)
			cout << endl;
		cout << "密钥第" << (i + 1) << "位改变：";
		if (result[i] == '0')
			result[i] = '1';
		else
			result[i] = '0';
		StringtoNum(key_new, result);
		//======================利用修改后的密钥进行加密==========================
		keyExpansion(key_new, subKey);
		addRoundKey(txt_new, subKey[0]);     //轮密钥加
		for (int i = 1; i <= 10; ++i)
		{
			byteSub(txt_new, 1);
			shiftRow(txt_new, 1);
			if (i != 10)      //最后一次计算不需要列混合
			{
				mixColumn(txt_new, 1);
			}
			addRoundKey(txt_new, subKey[i]);
		}
		//======================利用修改后的密钥进行加密==========================
		int result_text = 0;
		string s_new = NumtoString(txt_new);
		string s = NumtoString(txt);
		for (int i = 0; i < 128; i++) {
			if (s_new[i] == s[i]) {
				result_text++;
			}
		}
		cout << "密文改变";
		cout << (dec) << result_text << "位     ";
		ans += result_text;
		if (result[i] == '0')
			result[i] = '1';
		else
			result[i] = '0';
	}
	cout << endl << "依次修改密钥的每一位，平均每次改变" << ans / 128 << "位" << endl;
	system("pause");
	return 0;
}