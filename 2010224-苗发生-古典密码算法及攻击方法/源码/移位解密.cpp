#include<iostream>
using namespace std;
void Shiftdecryption()
{
    cout << "请输入你要解密的密文" << endl;
    char Text[1000];
    cin.getline(Text, 1000);
    int shift = 25;
    while (shift > 0)
    {
        for (int i = 0; int(Text[i]) != 0; i++)
        {
            if (int(Text[i]) < 65 || (int(Text[i]) > 90 && int(Text[i]) < 97) || int(Text[i]) > 122)continue;
            Text[i] = char(int(Text[i]) + 1);
            if (char(Text[i]) == 91)Text[i] = char(65);
            if (char(Text[i]) == 123)Text[i] = char(97);
        }
        cout << "移" << 26 - shift << "位解密结果：" << Text << endl;
        shift--;
    }
    cout << "***************************************" << endl;
}

int main()
{
    Shiftdecryption();
    system("pause");
}