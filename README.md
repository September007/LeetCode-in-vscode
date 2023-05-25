# LeetCode-in-VSCode


## Config

```bash
git pull git@github.com:September007/LeetCode-in-vscode.git
cd LeetCode-in-vscode
git submodule update --init --recursive

```
然后硬编码你的 leetcode.workspaceFolder 到custom.cmake
示例：
**`vscode settings.json`**
```json
// 
{
    //...
    "leetcode.defaultLanguage": "cpp",
    "leetcode.hideSolved": true,
    "leetcode.endpoint": "leetcode-cn",
    "leetcode.workspaceFolder": "D:/CODE/LeetCode-in-vscode",
    "clang-format.style": "Chromium"
}
``` 
对应 **`${CMAKE_CURRENT_LIST_DIR}/custom.cmake`**
```cmake

set(LEETCODE_PROBLEM_SOURCES "D:/CODE/LeetCode-in-vscode"  CACHE STRING "")
message(STATUS "hardcode LEETCODE_PROBLEM_SOURCES:${LEETCODE_PROBLEM_SOURCES}")
```
## Debug
提供两种本地调试的方法
我以第一题举个例子
如下是 LeetCode vscode插件生成的带标注的源文件
```cpp
/*
 * @lc app=leetcode.cn id=1 lang=cpp
 *
 * [1] 两数之和
 */

// @lc code=start
class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        vector<int> answer(2);
        int         size = nums.size();
        for (int i = 0; i < size - 1; ++i)
            for (int j = i + 1; j < size; ++j)
                if (nums[i] + nums[j] == target)
                {
                    answer[0] = i, answer[1] = j;
                    return answer;
                }
        return answer;
    }
};
// @lc code=end

```
## 第一种：内嵌的调试代码
### 基本使用
将其修改成如下，然后调试目标 "1"
```cpp
/*
 * @lc app=leetcode.cn id=1 lang=cpp
 *
 * [1] 两数之和
 */
#ifdef LOCAL
#    include <pch.h>
using namespace std;
#else
#    define TEST(nl, nr) void nl##nr()
#    define EXPECT_EQ(l, r)
#    define EXPECT_TRUE(l)
#endif
// @lc code=start
class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        vector<int> answer(2);
        int         size = nums.size();
        for (int i = 0; i < size - 1; ++i)
            for (int j = i + 1; j < size; ++j)
                if (nums[i] + nums[j] == target)
                {
                    answer[0] = i, answer[1] = j;
                    return answer;
                }
        return answer;
    }
};
// @lc code=end

TEST(test, t0)
{
    Solution s;
    auto     v = std::vector<int>{2, 7, 11, 15};
    auto     ans = s.twoSum(v, 9);
    auto     exp = std::vector<int>{0, 1};
    EXPECT_EQ(ans, exp);
}
```
### 重写main
todo

## 第二种：嵌入源文件
### 基本使用 
调试目标 "1-"
无需修改用以提交的源文件
打开CMakeLists开关
```cmake
option(ENABLE_REFER "生成 embeded/* 中的引用型的调试目标，其将包含提交文件" ON)
```
触发cmake 重新configure
在embeded文件夹下出现 1-.cpp如下（自动生成)
在其中编写你的测试用例即可
```cpp
/* 此文件从template.cpp */
#include <bits/stdc++.h>
#include <gtest/gtest.h>
#include <string>
using namespace std;

/* utils */
#include <util/util.h>
using namespace LT_UTIL; /* 这可能与一些类型不兼容，那么你需要重写类型，然后 using yourtype; */

#undef LOCAL/* 关闭引入的源文件中的local内容 */
#include <../1.两数之和.cpp>


TEST(test,default)
{
    Solution s;
}

int main(int argc,char**argv){
    
  vector<char *> vargv = {argv, argv + argc};
  char no_catch_excepetion[]={"--gtest_catch_exceptions=0"};
  vargv.push_back(no_catch_excepetion);
  argc++;
  ::testing::InitGoogleTest(&argc, vargv.data());
  return RUN_ALL_TESTS();
}

```

## utils 库的使用


## tips

### cmake commands
*in vscode*: 
after install the [cmake-tools plugins](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) then you have multi commands to use
invoke the commands selector by { ctrl+shift+p then type 'cmake' }|{ctrl+p then type '>cmake' } 
* Delete Cache and Reconfigure
* Set Build Target
* Set Debug Target

you can trigger Cmake to configure by save (by ctrl+s when focus on CMakeLists.txt), if you can not, you can try this method show above
