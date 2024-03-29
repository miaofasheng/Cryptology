#pragma once
#include <iostream>
#include <stdlib.h> 
using namespace std;
const int MAXSIZE = 64;
static int prime[] = { 3,    5,    7,    11,   13,   17,   19,   23,   29,   31,
37,   41,   43,   47,   53,   59,   61,   67,   71,   73,
79,   83,   89,   97,   101,  103,  107,  109,  113,  127,
131,  137,  139,  149,  151,  157,  163,  167,  173,  179,
181,  191,  193,  197,  199,  211,  223,  227,  229,  233,
239,  241,  251,  257,  263,  269,  271,  277,  281,  283,
293,  307,  311,  313,  317,  331,  337,  347,  349,  353,
359,  367,  373,  379,  383,  389,  397,  401,  409,  419,
421,  431,  433,  439,  443,  449,  457,  461,  463,  467,
479,  487,  491,  499,  503,  509,  521,  523,  541,  547,
557,  563,  569,  571,  577,  587,  593,  599,  601,  607,
613,  617,  619,  631,  641,  643,  647,  653,  659,  661,
673,  677,  683,  691,  701,  709,  719,  727,  733,  739,
743,  751,  757,  761,  769,  773,  787,  797,  809,  811,
821,  823,  827,  829,  839,  853,  857,  859,  863,  877,
881,  883,  887,  907,  911,  919,  929,  937,  941,  947,
953,  967,  971,  977,  983,  991,  997,  1009, 1013, 1019,
1021, 1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069, 1087,
1091, 1093, 1097, 1103, 1109, 1117, 1123, 1129, 1151, 1153,
1163, 1171, 1181, 1187, 1193, 1201, 1213, 1217, 1223, 1229,
1231, 1237, 1249, 1259, 1277, 1279, 1283, 1289, 1291, 1297,
1301, 1303, 1307, 1319, 1321, 1327, 1361, 1367, 1373, 1381,
1399, 1409, 1423, 1427, 1429, 1433, 1439, 1447, 1451, 1453,
1459, 1471, 1481, 1483, 1487, 1489, 1493, 1499, 1511, 1523,
1531, 1543, 1549, 1553, 1559, 1567, 1571, 1579, 1583, 1597,
1601, 1607, 1609, 1613, 1619, 1621, 1627, 1637, 1657, 1663,
1667, 1669, 1693, 1697, 1699, 1709, 1721, 1723, 1733, 1741,
1747, 1753, 1759, 1777, 1783, 1787, 1789, 1801, 1811, 1823,
1831, 1847, 1861, 1867, 1871, 1873, 1877, 1879, 1889, 1901,
1907, 1913, 1931, 1933, 1949, 1951, 1973, 1979, 1987, 1993,
1997, 1999, 2003, 2011, 2017, 2027, 2029, 2039, 2053, 2063,
2069, 2081, 2083, 2087, 2089, 2099, 2111, 2113, 2129, 2131,
2137, 2141, 2143, 2153, 2161, 2179, 2203, 2207, 2213, 2221,
2237, 2239, 2243, 2251, 2267, 2269, 2273, 2281, 2287, 2293,
2297, 2309, 2311, 2333, 2339, 2341, 2347, 2351, 2357, 2371,
2377, 2381, 2383, 2389, 2393, 2399, 2411, 2417, 2423, 2437,
2441, 2447, 2459, 2467, 2473, 2477, 2503, 2521, 2531, 2539,
2543, 2549, 2551, 2557, 2579, 2591, 2593, 2609, 2617, 2621,
2633, 2647, 2657, 2659, 2663, 2671, 2677, 2683, 2687, 2689,
2693, 2699, 2707, 2711, 2713, 2719, 2729, 2731, 2741, 2749,
2753, 2767, 2777, 2789, 2791, 2797, 2801, 2803, 2819, 2833,
2837, 2843, 2851, 2857, 2861, 2879, 2887, 2897, 2903, 2909,
2917, 2927, 2939, 2953, 2957, 2963, 2969, 2971, 2999, 3001,
3011, 3019, 3023, 3037, 3041, 3049, 3061, 3067, 3079, 3083,
3089, 3109, 3119, 3121, 3137, 3163, 3167, 3169, 3181, 3187,
3191, 3203, 3209, 3217, 3221, 3229, 3251, 3253, 3257, 3259,
3271, 3299, 3301, 3307, 3313, 3319, 3323, 3329, 3331, 3343,
3347, 3359, 3361, 3371, 3373, 3389, 3391, 3407, 3413, 3433,
3449, 3457, 3461, 3463, 3467, 3469, 3491, 3499, 3511, 3517,
3527, 3529, 3533, 3539, 3541, 3547, 3557, 3559, 3571, 3581,
3583, 3593, 3607, 3613, 3617, 3623, 3631, 3637, 3643, 3659,
3671, 3673, 3677, 3691, 3697, 3701, 3709, 3719, 3727, 3733,
3739, 3761, 3767, 3769, 3779, 3793, 3797, 3803, 3821, 3823,
3833, 3847, 3851, 3853, 3863, 3877, 3881, 3889, 3907, 3911,
3917, 3919, 3923, 3929, 3931, 3943, 3947, 3967, 3989, 4001,
4003, 4007, 4013, 4019, 4021, 4027, 4049, 4051, 4057, 4073,
4079, 4091, 4093, 4099, 4111, 4127, 4129, 4133, 4139, 4153,
4157, 4159, 4177, 4201, 4211, 4217, 4219, 4229, 4231, 4241,
4243, 4253, 4259, 4261, 4271, 4273, 4283, 4289, 4297, 4327,
4337, 4339, 4349, 4357, 4363, 4373, 4391, 4397, 4409, 4421,
4423, 4441, 4447, 4451, 4457, 4463, 4481, 4483, 4493, 4507,
4513, 4517, 4519, 4523, 4547, 4549, 4561, 4567, 4583, 4591,
4597, 4603, 4621, 4637, 4639, 4643, 4649, 4651, 4657, 4663,
4673, 4679, 4691, 4703, 4721, 4723, 4729, 4733, 4751, 4759,
4783, 4787, 4789, 4793, 4799, 4801, 4813, 4817, 4831, 4861,
4871, 4877, 4889, 4903, 4909, 4919, 4931, 4933, 4937, 4943,
4951, 4957, 4967, 4969, 4973, 4987, 4993, 4999 };
class BigInt {
	friend bool operator< (const BigInt&, const BigInt&);
	friend bool operator> (const BigInt&, const BigInt&);
	friend bool operator<= (const BigInt&, const int&);
	friend bool operator== (const BigInt&, const BigInt&);
	friend bool operator== (const BigInt&, const int&);
	friend BigInt operator+ (const BigInt&, const BigInt&);
	friend BigInt operator- (const BigInt&, const BigInt&);
	friend BigInt operator- (const BigInt&, const int&);
	friend BigInt operator* (const BigInt&, const BigInt&);
	friend BigInt operator% (const BigInt&, const BigInt&);
	friend BigInt operator/ (const BigInt&, const BigInt&);
	friend BigInt operator* (const BigInt&, const unsigned int&);
	friend BigInt Mod(const BigInt&, const BigInt&, const BigInt&);
	friend void Genbigodd(BigInt& n);
public:
	BigInt();
	BigInt(const int&);
	BigInt(const BigInt&);
	void operator= (const BigInt&);
	void operator= (const int& a) { Putzero(); element[0] = a; }
	void operator>> (const int&);
	inline int GetLength() const;   
	void Putzero();  
	void Random(); 
	void Randomsmall();  
	void Input();
	void Print() const;
public:
	unsigned int element[MAXSIZE];
	bool sign;
};


