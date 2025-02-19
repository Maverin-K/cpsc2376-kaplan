#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    std::vector<int> nums{ 234,128,362,944,425,153,678,332 };


    /*std::for_each(nums.begin(), nums.end(), [](int& x) {x *= 2});
    std::for_each(nums.begin(),nums.end(),[](int&x){std::out << x << ", "});*/

    /*for (auto& num : nums)
    {
        num *= 2;
    }
    for (auto& num : nums) std::cout << num << ", ";*/


    /*int x{54};
    //[&] will capture outside variables other than a & b
    auto f = [&](int a, int b) { return a/10%10<b/10%10;};
    std::sort(nums.begin(), nums.end(),f);

    for(auto it{nums.begin()};it!=nums.end();it++)
    {
        std::cout << *it << ", ";
    }*/
    
    return 0;
}

