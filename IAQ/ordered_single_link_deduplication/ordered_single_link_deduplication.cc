#include "iaq/solve/ordered_single_link_deduplication.hpp"
#include <list>

using iaq::solve::OrderedLinkDeduplication;




OrderedLinkDeduplication::PLinkNode OrderedLinkDeduplication::operator()(PLinkNode head) const
{
    if (head == nullptr){
        return nullptr;
    }

    std::list<OrderedLinkDeduplication::PLinkNode> listlink;
    OrderedLinkDeduplication::PLinkNode curnode = head->next;
    listlink.push_back(head);
    for(;curnode!=nullptr;curnode = curnode->next){
        if (!listlink.empty() &&
            listlink.back()->value == curnode->value){
            auto tmpnode = curnode->next;
            if (tmpnode == nullptr ||
                listlink.back()->value != tmpnode->value){
                    listlink.pop_back();
                }

            if (tmpnode == nullptr && !listlink.empty()){
                listlink.back()->next = nullptr;
            }

        }else{
            if (!listlink.empty()){
                listlink.back()->next = curnode;
            }
            listlink.push_back(curnode);
        }
    }
    
    return listlink.empty()? nullptr: listlink.front();
}