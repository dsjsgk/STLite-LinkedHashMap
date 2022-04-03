#ifndef SJTU_LINKED_HASHMAP_HPP_STD
#define SJTU_LINKED_HASHMAP_HPP_STD

#include <cstddef>
#include <functional>
#include <unordered_map>
#include <bits/stdc++.h>
#include "utility.hpp"
#include "exceptions.hpp"

namespace sjtu {
    template <
            class Key,
            class Value,
            class Hash = std::hash<Key>, 
            class Equal = std::equal_to<Key>
    >
    class linked_hashmap_std {
    public:
        using value_type = pair<const Key, Value>;
    
    private:
        class Node {
        public:
            value_type * val = nullptr;
            Node * next = nullptr;
            
            Node * before = nullptr;
            Node * after = nullptr;
            
            Node(const Key &k, const Value &v, Node * n) : val(new value_type(k, v)), next(n) {}
            
            Node() = default;
            
            ~Node() { delete val; }
        };
        
        std::unordered_map<Key, Node *, Hash, Equal> HashMaps;
        
        class LinkedList {
        public:
            Node * front;
            Node * rear;
            
            LinkedList() {
                front = new Node();
                rear = new Node();
                front->after = rear, rear->before = front;
            }
            
            ~LinkedList() {
                delete front;
                delete rear;
            }
            
            Node * insert(Node * cur) {
                cur->before = rear->before, cur->after = rear;
                rear->before = rear->before->after = cur;
                return cur;
            }
            
            Node * erase(Node * cur) {
                cur->before->after = cur->after, cur->after->before = cur->before;
                return cur;
            }
            
            void clear() {
                delete front;
                delete rear;
                front = new Node();
                rear = new Node();
                front->after = rear, rear->before = front;
            }
        };
        
        LinkedList list;
    
    public:
        class const_iterator;
        
        class iterator {
        private:
            friend class linked_hashmap_std;
            
            Node * ele = nullptr;
        
        public:
            iterator() = default;
            
            explicit iterator(Node * e) : ele(e) {}
            
            iterator(const iterator &other) : ele(other.ele) {}
            
            iterator operator++(int) {
                if (ele->after == nullptr) throw invalid_iterator(); // end()
                iterator ret = *this;
                ele = ele->after;
                return ret;
            }
            
            iterator &operator++() {
                if (ele->after == nullptr) throw invalid_iterator(); // end()
                ele = ele->after;
                return *this;
            }
            
            iterator operator--(int) {
                if (ele->before->before == nullptr) throw invalid_iterator(); // begin()
                iterator ret = *this;
                ele = ele->before;
                return ret;
            }
            
            iterator &operator--() {
                if (ele->before->before == nullptr) throw invalid_iterator(); // begin()
                ele = ele->before;
                return *this;
            }
            
            value_type &operator*() const {
                return *ele->val;
            }
            
            bool operator==(const iterator &rhs) const {
                return ele == rhs.ele;
            }
            
            bool operator==(const const_iterator &rhs) const {
                return ele == rhs.ele;
            }
            
            bool operator!=(const iterator &rhs) const {
                return !(*this == rhs);
            }
            
            bool operator!=(const const_iterator &rhs) const {
                return !(*this == rhs);
            }
            
            value_type * operator->() const noexcept {
                return ele->val;
            }
        };
        
        class const_iterator {
        private:
            friend class linked_hashmap_std;
            
            const Node * ele = nullptr;
        
        public:
            const_iterator() = default;
            
            explicit const_iterator(Node * e) : ele(e) {}
            
            const_iterator(const const_iterator &other) : ele(other.ele) {}
            
            const_iterator(const iterator &other) : ele(other.ele) {}
            
            const_iterator operator++(int) {
                if (ele->after == nullptr) throw invalid_iterator(); // end()
                const_iterator ret = *this;
                ele = ele->after;
                return ret;
            }
            
            const_iterator &operator++() {
                if (ele->after == nullptr) throw invalid_iterator(); // end()
                ele = ele->after;
                return *this;
            }
            
