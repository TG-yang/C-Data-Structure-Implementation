#include <iostream>

using namespace std;


template <typename T>
class Vector{
private:
    int theSize;
    int theCapacity;
    T* items;    //vector内部实际上是管理了一个数组指针,指向首元素的指针
public:
    explicit Vector(int initsize = 0);
    Vector(const Vector&V);
    ~Vector(){delete []items;}
    Vector<T>&operator=(const Vector& ths);
    void resize(int newSize);
    void reserve(int newCapacity);
    T& operator[] (int index);
    const T& operator[] (int index) const;
    bool isEmpty() const;
    int size() const;
    int capacity() const;
    void push_back(T obj);
    void pop_back();
    const T & back() const;
    void insert(T*iterator,T value);
    
    typedef T* iterator;
    typedef const T* const_iterator;
    
    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;
};

#define  SPACE_CAPACITY 5

template <typename T>
Vector<T>::Vector(int initsize) : theSize(initsize), theCapacity(initsize + SPACE_CAPACITY){
    items = new T[theCapacity];
}

template <typename T>
Vector<T>::Vector(const Vector &V): theSize(V.theSize), theCapacity(V.theCapacity){
    items = new T[theCapacity];
    for(int i = 0; i < theSize; ++i){
        items[i] = V.items[i];
    }
}

template <typename T>
Vector<T> &Vector<T>::operator=(const Vector &ths) {
    if(this != &ths){
        delete[] items;
        theSize = ths.theSize;
        theCapacity = ths.theCapacity;
        items = new T[theCapacity];
        for(int i = 0; i < ths.theSize; ++i){
            items[i] = ths.items[i];
        }
    }
    return *this;
}

template <typename T>
void Vector<T>::resize(int newSize) {
    if(newSize <= theSize)
        return;
    while(newSize > theCapacity)
        reserve(2 * newSize + 1);
    theSize = newSize;
}


template <typename T>
void Vector<T>::reserve(int newCapacity) {
    if(newCapacity < theSize){
        return;
    }
    T*temp = items;
    items = new T[newCapacity];
    for(int i = 0; i < theSize; ++i){
        items[i] = temp[i];
    }
    theCapacity = newCapacity;
    delete[] temp;
}

template <typename T>
const T& Vector<T>::operator[](int index) const {
    return items[index];
}

template <typename T>
T& Vector<T>::operator[](int index) {
    return items[index];
}

template <typename T>
bool Vector<T>::isEmpty() const {
    return size() == 0;
}

template <typename T>
int Vector<T>::size() const {
    return theSize;
}

template <typename T>
int Vector<T>::capacity() const {
    return theCapacity;
}

template <typename T>
void Vector<T>::push_back(T obj) {
    if(theSize == theCapacity){
        reserve(2*theCapacity + 1);
    }
    items[theSize++] = obj;
}

template <typename T>
void Vector<T>::pop_back() {
    --theSize;
}

template <typename T>
const T& Vector<T>::back() const {
    return items[size() - 1];
}

template <typename T>
T* Vector<T>::begin() {
    return &items[0];
}

template <typename T>
T* Vector<T>::end() {
    return &items[size()];
}

template <typename T>
const T* Vector<T>::cbegin() const {
    return &items[0];
}

template <typename T>
const T* Vector<T>::cend() const {
    return &items[size()];
}

template <typename T>
void Vector<T>::insert(T*iterator, T value) {
    if(theSize == theCapacity){
        reserve(2*theCapacity + 1);
    }
    T*tmp = new T[theSize + 1];
    const T* it = this->begin();
    int i = 0;
    while (it != iterator){
        tmp[i++] = *it;
        ++it;
    }
    tmp[i++] = value;
    while (it != this->end()){
        tmp[i++] = *it;
        ++it;
    }
    items = tmp;
    theSize++;
}


int main(){
    Vector<int>vector1;
    vector1.push_back(1);
    vector1.push_back(2);
    vector1.push_back(5);
    
    Vector<int>vector2;
    vector2 = vector1;
    vector2.insert(vector2.end(),0);
    for(int i = 0; i < vector2.size(); ++i){
        cout << vector2[i] << " ";
    }
}
