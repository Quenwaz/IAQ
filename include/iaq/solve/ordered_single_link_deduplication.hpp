#ifndef __H_ordered_single_link_deduplication_included__
#define __H_ordered_single_link_deduplication_included__
#include "iaq/iaq_defs.hpp"
#include <cstddef>

namespace iaq::solve
{
    struct OrderedLinkDeduplication : public iaq::AlgBase
    {
        explicit OrderedLinkDeduplication(iaq::Version ver = iaq::Version::V1)
            : iaq::AlgBase(ver)
        {
        }
        iaq::Version GetSupportMaxVersion() const override
        {
            return iaq::Version::V2;
        }

        typedef struct LinkNode
        {
            int value;
            LinkNode* next{nullptr};
            explicit LinkNode(int v): value(v), next(nullptr){}
        }*PLinkNode;


        PLinkNode operator()(PLinkNode head) const;

    };

}



#endif // __H_ordered_single_link_deduplication_included__