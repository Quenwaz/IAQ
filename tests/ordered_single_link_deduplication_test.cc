#include "gtest/gtest.h"
#include "iaq/solve/ordered_single_link_deduplication.hpp"

TEST(ordered_single_link_deduplication_test, t1)
{
    typedef iaq::solve::OrderedLinkDeduplication::LinkNode LinkNode;
    LinkNode* head = new LinkNode(1);
    ASSERT_EQ(iaq::solve::OrderedLinkDeduplication()(head), head);
}


TEST(ordered_single_link_deduplication_test, t2)
{
    typedef iaq::solve::OrderedLinkDeduplication::LinkNode LinkNode;
    LinkNode* head = new LinkNode(1);
    auto curnode = head;

    for(size_t i =0 ;i < 10; ++i){
        curnode->next = new LinkNode(1);
        curnode = curnode->next;
    }

    ASSERT_EQ(iaq::solve::OrderedLinkDeduplication()(head), nullptr);
}


TEST(ordered_single_link_deduplication_test, t3)
{
    typedef iaq::solve::OrderedLinkDeduplication::LinkNode LinkNode;
    LinkNode* head = new LinkNode(1);
    auto curnode = head;

    std::vector<int> tv = {1,2,3,3,3,4,5,5,5,6,7,7,7};
    for(auto v : tv){
        curnode->next = new LinkNode(v);
        curnode = curnode->next;
    }
    head = iaq::solve::OrderedLinkDeduplication()(head);
    tv.clear();
    for (auto curnode = head; curnode != nullptr; curnode = curnode->next)
    {
        tv.push_back(curnode->value);
    }
    
    ASSERT_EQ(tv, std::vector<int>({2,4,6}));
}

