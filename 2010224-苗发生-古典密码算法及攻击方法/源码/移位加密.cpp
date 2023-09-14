#include<iostream>
using namespace std;
void Shiftencryption()
{
    char Text[1000];
    int shift = 0;
    cout << "请输入您要加密的明文" << endl;
    cin.getline(Text, 1000);
    cout << "请输入偏移位数（右移）:";
    cin >> shift;
    shift %= 26;
    int after = 0;
    int shift_65 = shift + 65;
    int shift_90 = shift + 90;
    int shift_97 = shift + 97;
    int shift_122 = shift + 122;
    for (int i = 0; int(Text[i]) != 0; i++)
    {
        //计算移位后的ascii
        after = int(Text[i]) + shift;
        //判断移位后的
        if (after >= shift_65 && after <= 90)
        {
            Text[i] = char(after);
        }
        if (after > 90 && after <= shift_90)
        {
            Text[i] = char(after - 26);
        }
        if (after >= shift_97 && after <= 122)
        {
            Text[i] = char(after);
        }
        if (after > 122 && after <= shift_122)
        {
            Text[i] = char(after - 26);
        }
    }
    cout << "移位后的密文为：" << endl << Text << endl;
    cout << "------------------------------------" << endl;
}
int main()
{
    Shiftencryption();
    system("pause");
}