#include <iostream>
#include <string>
#include <cctype>

using std::cin;
using std::cout;
using std::string;

int main()
{
    string ori, res;
    std::getline(cin, ori);

    for (char &chara : ori)
    {
        if(!ispunct(chara))
            res += chara;
    }
    cout << res;

    return 0;
}
