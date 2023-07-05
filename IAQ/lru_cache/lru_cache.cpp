#include "iaq/solve/lru_cache.hpp"
#include <unordered_map>
#include <list>

template<typename T>
struct CacheNode{
    std::string key;
    T value;
    CacheNode* next;
    CacheNode* prev;
    CacheNode(const char* key, const T& val)
        : key(key), value(val),next(nullptr), prev(nullptr){}
};


struct iaq::solve::LRUCache::Impl
{
    typedef int ValueType;
    typedef CacheNode<ValueType> NodeType;
    typedef NodeType* NodeTypePtr;
public:
    std::unordered_map<std::string, NodeTypePtr> cache_map;
    NodeTypePtr cache_link_head = nullptr;
    NodeTypePtr cache_link_tail = nullptr;

public:
    void move_link_to_head(NodeTypePtr node)
    {
        if (node != cache_link_head)
        {
            remove_node(node);
            add_link_to_head(node);
        }
    }

    void add_link_to_head(NodeTypePtr node)
    {
        if (cache_link_head == nullptr){
            cache_link_head = node;
            cache_link_tail = cache_link_head;
        }

        cache_link_head->prev = node;
        node->next = cache_link_head;
        cache_link_head = node;
    }

    void remove_tail(){
        remove_node(cache_link_tail);
    }

private:
    void remove_node(NodeTypePtr node)
    {
        if (node == cache_link_head){
            cache_link_head = cache_link_head->next;
            if (cache_link_head != nullptr)
                cache_link_head->prev = nullptr;
        }else if(node == cache_link_tail){
            cache_link_tail = cache_link_tail->prev;
            if (cache_link_tail != nullptr)
                cache_link_tail->next = nullptr;
        }else{
            node->next->prev = node->prev;
            node->prev = node->next;
        }
    }
};

iaq::solve::LRUCache::LRUCache(size_t capacity,iaq::Version ver)
    : iaq::AlgBase(ver),cache_capacity_(capacity), implptr_(new Impl())
{
}


iaq::solve::LRUCache::~LRUCache()
{
    delete implptr_;
    implptr_ = nullptr;
}

template<>
bool iaq::solve::LRUCache::get<int>(const char* key,int& val)
{
    auto iter_find = implptr_->cache_map.find(key);
    if(iter_find == implptr_->cache_map.end()){
        return false;
    }
    val = iter_find->second->value;
    implptr_->move_link_to_head(iter_find->second);

    return true;
} 

template<>
void iaq::solve::LRUCache::put<int>(const char* key, const int& val)
{
    auto iter_find = implptr_->cache_map.find(key);
    if(iter_find == implptr_->cache_map.end()){
        Impl::NodeTypePtr node = new Impl::NodeType(key, val);
        implptr_->cache_map[key] = node;
        implptr_->add_link_to_head(node);
        if (implptr_->cache_map.size() > cache_capacity_)
        {
            implptr_->cache_map.erase(implptr_->cache_link_tail->key);
            implptr_->remove_tail();
        }
    }else{
        Impl::NodeTypePtr node = iter_find->second;
        implptr_->move_link_to_head(node);
    }
}


