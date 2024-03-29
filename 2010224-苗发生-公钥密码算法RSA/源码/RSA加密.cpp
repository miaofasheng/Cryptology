#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "bigint.h"
#include <ctime>
using namespace std;
BigInt e;  //e为公开钥
BigInt d;  //d为秘密钥，即e模t的乘法逆元
BigInt y;  //y用于参与扩展欧几里得运算，存储t模e的乘法逆元
BigInt t;
BigInt p; //大素数
BigInt q; //大素数
BigInt c; //密文
BigInt m; //明文
BigInt M;  //解密得明文
BigInt n;
//对大奇数n进行RabinMiller检测
bool RabinMiller(const BigInt& n)
{
	BigInt r, a, y;
	unsigned int s, j;
	r = n - 1;
	s = 0;
	while (!(r.element[0]&1))
	{
		s++;
		r >> 1;
	}
	//随机产生一个小于N-1的检测数a
	a.Randomsmall();
	//y = a的r次幂模n
	y = Mod(a, r, n);

	//检测J=2至J<S轮
	if ((!(y == 1)) && (!(y == (n - 1))))
	{
		j = 1;
		while ((j <= s - 1) && (!(y == (n - 1))))
		{
			y = (y * y) % n;
			if (y == 1)
				return false;
			j++;
		}
		if (!(y == (n - 1)))
			return false;
	}
	return true;
}



//产生一个素数
BigInt GeneratePrime()
{
	BigInt n;
	int circle = 0;

	//无限次循环，不断产生素数，直到i==5时（通过五轮RabinMiller测试）才会跳出while循环
	while (circle < 5)
	{
		Genbigodd(n);
		circle = 0;
		//进行五轮RABINMILLER测试,五轮全部通过则素数合格
		for (; circle < 5; circle++)
		{
			if (!RabinMiller(n))
			{
				break;
			}
		}
	}
	n.Print();
	return n;
}

//求两个大数的最大公约数,采用辗转相除法
BigInt Gcd(const BigInt& m, const BigInt& n)
{
	if (n == 0)
		return m;
	else
		return Gcd(n, m % n);
}

//用扩展欧几里德算法求乘法模逆
BigInt ExtendedGcd(const BigInt& a, const BigInt& b, BigInt& x, BigInt& y)
{
	BigInt t, d;
	//如果一个操作数为零则无法进行除法运算
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	d = ExtendedGcd(b, a % b, x, y);
	t = x;
	x = y;
	y = t - ((a / b) * y);
	return d;
}
BigInt Gene(BigInt t)
{
	BigInt temp;
	while (true)
	{
		//产生与t互质的e
		e.Random();
		while (!(Gcd(e, t) == 1))
		{
			e.Random();
		}
		temp = ExtendedGcd(e, t, d, y);
		temp = (e * d) % t;
		if (temp == 1)
			break;

		//否则重新生成e
	}
	return e;
}
int main()
{
	int length;
	bool flag;
	do {
		cout << "生成大素数p" << endl;
		//产生大素数
		p = GeneratePrime();
		p.Print();
		cout << endl;
		cout << "生成大素数q" << endl;
		//产生大素数
		q = GeneratePrime();
		q.Print();
		cout << endl;
		n = p * q;
	    t = (p - 1) * (q - 1);
		e=Gene(t);
		cout << "公钥e为： " << endl;
		//16进制形式显示
		e.Print();
		cout << endl;
		cout << "明文如下： " << endl;
		m.Input();
		m.Print();
		//16进制形式显示
		cout << "用秘密钥e对m加密,得到密文分组c " << endl;
		c = Mod(m, e, n);
		cout << "密文分组c为：" << endl;
		//16进制形式显示
		c.Print();
		cout << "您是否继续进行加密操作？如果是则输入1，否则输入0" << endl;
		cin >> flag;
	} while (flag);
	return 0;
}