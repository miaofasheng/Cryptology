#include<iostream>
using namespace std;
char result[26];
int main()
{
    char Text[1000];
    int a = 1;

    //zhihuanbiao();
    cout << "请输入你的文本" << endl;
    cin.getline(Text, 1000);
    cout << "替换后的结果" << endl;
    for (int i = 0; int(Text[i]) != 0; i++)
    {
        if (Text[i] == 'C')
            cout << 'E';
        else if (Text[i] == 'S')
            cout << 'T';
        else if (Text[i] == 'H')
            cout << 'B';
        else if (Text[i] == 'I')
            cout << 'H';
        else if (Text[i] == 'N')
            cout << 'A';
        else if (Text[i] == 'M')
            cout << 'O';
        else if (Text[i] == 'P')
            cout << 'R';
        else if (Text[i] == 'Q')
            cout << 'M';
        else if (Text[i] == 'V')
            cout << 'W';
        else if (Text[i] == 'J')
            cout << 'I';
        else if (Text[i] == 'E')
            cout << 'G';
        else if (Text[i] == 'R')
            cout << 'S';
        else if (Text[i] == 'Z')
            cout << 'U';
        else if (Text[i] == 'G')
            cout << 'C';
        else if (Text[i] == 'B')
            cout << 'N';
        else if (Text[i] == 'A')
            cout << 'L';
        else if (Text[i] == 'X')
            cout << 'P';
        else if (Text[i] == 'T')
            cout << 'V';
        else if (Text[i] == 'O')
            cout << 'Z';

        else
            cout << Text[i];
    }
    cout << endl;
    system("pause");
}