BigInt Mod(const BigInt& num, const BigInt& p, const BigInt& m)
{
	BigInt temp = p;
	BigInt base = num % m;
	BigInt result(1);

	//检测指数p的二进制形式的每一位
	while (!(temp <= 1))
	{
		if (temp.element[0] & 1)
		{
			result = (result * base) % m;
		}
		base = (base * base) % m;
		temp >> 1;
	}
	return (base * result) % m;
}

void Genbigodd(BigInt& num)
{
	int i = 0;
	BigInt divisor;
	const int length = sizeof(prime) / sizeof(int);
	while (i != length)
	{
		//生成大奇数
		num.Random();
		while (!(num.element[0] & 1))
			num.Random();
		i = 0;
		for (; i < length; i++)
		{
			divisor = prime[i];
			if ((num % divisor) == 0)
				break;
		}
	}
}

BigInt::BigInt()
{
	for (int i = 0; i < MAXSIZE; i++)
		element[i] = 0;
	sign = true;
}
//用int初始化大数
BigInt::BigInt(const int& num)
{
	for (int i = 0; i < MAXSIZE; i++)
		element[i] = 0;
	element[0] = num;
	if (num >= 0)
		sign = true;
	else
		sign = false;
}

//用大数给大数赋值
BigInt::BigInt(const BigInt& num)
{
	for (int i = 0; i < MAXSIZE; i++)
		element[i] = num.element[i];
	sign = num.sign;
}

