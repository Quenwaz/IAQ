#ifndef _h_lrucache_included
#define _h_lrucache_included
#include "iaq/iaq_defs.hpp"
#include <cstddef>

namespace iaq::solve
{
    struct LRUCache : public iaq::AlgBase
    {
        LRUCache(size_t capacity,iaq::Version ver = iaq::Version::V1);
        ~LRUCache();

        iaq::Version GetSupportMaxVersion() const override
        {
            return iaq::Version::V2;
        }

        template<typename T>
        bool get(const char* key,T& val);

        template<typename T>
        void put(const char* key, const T& val);


    private:
        const size_t cache_capacity_;
        struct Impl;
        Impl* implptr_;
    };

}



#endif // _h_lrucache_included