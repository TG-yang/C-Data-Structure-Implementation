#include <iostream>
#include <vector>

//Priority queues are a type of container adaptors, specifically designed such that
//its first element is always the greatest of the elements it contains, according to some strict weak ordering criterion.
//不是完全排序
using namespace std;

template <class T>
struct Less{
    bool operator()(const T&x, const T&y){
        return x < y;
    }
};
template <class T>
struct Greater{
    bool operator()(const T&x, const T&y){
        return x > y;
    }
};

template <class T, class Cmp = Less<T>>
class Heap{
private:
    vector<T> _heap;
public:
    Heap(){};
    Heap(const T*arr, size_t size);
    void push(T&t);
    void pop();
    bool empty()const;
    const T&top()const;

protected:
    void AdjustDown(int root);
    void AdjustUp(int child);
};

template <class T, class Cmp>
Heap<T,Cmp>::Heap(const T*arr, size_t size){
    for(int i = 0; i < size; ++i){
        _heap.push_back(arr[i]);
    }
    int root = (_heap.size() - 2) / 2;
    while (root >= 0)
        AdjustDown(root--);
}

template <class T, class Cmp>
void Heap<T,Cmp>::push(T &t) {
    _heap.push_back(t);
    AdjustUp(_heap.size() - 1);
}

template <class T, class Cmp>
void Heap<T,Cmp>::pop() {
    if(_heap.size() == 0)
        return;
    if(_heap.size() <= 2){
        swap(_heap[0],_heap[_heap.size() - 1]);
        _heap.pop_back();
    }else{
        swap(_heap[0],_heap[_heap.size() - 1]);
        _heap.pop_back();
        AdjustDown(0);
    }
}

template <class T, class Cmp>
bool Heap<T,Cmp>::empty() const {
    return _heap.size() == 0;
}

template <class T, class Cmp>
const T&Heap<T,Cmp>::top() const {
    if(_heap.size() != 0){
        return _heap[0];
    }

}

template <class T, class Cmp>
void Heap<T,Cmp>::AdjustDown(int root) {
    while (root <= (_heap.size() - 2) / 2){
        int child = root * 2 + 2 >= _heap.size() ? root * 2 + 1 : Cmp()(_heap[root * 2 + 1], _heap[root * 2 + 2]) ? root * 2 + 1 : root * 2 + 2;
        if (!Cmp()(_heap[root], _heap[child])){
            swap(_heap[root], _heap[child]);
        }else{
            break;
        }
        root = child;
    }
}

template <class T, class Cmp>
void Heap<T,Cmp>::AdjustUp(int child) {
    while (child >= 1){
        int root = (child - 1) / 2;
        if (!Cmp()(_heap[root], _heap[child])){
            swap(_heap[root], _heap[child]);
        }
        child = root;
    }
}


int main() {
    int arr[] = { 11,10,13,9,8,15,12,20,3,1};
    Heap<int, Less<int> >hp1(arr, 10);
    int b = 3;
    hp1.push(b);
    cout << "Over!" << endl;
    while (!hp1.empty())
    {
        cout << hp1.top() << " ";
        hp1.pop();
    }
}