void BigInt::operator= (const BigInt& input)
{
	for (int i = 0; i < MAXSIZE; i++)
		element[i] = input.element[i];
	sign = input.sign;
}

//比较两个大数的大小,a<b,返回真,否则返回假
bool operator< (const BigInt& left, const BigInt& right)
{
	for (int i = MAXSIZE - 1; i > 0; i--)
	{
		if (left.element[i] < right.element[i])
			return true;
		if (left.element[i] > right.element[i])
			return false;
	}
	return left.element[0] < right.element[0];
}

//比较两个大数的大小,a>b,返回真,否则返回假
bool operator> (const BigInt& left, const BigInt& right)
{
	for (int i = MAXSIZE - 1; i >= 0; i--)
	{
		if (left.element[i] > right.element[i])
			return true;
		if (left.element[i] < right.element[i])
			return false;
	}
	return false;
}

bool operator== (const BigInt& left, const BigInt& right)
{
	for (int i = 0; i < MAXSIZE; i++)
		if (left.element[i] != right.element[i])
			return false;
	return true;
}

bool operator== (const BigInt& left, const int& right)
{
	for (int i = 1; i < left.GetLength(); i++)
		if (left.element[i] != 0)
			return false;
	return left.element[0] == right;
}

//计算两个大数的和,采用竖式相加法
BigInt operator+ (const BigInt& left, const BigInt& right)
{
	BigInt result;
	unsigned __int64 sum;
	unsigned int temp = 0, sub;
	int length = (left.GetLength() >= right.GetLength() ? left.GetLength() : right.GetLength());
	//当两数符号相同时,进行加法运算
	if (left.sign == right.sign)
	{
		//每一位进行竖式相加
		for (int i = 0; i < length; i++)
		{
			sum = (unsigned __int64)left.element[i] + right.element[i] + temp;
			result.element[i] = (unsigned int)sum;
			//sum的高位为进位
			temp = (sum >> 32);
		}

		result.sign = left.sign;
		return result;
	}
	//两数符号不同时,进行减法运算
	else
	{
		BigInt tempa, tempb;

		//取出a,b中绝对值较大的作为被减数
		if (left < right)
		{
			tempa = right;
			tempb = left;
		}
		else
		{
			tempa = left;
			tempb = right;
		}

		//每一位进行竖式减
		for (int i = 0; i < length; i++)
		{
			sub = tempb.element[i] + temp;
			if (tempa.element[i] >= sub)
			{
				result.element[i] = tempa.element[i] - sub;
				temp = 0;
			}
			else
			{
				//借位减
				result.element[i] = (unsigned __int64)tempa.element[i] + (1 << 32) - sub;
				temp = 1;
			}
		}
		result.sign = tempa.sign;
		return result;
	}
}

BigInt operator- (const BigInt& left, const BigInt& right)
{
	BigInt result;
	//64位数据,存放每两位数相加的临时和
	unsigned __int64 sum;
	unsigned int temp = 0, sub;
	//符号相同时,进行减法运算
	if (left.sign == right.sign)
	{
		BigInt tempa, tempb;

		//取出a,b中绝对值较大的作为被减数
		if (left < right)
		{
			tempa = right;
			tempb = left;
			tempa.sign = !tempa.sign;
		}
		else
		{
			tempa = left;
			tempb = right;
		}
		//每一位进行竖式减
		for (int i = 0; i < MAXSIZE; i++)
		{
			sub = tempb.element[i] + temp;
			if (tempa.element[i] >= sub)
			{
				result.element[i] = tempa.element[i] - sub;
				temp = 0;
			}
			else
			{
				//借位减
				result.element[i] = (unsigned __int64)tempa.element[i] + (1 << 32) - sub;
				temp = 1;
			}
		}
		result.sign = tempa.sign;
		return result;
	}
	//两数符号不同时,进行加法运算
	else
	{
		//每一位进行竖式相加
		for (int i = 0; i < MAXSIZE; i++)
		{
			sum = (unsigned __int64)left.element[i] + right.element[i] + temp;
			result.element[i] = (unsigned int)sum;
			//sum的高位为进位
			temp = (sum >> 32);
		}
		result.sign = left.sign;
		return result;
	}
}

