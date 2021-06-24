#include "gtest/gtest.h"
#include "iaq/iaq.hpp"

using namespace iaq;

TEST(addtwonum, t1)
{
    solve::AddTwoNumbers::List list1;
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);
    list1.push_back(4);

    solve::AddTwoNumbers::List list2;
    list2.push_back(1);
    list2.push_back(2);
    list2.push_back(3);

    EXPECT_FALSE(list1==list2) <<"测试链表等号操作符";
    list2.push_back(4);
    ASSERT_EQ(list1, list2);
}


TEST(addtwonum, t2)
{
    solve::AddTwoNumbers::List list1;
    list1.push_back(0);

    solve::AddTwoNumbers::List list2;
    list2.push_back(0);


    EXPECT_TRUE(list1==list2) <<"测试链表等号操作符";

    solve::AddTwoNumbers::List list3;
    list3.push_back(0);

    auto result = solve::AddTwoNumbers()(list1.GetRoot(), list2.GetRoot());
    if (result != NULL)
    {
        EXPECT_EQ(list3, solve::AddTwoNumbers::List(result));
    }else{
        ADD_FAILURE();
    }
}


TEST(addtwonum, t3)
{
    solve::AddTwoNumbers::List list1;
    list1.push_back(2);
    list1.push_back(4);
    list1.push_back(3);

    solve::AddTwoNumbers::List list2;
    list2.push_back(5);
    list2.push_back(6);
    list2.push_back(4);

    EXPECT_FALSE(list1==list2) <<"测试链表等号操作符";

    solve::AddTwoNumbers::List list3;
    list3.push_back(7);
    list3.push_back(0);
    list3.push_back(8);

    auto result = solve::AddTwoNumbers()(list1.GetRoot(), list2.GetRoot());
    if (result != NULL)
    {
        EXPECT_EQ(list3, solve::AddTwoNumbers::List(result));
    }else{
        ADD_FAILURE();
    }
}

TEST(addtwonum, t4)
{
    solve::AddTwoNumbers::List list1;
    list1.push_back(2);
    list1.push_back(4);
    list1.push_back(9);

    solve::AddTwoNumbers::List list2;
    list2.push_back(5);
    list2.push_back(6);
    list2.push_back(4);
    list2.push_back(9);

    EXPECT_FALSE(list1==list2) <<"测试链表等号操作符";

    solve::AddTwoNumbers::List list3;
    list3.push_back(7);
    list3.push_back(0);
    list3.push_back(4);
    list3.push_back(0);
    list3.push_back(1);

    auto result = solve::AddTwoNumbers()(list1.GetRoot(), list2.GetRoot());
    if (result != NULL)
    {
        EXPECT_EQ(list3, solve::AddTwoNumbers::List(result));
    }else{
        ADD_FAILURE();
    }
}

TEST(addtwonum, t5)
{
    solve::AddTwoNumbers::List list1;
    list1.push_back(9);
    list1.push_back(9);
    list1.push_back(9);
    list1.push_back(9);
    list1.push_back(9);
    list1.push_back(9);
    list1.push_back(9);

    solve::AddTwoNumbers::List list2;
    list2.push_back(9);
    list2.push_back(9);
    list2.push_back(9);
    list2.push_back(9);

    EXPECT_FALSE(list1==list2) <<"测试链表等号操作符";

    solve::AddTwoNumbers::List list3;
    list3.push_back(8);
    list3.push_back(9);
    list3.push_back(9);
    list3.push_back(9);
    list3.push_back(0);
    list3.push_back(0);
    list3.push_back(0);
    list3.push_back(1);

    auto result = solve::AddTwoNumbers()(list1.GetRoot(), list2.GetRoot());
    if (result != NULL)
    {
        EXPECT_EQ(list3, solve::AddTwoNumbers::List(result));
    }else{
        ADD_FAILURE();
    }
}

