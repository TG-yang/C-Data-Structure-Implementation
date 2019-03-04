#include <iostream>
#include <queue>

//queues are a type of container adaptor, specifically designed to operate in a FIFO context (first-in first-out),
//where elements are inserted into one end of the container and extracted from the other.
using namespace std;



template <typename T>
class Queue{
private:
    T* array;
    int Front;
    int rear;
    int capacity;
public:
    Queue(int maxsize = 10);
    Queue(const Queue<T>&rhs);
    Queue<T>&operator=(const Queue<T>&rhs);
    ~Queue();
protected:
    bool full()const;
public:
    bool empty()const;
    int size() const;
    void push(const T&data);
    void pop();
    T& front();
    T front() const;
    T& back();
    T back() const;
};

template <typename T>
Queue<T>::Queue(int maxsize):Front(0), rear(0), capacity(maxsize){
    array = new T[maxsize];
    assert(array != NULL);
}
template <typename T>
Queue<T>::Queue(const Queue<T>&rhs): Front(rhs.Front),rear(rhs.rear),capacity(rhs.capacity){
    array = new T[capacity];
    for(int i = 0; i != this->size(); ++i){
        array[i] = rhs.array[i];
    }
}
template <typename T>
Queue<T>&Queue<T>::operator=(const Queue<T> &rhs){
    if(this != &rhs){
        delete[] array;
        capacity = rhs.capacity;
        Front = rhs.Front;
        rear = rhs.rear;
        array = new T[capacity];
        for(int i = 0; i != (this->size()); ++i){
            array[i] = rhs.array[i];
        }
    }
    return *this;
}

template <typename T>
Queue<T>::~Queue(){
    delete []array;
}

template <typename T>
bool Queue<T>::empty() const{
    return rear == Front;
}
template <typename T>
bool Queue<T>::full() const{
    return (rear + 1) % (capacity)== Front;
}
template <typename T>
int Queue<T>::size() const{
    return (rear - Front + capacity) % capacity;
}
template <typename T>
void Queue<T>::push(const T &data){

    if(!full()){
        array[rear] = data;
        rear = (rear + 1) % (capacity);
    }else{
        T*newarray = new T[2*capacity];
        for(int i = 0;i < 2*capacity && !this->empty();++i){
            newarray[i] = this->front();
            this->pop();
        }
        delete[] array;
        array = newarray;
        Front = 0;
        array[rear] = data;
        rear = this->rear + 1;
        capacity = 2*capacity;
    }
}
template <typename T>
void Queue<T>::pop(){
    if(!empty()){
        Front = (Front + 1) % capacity;
    }else{
        cout << "empty queue!" << endl;
    }
}

template <typename T>
T& Queue<T>::front(){
    if(empty())
        cout << "Error, queue is empty!";
    return array[Front];
}

template <typename T>
T Queue<T>::front() const{
    if(empty())
        cout << "Error queue is empty!";
    return array[Front];
}

template<typename T>
T& Queue<T>::back(){
    if (empty())
        cerr << "Error, queue is empty!";
    int index = rear - 1 >= 0 ? rear - 1 : capacity - 1;
    return array[index];                             //rear类似与尾后指针
}

template<typename T>
T Queue<T>::back() const{
    if (empty())
        cerr << "Error, queue is empty!";
    int index = rear - 1 >= 0 ? rear - 1 : capacity - 1;
    return array[index];
}



int main()
{
    queue<int>q1;
    Queue<int> q(3); //声明队列
    int a = 1, b = 2, c = 3;
    int d = 4, e = 5, g = 6;
    q.push(a);
    q.push(b);
    q.push(c);
    q.pop();
    q.push(d);
    q.push(e);
    q.push(g);
    cout << q.front() << " " << q.back();

    cout << endl;
    return 0;
}