//大数减一个int数
BigInt operator- (const BigInt& left, const int& right)
{
	BigInt temp(right);
	BigInt result = left - temp;
	return result;
}

//大数乘以一个INT数
BigInt operator* (const BigInt& left, const unsigned int& right)
{
	BigInt result;
	//存放B乘以A的每一位的临时积
	unsigned __int64 sum;
	//存放进位
	unsigned int carry = 0;

	for (int i = 0; i < MAXSIZE; i++)
	{
		sum = ((unsigned __int64)left.element[i]) * right + carry;
		result.element[i] = (unsigned int)sum;
		//进位在SUM的高位中
		carry = (sum >> 32);
	}
	result.sign = left.sign;
	return result;
}

//大数相乘,采用竖式乘
BigInt operator* (const BigInt& left, const BigInt& right)
{
	//last存放竖式上一行的积,temp存放当前行的积
	BigInt result, last, temp;
	//sum存放当前行带进位的积
	unsigned __int64 sum;
	//存放进位
	unsigned int carry;

	//进行竖式乘
	for (int i = 0; i < right.GetLength(); i++)
	{
		carry = 0;
		//B的每一位与A相乘
		for (int j = 0; j < left.GetLength() + 1; j++)
		{
			sum = ((unsigned __int64)left.element[j]) * (right.element[i]) + carry;
			if ((i + j) < MAXSIZE)
				temp.element[i + j] = (unsigned int)sum;
			carry = (sum >> 32);
		}
		result = (temp + last);
		last = result;
		temp.Putzero();
	}
	//判断积的符号
	if (left.sign == right.sign)
		result.sign = true;
	else
		result.sign = false;

	return result;
}

//大数除,采用试商除法,采用二分查找法优化
BigInt operator/ (const BigInt& left, const BigInt& right)
{
	unsigned int mul, low, high;
	BigInt dividend, quotient, sub, subsequent;
	int lengtha = left.GetLength(), lengthb = right.GetLength();

	//如果被除数小于除数,直接返回0
	if (left < right)
	{
		if (left.sign == right.sign)
			quotient.sign = true;
		else
			quotient.sign = false;
		return quotient;
	}

	int i;
	for (i = 0; i < lengthb; i++)
		dividend.element[i] = left.element[lengtha - lengthb + i];

	for (i = lengtha - lengthb; i >= 0; i--)
	{
		//如果被除数小于除数,再往后补位
		if (dividend < right)
		{
			for (int j = lengthb; j > 0; j--)
				dividend.element[j] = dividend.element[j - 1];
			dividend.element[0] = left.element[i - 1];
			continue;
		}

		low = 0;
		high = 0xffffffff;

		//二分查找法查找试商
		while (low < high)
		{
			mul = (((unsigned __int64)high) + low) / 2;
			sub = (right * mul);
			subsequent = (right * (mul + 1));

			if (((sub < dividend) && (subsequent > dividend)) || (sub == dividend))
				break;
			if (subsequent == dividend)
			{
				mul++;
				sub = subsequent;
				break;
			}
			if ((sub < dividend) && (subsequent < dividend))
			{
				low = mul;
				continue;
			}
			if ((sub > dividend) && (subsequent > dividend))
			{
				high = mul;
				continue;
			}

		}

		//试商结果保存到商中去
		quotient.element[i] = mul;
		dividend = dividend - sub;
		if ((i - 1) >= 0)
		{
			for (int j = lengthb; j > 0; j--)
				dividend.element[j] = dividend.element[j - 1];
			dividend.element[0] = left.element[i - 1];
		}
	}

	//判断商的符号
	if (left.sign == right.sign)
		quotient.sign = true;
	else
		quotient.sign = false;
	return quotient;
}

