#include "gtest/gtest.h"
#include "iaq/solve/lru_cache.hpp"


TEST(lrucache_test, positive)
{
    iaq::solve::LRUCache lrucache(5);
    int val = 0;
    ASSERT_FALSE(lrucache.get("3", val));
    lrucache.put("1",1);
    lrucache.put("2",2);
    lrucache.put("3",3);
    lrucache.put("4",4);
    lrucache.put("5",5);
    lrucache.put("6",6);
    ASSERT_FALSE(lrucache.get("1", val));
    ASSERT_EQ(0,val);
    ASSERT_TRUE(lrucache.get("6", val));
    ASSERT_EQ(val,6);
}
