//
// Created by Administrator on 2020\2\1 0001.
//
#include "gmock/gmock.h"

using namespace testing;

struct SumCase{
    int a,b,expected;
    SumCase(int anA,int anB,int anExcepted)
    :a(anA),b(anB),expected(anExcepted){

    }
};

class Adder{
public:
    static int sum(int a,int b){
        return a+b;
    }
};

//定义衍生自TestWithParam<T>的fixture
class AnAdder : public TestWithParam<SumCase>{

};

TEST(AnAdder, GeneratesSumFrmTwoNumbers)
{
    ASSERT_THAT(Adder::sum(1,1),Eq(2));
}

TEST_P(AnAdder, GeneratesLotsOfSumsFromTwoNumbers)
{
    //外部传入的参数
    SumCase input = GetParam();
    ASSERT_THAT(Adder::sum(input.a, input.b), Eq(input.expected));
}

//传递三次参数，相当于执行三次测试用例
SumCase sums[] = {
    SumCase(1, 1, 2),
    SumCase(1, 2, 3),
    SumCase(2, 2, 4),
};

INSTANTIATE_TEST_CASE_P(BulkTest, AnAdder, ValuesIn(sums));