#include <iostream>
#include<string>
#include<string.h>
using namespace std;
class MD5 {
public:
	bool OVER;
	unsigned int Link[4];
	unsigned int Count[2];
	unsigned char Buffer[64];
	unsigned char Digest[16];
	static  unsigned char Padding[64];
	static  char hex[16];
	MD5(string& message);
	unsigned char* GetDigest();
	string getstring();
	void Init(unsigned char* input, int len);
	void zip(unsigned char block[64]);
	void Encryption(unsigned int* input, unsigned char* output, int length);
};
unsigned int F(unsigned int& x, unsigned int& y, unsigned int& z)
{
	return (x & y) | (~x & z);
}
unsigned int G(unsigned int& x, unsigned int& y, unsigned int& z)
{
	return (x & z) | (y & ~z);
}
unsigned int H(unsigned int& x, unsigned int& y, unsigned int& z)
{
	return x ^ y ^ z;
}
unsigned int I(unsigned int& x, unsigned int& y, unsigned int& z)
{
	return y ^ (x | ~z);
}
unsigned int Left_shift(unsigned int& num, unsigned int& n)
{
	return (num << n) | (num >> (32 - n));
}
void Round_One(unsigned int& a, unsigned int& b, unsigned int& c, unsigned int& d, unsigned int& x, unsigned int s, unsigned int ac)
{
	a += F(b, c, d) + x + ac;
	a = Left_shift(a, s);
	a += b;
}
void Round_Two(unsigned int& a, unsigned int& b, unsigned int& c, unsigned int& d, unsigned int& x, unsigned int s, unsigned int ac)
{
	a += G(b, c, d) + x + ac;
	a = Left_shift(a, s);
	a += b;
}
void Round_Three(unsigned int& a, unsigned int& b, unsigned int& c, unsigned int& d, unsigned int& x, unsigned int s, unsigned int ac)
{
	a += H(b, c, d) + x + ac;
	a = Left_shift(a, s);
	a += b;
}
void Round_Four(unsigned int& a, unsigned int& b, unsigned int& c, unsigned int& d, unsigned int& x, unsigned int s, unsigned int ac)
{
	a += I(b, c, d) + x + ac;
	a = Left_shift(a, s);
	a += b;
}
//左循环移位位数
int s[4][4] = { 7,12,17,22,5,9,14,20,4,11,16,23,6,10,15,21 };
//填充
unsigned char MD5::Padding[64] = { 0x80 };
//提前存储16进制的每个数
char MD5::hex[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b','c', 'd', 'e', 'f' };
MD5::MD5(string& txt) {
	OVER = false;
	Count[0] = Count[1] = 0;
	Link[0] = 0x67452301;
	Link[1] = 0xefcdab89;
	Link[2] = 0x98badcfe;
	Link[3] = 0x10325476;
	Init((unsigned char*)txt.c_str(), txt.length());
}
unsigned char* MD5::GetDigest() {
	if (!OVER) {
		OVER = true;
		unsigned char Bits[8];
		unsigned int oldState[4];
		unsigned int oldCount[2];
		int nowlength, waitlength;
		memcpy(oldState, Link, 16);
		memcpy(oldCount, Count, 8);
		Encryption(Count, Bits, 8);
		nowlength = (unsigned int)((Count[0] >> 3) & 0x3f);
		waitlength = (nowlength < 56) ? (56 - nowlength) : (120 - nowlength);
		Init(Padding, waitlength);
		nowlength = (unsigned int)((Count[0] >> 3) & 0x3f);
		memcpy(&Buffer[nowlength], Bits, 8);
		zip(Buffer);
		Encryption(Link, Digest, 16);
		memcpy(Link, oldState, 16);
		memcpy(Count, oldCount, 8);
	}
	return Digest;
}

void MD5::Init(unsigned char* input, int len) {
	unsigned int i, nowlength, waitlength;
	OVER = false;
	nowlength = (unsigned int)((Count[0] >> 3) & 0x3f);
	Count[0] += (unsigned int)len << 3;
	if ((Count[0]) < ((unsigned int)len << 3)) {
		Count[1] += 1;
	}
	Count[1] += ((unsigned int)len >> 29);
	waitlength = 64 - nowlength;
	if (len >= waitlength) {
		memcpy(&Buffer[nowlength], input, waitlength);
		zip(Buffer);
		for (i = waitlength; i + 63 < len; i += 64) {
			zip(&input[i]);
		}
		nowlength = 0;
	}
	else {
		i = 0;
	}
	memcpy(&Buffer[nowlength], &input[i], len - i);
}

void MD5::zip(unsigned char block[64]) {
	unsigned int a = Link[0], b = Link[1], c = Link[2], d = Link[3], x[16];
	for (int i = 0, j = 0; j < 64; ++i, j += 4) {
		x[i] = ((unsigned int)block[j]) | (((unsigned int)block[j + 1]) << 8) |
			(((unsigned int)block[j + 2]) << 16) | (((unsigned int)block[j + 3]) << 24);
	}
	Round_One(a, b, c, d, x[0], s[0][0], 0xd76aa478);
	Round_One(d, a, b, c, x[1], s[0][1], 0xe8c7b756);
	Round_One(c, d, a, b, x[2], s[0][2], 0x242070db);
	Round_One(b, c, d, a, x[3], s[0][3], 0xc1bdceee);
	Round_One(a, b, c, d, x[4], s[0][0], 0xf57c0faf);
	Round_One(d, a, b, c, x[5], s[0][1], 0x4787c62a);
	Round_One(c, d, a, b, x[6], s[0][2], 0xa8304613);
	Round_One(b, c, d, a, x[7], s[0][3], 0xfd469501);
	Round_One(a, b, c, d, x[8], s[0][0], 0x698098d8);
	Round_One(d, a, b, c, x[9], s[0][1], 0x8b44f7af);
	Round_One(c, d, a, b, x[10], s[0][2], 0xffff5bb1);
	Round_One(b, c, d, a, x[11], s[0][3], 0x895cd7be);
	Round_One(a, b, c, d, x[12], s[0][0], 0x6b901122);
	Round_One(d, a, b, c, x[13], s[0][1], 0xfd987193);
	Round_One(c, d, a, b, x[14], s[0][2], 0xa679438e);
	Round_One(b, c, d, a, x[15], s[0][3], 0x49b40821);
	Round_Two(a, b, c, d, x[1], s[1][0], 0xf61e2562);
	Round_Two(d, a, b, c, x[6], s[1][1], 0xc040b340);
	Round_Two(c, d, a, b, x[11], s[1][2], 0x265e5a51);
	Round_Two(b, c, d, a, x[0], s[1][3], 0xe9b6c7aa);
	Round_Two(a, b, c, d, x[5], s[1][0], 0xd62f105d);
	Round_Two(d, a, b, c, x[10], s[1][1], 0x2441453);
	Round_Two(c, d, a, b, x[15], s[1][2], 0xd8a1e681);
	Round_Two(b, c, d, a, x[4], s[1][3], 0xe7d3fbc8);
	Round_Two(a, b, c, d, x[9], s[1][0], 0x21e1cde6);
	Round_Two(d, a, b, c, x[14], s[1][1], 0xc33707d6);
	Round_Two(c, d, a, b, x[3], s[1][2], 0xf4d50d87);
	Round_Two(b, c, d, a, x[8], s[1][3], 0x455a14ed);
	Round_Two(a, b, c, d, x[13], s[1][0], 0xa9e3e905);
	Round_Two(d, a, b, c, x[2], s[1][1], 0xfcefa3f8);
	Round_Two(c, d, a, b, x[7], s[1][2], 0x676f02d9);
	Round_Two(b, c, d, a, x[12], s[1][3], 0x8d2a4c8a);
	Round_Three(a, b, c, d, x[5], s[2][0], 0xfffa3942);
	Round_Three(d, a, b, c, x[8], s[2][1], 0x8771f681);
	Round_Three(c, d, a, b, x[11], s[2][2], 0x6d9d6122);
	Round_Three(b, c, d, a, x[14], s[2][3], 0xfde5380c);
	Round_Three(a, b, c, d, x[1], s[2][0], 0xa4beea44);
	Round_Three(d, a, b, c, x[4], s[2][1], 0x4bdecfa9);
	Round_Three(c, d, a, b, x[7], s[2][2], 0xf6bb4b60);
	Round_Three(b, c, d, a, x[10], s[2][3], 0xbebfbc70);
	Round_Three(a, b, c, d, x[13], s[2][0], 0x289b7ec6);
	Round_Three(d, a, b, c, x[0], s[2][1], 0xeaa127fa);
	Round_Three(c, d, a, b, x[3], s[2][2], 0xd4ef3085);
	Round_Three(b, c, d, a, x[6], s[2][3], 0x4881d05);
	Round_Three(a, b, c, d, x[9], s[2][0], 0xd9d4d039);
	Round_Three(d, a, b, c, x[12], s[2][1], 0xe6db99e5);
	Round_Three(c, d, a, b, x[15], s[2][2], 0x1fa27cf8);
	Round_Three(b, c, d, a, x[2], s[2][3], 0xc4ac5665);
	Round_Four(a, b, c, d, x[0], s[3][0], 0xf4292244);
	Round_Four(d, a, b, c, x[7], s[3][1], 0x432aff97);
	Round_Four(c, d, a, b, x[14], s[3][2], 0xab9423a7);
	Round_Four(b, c, d, a, x[5], s[3][3], 0xfc93a039);
	Round_Four(a, b, c, d, x[12], s[3][0], 0x655b59c3);
	Round_Four(d, a, b, c, x[3], s[3][1], 0x8f0ccc92);
	Round_Four(c, d, a, b, x[10], s[3][2], 0xffeff47d);
	Round_Four(b, c, d, a, x[1], s[3][3], 0x85845dd1);
	Round_Four(a, b, c, d, x[8], s[3][0], 0x6fa87e4f);
	Round_Four(d, a, b, c, x[15], s[3][1], 0xfe2ce6e0);
	Round_Four(c, d, a, b, x[6], s[3][2], 0xa3014314);
	Round_Four(b, c, d, a, x[13], s[3][3], 0x4e0811a1);
	Round_Four(a, b, c, d, x[4], s[3][0], 0xf7537e82);
	Round_Four(d, a, b, c, x[11], s[3][1], 0xbd3af235);
	Round_Four(c, d, a, b, x[2], s[3][2], 0x2ad7d2bb);
	Round_Four(b, c, d, a, x[9], s[3][3], 0xeb86d391);
	Link[0] += a;
	Link[1] += b;
	Link[2] += c;
	Link[3] += d;
}

void MD5::Encryption(unsigned int* Input_txt, unsigned char* Result, int Len) {
	for (int i = 0, j = 0; j < Len; ++i, j += 4) {
		Result[j] = (unsigned char)(Input_txt[i] & 0xff);
		Result[j + 1] = (unsigned char)((Input_txt[i] >> 8) & 0xff);
		Result[j + 2] = (unsigned char)((Input_txt[i] >> 16) & 0xff);
		Result[j + 3] = (unsigned char)((Input_txt[i] >> 24) & 0xff);
	}
}

string MD5::getstring() {
	unsigned char* digest_ = GetDigest();
	string str;
	for (int i = 0; i < 16; ++i) {
		int t = digest_[i];
		int a = t / 16;
		int b = t % 16;
		str.append(1, hex[a]);
		str.append(1, hex[b]);
	}
	return str;
}

void Print(string& txt) {
	string md5 = MD5(txt).getstring();
	cout << "MD5：" << endl;
	//cout << "0x";
	for (int i = 0; i < 32; i++) {
		if (i % 2 == 0 && i != 0&&i!=16)
			cout << "  ";
		if (i % 2 == 0) {
			cout << "0x";
		}
		cout << md5[i];
		if (i == 15)
			cout << endl;
	}
	cout << endl;
	return;
}


int main() {
	bool flag=true;
	int num = 0;
	do {
		if (num != 0)
		{
			cout << "您是否继续进行加密，如果是，请输入1，否则输入0退出程序！" << endl;
			cin >> flag;
			num++;
		}
		string txt;
		cout << "请输入要加密的字符串：" << endl;
		getline(cin, txt);
		Print(txt);
		cout << "==============================================" << endl;
	} while (flag);
}