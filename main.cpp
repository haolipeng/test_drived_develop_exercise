//
// Created by Administrator on 2020\1\31 0031.
//

#include "gmock/gmock.h"
#include "Soundex.h"

int main(int argc, char** argv){
    //初始化测试库
    testing::InitGoogleMock(&argc, argv);

#if 0
    Soundex soundex;
    std::string x = soundex.encode("A");
    return 0;
#else
    return RUN_ALL_TESTS();
#endif
}