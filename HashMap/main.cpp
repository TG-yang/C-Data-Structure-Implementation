#include <iostream>


//Unordered map is an associative container that contains key-value pairs with unique keys.
//Search, insertion, and removal of elements have average constant-time complexity.


//Internally, the elements are not sorted in any particular order,
//but organized into buckets. Which bucket an element is placed into depends entirely on the hash of its key.
//This allows fast access to individual elements, since once the hash is computed,
//it refers to the exact bucket the element is placed into.
//STL中，map对应的数据结构是红黑树。红黑树是一种近似于平衡的二叉查找树，
//里面的数据是有序的。在红黑树上做查找操作的时间复杂度为 O(logN)。
//而unordered_map对应 哈希表，哈希表的特点就是查找效率高，时间复杂度为常数级别 O(1)，
//而额外空间复杂度则要高出许多。所以对于需要高效率查询的情况，使用unordered_map容器。
//而如果对内存大小比较敏感或者数据存储要求有序的话，则可以用map容器。

//插入:O(1)，最坏情况O(N)。
//
//查看:O(1)，最坏情况O(N)。
//
//删除:O(1)，最坏情况O(N)。
using namespace std;

template <class Key, class Value>
class HashNode{
public:
    Key _key;
    Value _val;
    HashNode*next;

    HashNode(Key key, Value val){
        _key = key;
        _val = val;
        next = NULL;
    }
    ~HashNode(){}
    HashNode&operator=(const HashNode&node){
        _key = node._key;
        _val = node._val;
        next = node.next;
        return *this;
    }
};

template <class Key, class Value, class HashFunc, class EqualKey>
class HashMap{
private:
    HashFunc hash;
    EqualKey equal;
    HashNode<Key,Value>**table;
    unsigned int _size;
    Value ValueNULL;
public:
    HashMap(int size);
    ~HashMap();
    bool insert(const Key&key, const Value&value);
    bool del(const Key&key);
    Value&find(const Key&key);
    Value&operator[](const Key&key);
};

template <class Key, class Value, class HashFunc, class EqualKey>
HashMap<Key,Value,HashFunc,EqualKey>::HashMap(int size) :_size(size),hash(),equal(){
    table = new HashNode<Key,Value>*[_size];
    for(unsigned i = 0; i < _size; ++i)
        table[i] = NULL;
}

template <class Key, class Value, class HashFunc, class EqualKey>
HashMap<Key,Value,HashFunc,EqualKey>::~HashMap(){
    for(unsigned i = 0; i < _size; ++i){
        HashNode<Key,Value>*currentNode = table[i];
        while (currentNode){
            HashNode<Key,Value>*temp = currentNode;
            currentNode = currentNode->next;
            delete temp;
        }
    }
    delete table;
}

template <class Key, class Value, class HashFunc, class EqualKey>
bool HashMap<Key,Value,HashFunc,EqualKey>::insert(const Key &key, const Value &value){
    int index = hash(key) % _size;
    HashNode<Key,Value>*node = new HashNode<Key, Value>(key,value);
    node->next = table[index];
    table[index] = node;
    return true;
}

template <class Key, class Value, class HashFunc, class EqualKey>
bool HashMap<Key,Value,HashFunc,EqualKey>::del(const Key &key){
    unsigned index = hash(key)%_size;
    HashNode<Key,Value>*node = table[index];
    HashNode<Key,Value>*prev = NULL;
    while (node){
        if(node->_key == key){
            if(prev == NULL){
                table[index] = node->next;
            }else{
                prev->next = node->next;
            }
            delete node;
            return true;
        }
        prev = node;
        node = node->next;
    }
    return false;
}

template <class Key, class Value, class HashFunc, class EqualKey>
Value&HashMap<Key, Value, HashFunc, EqualKey>::find(const Key &key){
    unsigned index = hash(key) % _size;
    if(table[index] == NULL){
        cout << "There is no such key" << endl;
        return ValueNULL;
    }else{
        HashNode<Key,Value>*node = table[index];
        while (node){
            if(node->_key == key)
                return node->_val;
            node = node->next;
        }
    }
}

template <class Key, class Value, class HashFunc, class EqualKey>
Value&HashMap<Key, Value, HashFunc, EqualKey>::operator[](const Key &key) {
    return find(key);
}

class HashFunc{
public:
    int operator()(const string & key){
        int hash = 0;
        for(int i = 0; i < key.length(); ++i){
            hash = hash << 7 ^ key[i];
        }
        return (hash & 0x7FFFFFFF);
    }
};


class EqualKey{
public:
    bool operator()(const string & A, const string & B){
        if (A.compare(B) == 0)
            return true;
        else
            return false;
    }
};


int main() {
    HashMap<string, string, HashFunc, EqualKey> hashmap(100);

    hashmap.insert("hello", "world");
    hashmap.insert("why", "dream");
    hashmap.insert("c++", "good");
    hashmap.insert("welcome", "haha");


    cout << "after insert:" << endl;
    cout << hashmap.find("welcome").c_str() << endl;
    cout << hashmap.find("c++").c_str() << endl;
    cout << hashmap["why"].c_str() << endl;
    cout << hashmap["hello"].c_str() << endl;

    if (hashmap.del("hello"))
        cout << "remove is ok" << endl;    //remove is ok
    cout << hashmap.find("hello").c_str() << endl; //not exist print NULL

    hashmap["why"] = "love";
    cout << hashmap["why"].c_str() << endl;
    return 0;
}
