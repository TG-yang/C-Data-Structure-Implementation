#include <iostream>
#include <vector>


//last in, first out
//makes it easy to take an item off the top of the stack,
//while getting to an item deeper in the stack may require taking off multiple other items first

using namespace std;

template <typename T,int num>
class Stack
{
private:
    int _top;
    T _parr[num];
public:
    Stack();
    ~Stack();
    bool full();
    bool empty();
    bool push(T elem);
    bool pop(T &);
    int getPos()
    {
        return _top;
    }
};

template <typename T,int num>
Stack<T,num>::Stack():_top(-1)
{}
template <typename T,int num>
Stack<T,num>::~Stack()
{}
template <typename T,int num>
bool Stack<T,num>::full()
{
    return _top == (num-1);
}
template <typename T,int num>
bool Stack<T,num>::empty()
{
    return _top == -1;
}
template <typename T,int num>
bool Stack<T,num>::push(T elem)
{
    if(!full())
    {
        _parr[++_top] = elem;
        return true;
    }
    return false;
}
template <typename T,int num>
bool Stack<T,num>::pop(T & t)
{
    if(!empty())
    {
        t = _parr[_top--];
        return true;
    }
    else
        return false;
}



//template <typename T>
//class Stack{
//private:
//    vector<T>items;
//public:
//    Stack(){};
//    ~Stack(){};
//    bool empty();
//    bool push(T elem);
//    bool pop();
//    T top();
//};
//
//template <typename T>
//bool Stack<T>::empty() {
//    return items.size() == 0;
//}
//
//template <typename T>
//bool Stack<T>::push(T elem) {
//    items.push_back(elem);
//    return true;
//}
//
//template <typename T>
//bool Stack<T>::pop() {
//    if(items.size() > 0){
//        items.pop_back();
//        return true;
//    }else
//        return false;
//}
//
//template <typename T>
//T Stack<T>::top() {
//    return items[items.size() - 1];
//}


//
//int main() {
//    Stack<int>stack1;
//    stack1.push(1);
//    cout << stack1.top();
//    std::cout << "Hello, World!" << std::endl;
//    return 0;
//}