            const_iterator operator--(int) {
                if (ele->before->before == nullptr) throw invalid_iterator(); // begin()
                const_iterator ret = *this;
                ele = ele->before;
                return ret;
            }
            
            const_iterator &operator--() {
                if (ele->before->before == nullptr) throw invalid_iterator(); // begin()
                ele = ele->before;
                return *this;
            }
            
            value_type &operator*() const {
                return *ele->val;
            }
            
            bool operator==(const iterator &rhs) const {
                return ele == rhs.ele;
            }
            
            bool operator==(const const_iterator &rhs) const {
                return ele == rhs.ele;
            }
            
            bool operator!=(const iterator &rhs) const {
                return !(*this == rhs);
            }
            
            bool operator!=(const const_iterator &rhs) const {
                return !(*this == rhs);
            }
            
            value_type * operator->() const noexcept {
                return ele->val;
            }
        };
    
    public:
        linked_hashmap_std() {
            HashMaps.clear();
        }
        
        linked_hashmap_std(const linked_hashmap_std &other) {
            HashMaps.clear();
            for (const_iterator i = other.cbegin(); i != other.cend(); i++) {
                insert(*i.ele->val);
            }
        }
        
        linked_hashmap_std &operator=(const linked_hashmap_std &other) {
            if (this == &other) return *this;
            clear();
            for (const_iterator i = other.cbegin(); i != other.cend(); i++) {
                insert(*i.ele->val);
            }
            return *this;
        }
        
        ~linked_hashmap_std() {
            for (auto x: HashMaps) delete x.second;
        }
        
        Value &at(const Key &key) {
            
            if (!HashMaps.count(key)) throw index_out_of_bound();
            return HashMaps[key]->val->second;
        }
        
        const Value &at(const Key &key) const {
            if (!HashMaps.count(key)) throw index_out_of_bound();
            return HashMaps.at(key)->val->second;
        }
        
        Value &operator[](const Key &key) {
            if (!HashMaps.count(key)) {
                insert(value_type(key, Value()));
            }
            return HashMaps[key]->val->second;
        }
        
        
        const Value &operator[](const Key &key) const {
            if (!HashMaps.count(key)) throw index_out_of_bound();
            return HashMaps.at(key)->val->second;
        }
        
        iterator begin() {
            return iterator(list.front->after);
        }
        
        const_iterator cbegin() const {
            return const_iterator(list.front->after);
        }
        
        iterator end() {
            return iterator(list.rear);
        }
        
        const_iterator cend() const {
            return const_iterator(list.rear);
        }
        
        bool empty() const {
            return HashMaps.empty();
        }
        
        size_t size() const {
            return HashMaps.size();
        }
        
        void clear() {
            list.clear();
            for (auto x: HashMaps) delete x.second;
            HashMaps.clear();
        }
        
        pair<iterator, bool> insert(const value_type &value) {
            if (HashMaps.count(value.first)) return pair<iterator, bool>(iterator(HashMaps[value.first]), false);
            Node * newnode = new Node(value.first, value.second, nullptr);
            Node * node = list.insert(newnode);
            HashMaps[value.first] = node;
            return pair<iterator, bool>(iterator(node), true);
        }
        
        void erase(iterator pos) {
//            Node node = ;
            Node * ptr = HashMaps[pos.ele->val->first];
            HashMaps.erase(pos.ele->val->first);
            delete list.erase(ptr);
        }
        
        size_t count(const Key &key) const {
            return HashMaps.count(key);
        }
        
        iterator find(const Key &key) {
            
            if (!HashMaps.count(key)) return end();
            Node * ptr = HashMaps[key];
//            Node * ptr = &node;
            iterator it = iterator(ptr);
//            cerr<<it.ele
            return it;
        }
        
        const_iterator find(const Key &key) const {
            
            if (!HashMaps.count(key)) return cend();
//            Node node = ;
            Node * ptr = HashMaps.at(key);
            return const_iterator(ptr);
        }
    };
}

#endif
