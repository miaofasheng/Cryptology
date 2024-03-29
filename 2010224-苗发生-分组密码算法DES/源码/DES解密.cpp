#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
#include "des.h"
using namespace std;
bitset<64> key;
bitset<48> subKey[16];
//进行左移

bitset<28> leftShift(bitset<28> key, int shift)
{
	bitset<28> temp = key;
	for (int i = 27; i >= 0; --i)//左右两部分密钥各位28位
	{
		if (i - shift < 0)
			key[i] = temp[i - shift + 28];
		else
			key[i] = temp[i - shift];
	}
	return key;
}


void GenSubkey()
{
	bitset<28> left;
	bitset<28> right;
	//经过PC1_table的置换选择后，已经去除了奇偶校验位
	bitset<56> firstKey;
	for (int i = 0; i < 56; i++)
	{
		firstKey[55 - i] = key[64 - PC1_table[i]];
	}
	// 生成子密钥
	for (int index = 0; index < 16; index++)
	{
		// 分为左右两部分
		// 前28位与后28位
		for (int i = 28; i < 56; i++)
		{
			left[i - 28] = firstKey[i];
		}
		for (int i = 0; i < 28; i++)
		{
			right[i] = firstKey[i];
		}
		// 左移
		left = leftShift(left, LeftShift[index]);
		right = leftShift(right, LeftShift[index]);
		for (int i = 28; i < 56; i++)
		{
			firstKey[i] = left[i - 28];
		}
		for (int i = 0; i < 28; i++)
		{
			firstKey[i] = right[i];
		}
		bitset<48> zipKey;
		// 压缩置换，56位到48位
		for (int i = 0; i < 48; i++)
		{
			zipKey[47 - i] = firstKey[56 - PC2_table[i]];
		}
		subKey[index] = zipKey;
	}
}


//f 函数是多个置换函数和替代函数的组合函数，它将32位比特的输入变换为32位的输出
bitset<32> f(bitset<32> R, bitset<48> k)
{
	int temp = 0;
	bitset<48> expandR;
	for (int i = 0; i < 48; ++i)
		expandR[47 - i] = R[32 - Extend_table[i]];
	expandR = expandR ^ k;
	bitset<32> result;
	for (int i = 0; i < 48; i = i + 6)
	{
		int row = expandR[47 - i] * 2 + expandR[47 - i - 5];
		int col = expandR[47 - i - 1] * 8 + expandR[47 - i - 2] * 4 + expandR[47 - i - 3] * 2 + expandR[47 - i - 4];
		int num = S_BOX[i / 6][row][col];
		bitset<4> binary(num);
		result[31 - temp] = binary[3];
		result[31 - temp - 1] = binary[2];
		result[31 - temp - 2] = binary[1];
		result[31 - temp - 3] = binary[0];
		temp += 4;
	}
	// 第四步：P-置换

	bitset<32> tmp = result;
	for (int i = 0; i < 32; ++i)
		result[31 - i] = tmp[32 - Perm_table[i]];
	return result;
}



bitset<64> Encryption(bitset<64>& plaintext)
{
	bitset<64> ciphertext;
	bitset<64> firstInput;
	bitset<32> left;
	bitset<32> right;

	// 初始置换IP
	for (int i = 0; i < 64; i++)
		firstInput[63 - i] = plaintext[64 - InitPerm[i]];
	// 一分为二
	for (int i = 32; i < 64; i++)
		left[i - 32] = firstInput[i];
	for (int i = 0; i < 32; i++)
		right[i] = firstInput[i];
		
	// 迭代
	for (int round = 0; round < 16; round++)
	{
		bitset<32> nextHigh;
		nextHigh = right;
		right = left ^ f(right, subKey[round]);
		left = nextHigh;
	}
	// 合并注意高位和低位发生了调换
	for (int i = 0; i < 32; i++)
	{
		ciphertext[i] = left[i];
		ciphertext[i + 32] = right[i];
	}
	// 结尾置换IP-1
	firstInput = ciphertext;
	for (int i = 0; i < 64; i++)
		ciphertext[63 - i] = firstInput[64 - InvPerm[i]];
	return ciphertext;
}

/**
 *  DES解密
 */
bitset<64> Decryption(bitset<64>& ciphertext)
{
	bitset<64> plaintext;
	bitset<64> firstInput;
	bitset<32> left;
	bitset<32> right;

	// 初始置换IP
	for (int i = 0; i < 64; i++)
		firstInput[63 - i] = ciphertext[64 - InitPerm[i]];
	// 一分为二
	for (int i = 32; i < 64; i++)
	{
		left[i - 32] = firstInput[i];
		right[i-32] = firstInput[i-32];
	}
	// 迭代
	bitset<32> nextHigh;
	for (int round = 0; round < 16; round++)
	{
		nextHigh = right;
		right = left ^ f(right, subKey[15 - round]);
		left = nextHigh;
	}
	// 合并注意高位和低位发生了调换
	for (int i = 0; i < 32; i++)
	{
		plaintext[i] = left[i];
		plaintext[i + 32] = right[i];
	}
	// 结尾置换IP-1
	firstInput = plaintext;
	for (int i = 0; i < 64; i++)
		plaintext[63 - i] = firstInput[64 - InvPerm[i]];
	return plaintext;
}

int main() {
	bitset<64> cybertext=0;
	bitset<64> plaintext=0;

	string result="0x0000000000000000";//这个值是随意设置的仅仅起到初始化的作用
	bool flag;
	while (true)
	{
		string a;
		string b;
		string c;
		cout << "请输入你要用DES算法解密的密文" << endl;
		cin >> a;
		cout << "请输入你的密钥" << endl;
		cin >> b;
		HextoBit(a, plaintext);
		//HextoBit(c, cybertext);
		HextoBit(b, key);
		// 生成16个子密钥
		GenSubkey();
		for (int i = 0; i < 16; i++)
		{
			cout << "第" << i+1 << "个子密钥为" << subKey[i] << endl;
		}
		cout << "*************************************"<<endl;
		cybertext = Decryption(plaintext);
		BittoHex(cybertext, result);
		cout << "解密结果（明文）：" << result<<endl;
		cout << "*************************************" << endl;
		cout << "您是否要继续解密，输入0则继续进行DES解密，输入1则退出程序"<<endl;
		cin >> flag;
		if (flag == 0)
			continue;
		else
			break;
	}
	system("pause");
}

