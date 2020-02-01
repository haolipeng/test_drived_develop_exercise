//
// Created by Administrator on 2020\2\1 0001.
//

#include "gmock/gmock.h"

//Retweet类
class Retweet{

};

class RetweetCollection{
public:
    RetweetCollection(){
        _size = 0;
    }
    ~RetweetCollection(){
        _size = 0;
    }
public:
    bool IsEmpty()
    {
        return 0 == size();
    }

    int size(){
        return _size;
    }

    void add(const Retweet& sweet)
    {
        _size = 1;
    }

    void remove(const Retweet& sweet)
    {
        _size = 0;
    }

private:
    int _size;
};

using namespace testing;
class ARetweetCollection : public testing::Test
{
public:
    RetweetCollection retweets;
};

/*集合创建时为空*/
TEST_F(ARetweetCollection, IsEmptyWhenCreated)
{
    ASSERT_THAT(retweets.IsEmpty(), Eq(true));
}

/*集合创建时大小为0*/
TEST_F(ARetweetCollection, ZeroSizeWhenCreated)
{
    ASSERT_THAT(retweets.size(), Eq(0));
}

/*添加元素后大小不为空*/
TEST_F(ARetweetCollection, NonZeroWhenAdded)
{
    retweets.add(Retweet());
    ASSERT_THAT(retweets.size(),Eq(1));
}

TEST_F(ARetweetCollection, DecreaseSizeAfterRemove)
{
    retweets.add(Retweet());
    retweets.remove(Retweet());
    ASSERT_THAT(retweets.size(), Eq(0));
}

TEST_F(ARetweetCollection, NotEmptyWhenNonZero)
{
    retweets.add(Retweet());
    ASSERT_THAT(retweets.size(), Gt(0));
    ASSERT_FALSE(retweets.IsEmpty());
}