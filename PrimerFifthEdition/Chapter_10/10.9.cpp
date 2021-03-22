#include <algorithm>
#include <iostream>
#include <vector>

using std::cout;
using std::vector;

void elimDups(vector<int>& nums)
{
    std::sort(nums.begin(), nums.end());
    auto end_unique = std::unique(nums.begin(), nums.end());
    nums.erase(end_unique, nums.end());
}

int main()
{
    vector<int> a{
        9, 7, 6, 7, 8, 2, 3, 2, 5, 1, 1, 10, 5, 6, 7, 2, 3, 4, 5, 1,
    };

    elimDups(a);
    cout << a.size() << '\n';
    for (auto i : a)
        cout << i << ' ';

    return 0;
}
