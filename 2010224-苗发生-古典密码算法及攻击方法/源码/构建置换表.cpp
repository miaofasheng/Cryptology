#include<iostream>
using namespace std;
char result[26];
void zhihuanbiao()
{
    char Text[1000];
    cout << "请输入你的密钥" << endl;
    cin.getline(Text, 1000);
    bool flag[26] = { 0 };
    int k = 0;

    for (int i = 0; int(Text[i]) != 0; i++)
    {
        if (int(Text[i]) >= 97 && int(Text[i]) <= 122)
        {
            Text[i] -= 32;
        }
        if (int(Text[i]) >= 65 && int(Text[i]) <= 90)
        {
            int num = int(Text[i]) - 'A';
            if (flag[num] != true)
            {
                result[k] = Text[i];
                k++;
            }
            flag[num] = true;
        }
    }

    for (int i = 0; i < 26; i++)
    {
        if (flag[i] != true)
        {
            result[k] = char(int('A') + i);
            k++;
        }
        flag[i] = true;
    }
    for (int i = 0; i < 26; i++)
    {
        cout << char('A' + i) << ":" << result[i] << endl;;
    }
}

int main()
{
    zhihuanbiao();
    system("pause");
    return 0;
}