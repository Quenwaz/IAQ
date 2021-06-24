/**
 * @file twosum.cpp
 * @author Quenwaz (404937333@qq.com)
 * @brief 两数相加
 * @version 0.1
 * @date 2021-06-19
 * 
 * @copyright Copyright (c) 2021 Quenwaz
 * 
 */
#ifndef _h_add_two_num_included__
#define _h_add_two_num_included__
#include "iaq/iaq_defs.hpp"


namespace iaq::solve
{
    struct AddTwoNumbers : public iaq::AlgBase
    {
        explicit AddTwoNumbers(iaq::Version ver = iaq::Version::V1)
            : iaq::AlgBase(ver)
        {
        }

        iaq::Version GetSupportMaxVersion() const override
        {
            return iaq::Version::V1;
        }


        struct ListNode
        {
            int val;
            ListNode *next;
            ListNode() : val(0), next(nullptr) {}
            ListNode(int x) : val(x), next(nullptr) {}
            ListNode(int x, ListNode *next) : val(x), next(next) {}
        };

        class List
        {
        public:
            List();
            explicit List(ListNode* linkroot);
            ~List();
            void free();
            void push_back(const decltype(ListNode::val)& val);
            ListNode* GetRoot() const;
            bool operator==(const List& rhs) const;
        private:
            ListNode* root_;
            ListNode* curpos_;
        };


        ListNode* operator()(ListNode* l1, ListNode* l2) const;
        void reverse(ListNode** link) const;
    };

}

#endif // _h_add_two_num_included__