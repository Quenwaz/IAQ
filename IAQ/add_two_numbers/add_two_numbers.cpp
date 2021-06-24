
#include "iaq/solve/add_two_numbers.hpp"

using namespace iaq;

solve::AddTwoNumbers::List::List()
    : root_(nullptr), curpos_(nullptr)
{

}

solve::AddTwoNumbers::List::List(ListNode* linkroot)
    :root_(linkroot), curpos_(nullptr)
{
}

solve::AddTwoNumbers::List::~List()
{
    this->free();
}

solve::AddTwoNumbers::ListNode* solve::AddTwoNumbers::List::GetRoot() const
{
    return root_;
}

void solve::AddTwoNumbers::List::push_back(const decltype(ListNode::val)& val)
{
    ListNode* node = new ListNode(val);
    if(root_ == nullptr){
        root_ = node;
        curpos_ = root_;
        return;
    }
    curpos_->next = node;
    curpos_ = node;
}

bool solve::AddTwoNumbers::List::operator==(const List& rhs) const
{
    const ListNode* l_next = this->root_;
    const ListNode* r_next = rhs.root_;
    for(;l_next != nullptr && r_next != nullptr;)
    {
        if (r_next->val != l_next->val){
            return false;
        }
        l_next = l_next->next;
        r_next = r_next->next;
    }

    return l_next == nullptr && r_next == nullptr;
}


void solve::AddTwoNumbers::List::free()
{
    if (root_ == nullptr){
        return;
    }

    ListNode* curnode = root_;
    do
    {
        ListNode* next = curnode->next;
        delete curnode;
        curnode = nullptr;
        curnode = next;
    }while(curnode != nullptr);
}

void solve::AddTwoNumbers::reverse(ListNode** link) const
{
    if (link == nullptr || *link == nullptr)
    {
        return;
    }

    ListNode* last = *link;
    ListNode* next = (*link)->next;
    (*link)->next = nullptr;
    for (; next != nullptr;)
    {   
        ListNode* _last = last;
        last = next;
        ListNode* node = next->next ;
        next->next = _last;
        next = node;
    }

    *link = last;
}

namespace __internal{
    typedef solve::AddTwoNumbers::ListNode ListNode;
  
    ListNode* addtwonumbers_v1(ListNode* l1, ListNode* l2)
    {
        if (l1 == nullptr || l2 == nullptr){
            return nullptr;
        }

        ListNode* lhs = l1;
        ListNode* rhs = l2;

        ListNode *result_root = nullptr;
        int carry = 0;
        for (ListNode* curpos = nullptr;lhs != nullptr || rhs != nullptr || carry == 1;)
        {
            ListNode* node = new ListNode;
            if (result_root == nullptr){
                result_root = node;
                curpos = result_root;
            }else{
                curpos->next = node;
                curpos = node;
            }

            int val = 0;
            if (lhs != nullptr){
                val = lhs->val;
                lhs = lhs->next;
            }

            if (rhs != nullptr){
                val += rhs->val;
                rhs = rhs->next;
            }

            val += carry;
            node->val = val % 10;
            if (val > 9){
                carry = 1;
            }else carry = 0;
            
        }

        return result_root;
    }
}

solve::AddTwoNumbers::ListNode* solve::AddTwoNumbers::operator()(solve::AddTwoNumbers::ListNode* l1, solve::AddTwoNumbers::ListNode* l2) const
{
    return  __internal::addtwonumbers_v1(l1, l2);
}