//大数求模运算,与除法运算类似
BigInt operator% (const BigInt& left, const BigInt& b)
{
	unsigned int mul, low, high;
	BigInt dividend, quotient, sub, subsequent;
	int lengtha = left.GetLength(), lengthb = b.GetLength();

	//如果被除数小于除数,返回被除数为模
	if (left < b)
	{
		dividend = left;
		dividend.sign = left.sign;
		return dividend;
	}

	//进行除法运算
	int i;
	for (i = 0; i < lengthb; i++)
		dividend.element[i] = left.element[lengtha - lengthb + i];

	for (i = lengtha - lengthb; i >= 0; i--)
	{
		if (dividend < b)
		{
			for (int j = lengthb; j > 0; j--)
				dividend.element[j] = dividend.element[j - 1];
			dividend.element[0] = left.element[i - 1];
			continue;
		}

		low = 0;
		high = 0xffffffff;

		while (low <= high)
		{
			mul = (((unsigned __int64)high) + low) / 2;
			sub = (b * mul);
			subsequent = (b * (mul + 1));

			if (((sub < dividend) && (subsequent > dividend)) || (sub == dividend))
				break;
			if (subsequent == dividend)
			{
				mul++;
				sub = subsequent;
				break;
			}
			if ((sub < dividend) && (subsequent < dividend))
			{
				low = mul;
				continue;
			}
			if ((sub > dividend) && (subsequent > dividend))
			{
				high = mul;
				continue;
			}
		}

		quotient.element[i] = mul;
		dividend = dividend - sub;
		if ((i - 1) >= 0)
		{
			for (int j = lengthb; j > 0; j--)
				dividend.element[j] = dividend.element[j - 1];
			dividend.element[0] = left.element[i - 1];
		}
	}

	//临时被除数即为所求模
	dividend.sign = left.sign;
	return dividend;
}

//产生一个随机大数,大数的LENGTH为SIZE的1/4,是为了防止运算时的溢出
void BigInt::Random()
{
	for (int i = 0; i < (MAXSIZE / 4); i++)
		//由于RAND()最大只能产生0X7FFF的数,为了能产生32位的随机数,需要
		//3次RAND()操作
		element[i] = (rand() << 17) + (rand() << 2) + rand() % 4;
}

void BigInt::Input()
{
	for (int i = 0; i < (MAXSIZE / 4); i++)
		//由于RAND()最大只能产生0X7FFF的数,为了能产生32位的随机数,需要
		//3次RAND()操作
		element[i] = (rand() << 17) + (rand() << 2) + rand() % 4;
};



//产生一个较小的随机大数,大数的LENGTH为SIZE的1/8
void BigInt::Randomsmall()
{
	for (int i = 0; i < (MAXSIZE / 16); i++)
		element[i] = (rand() << 17) + (rand() << 2) + rand() % 4;
}

//将大数以16进制显示到屏幕上
void BigInt::Print() const
{
	unsigned int temp, result;
	unsigned int an = 0xf0000000;

	for (int i = GetLength() - 1; i >= 0; i--)
	{
		temp = element[i];
		//大数的每一位数字转换成16进制输出
		for (int j = 0; j < 8; j++)
		{
			result = temp & an;
			result = (result >> 28);
			temp = (temp << 4);
			if (result >= 0 && result <= 9)
				cout << result;
			else
			{
				switch (result)
				{
				case 10:
					cout << "a";
					break;
				case 11:
					cout << "b";
					break;
				case 12:
					cout << "c";
					break;
				case 13:
					cout << "d";
					break;
				case 14:
					cout << "e";
					break;
				case 15:
					cout << "f";
					break;
				}
			}
		}
		cout << " ";
		if (i == GetLength() / 2)
			cout << endl;
	}
	cout << endl;
}
//大数置0
void BigInt::Putzero()
{
	for (int i = 0; i < MAXSIZE; i++)
		element[i] = 0;
}

//返回大数长度
inline int BigInt::GetLength() const
{
	int length = MAXSIZE;
	for (int i = MAXSIZE - 1; i >= 0; i--)
	{
		//第一位不为0即为LENGTH
		if (element[i] == 0)
			length--;
		else
			break;
	}
	return length;
}

//重载移位操作符,向右移N位
void BigInt::operator>> (const int& a)
{
	unsigned int bit;
	element[0] = (element[0] >> a);
	for (int i = 1; i < GetLength(); i++)
	{
		//先将每一位的低位移到BIT中
		bit = element[i] & 1;
		//再把BIT移到上一位的高位中
		bit = bit << (32 - a);;
		element[i - 1] = element[i - 1] | bit;
		element[i] = (element[i] >> a);
	}
}

//判断大数和一个INT的大小
bool operator<= (const BigInt& a, const int& b)
{
	for (int i = 1; i < a.GetLength(); i++)
	{
		if (a.element[i] != 0)
			return false;
	}
	if (a.element[0] <= b)
		return true;
	else
		return false;
}