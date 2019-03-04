#include <iostream>

using namespace std;

template <typename T>
struct ListNode{
    ListNode(const T &e) : data(e),
    next(NULL), prev(NULL)
    { }

    T data;
    ListNode<T> *next;
    ListNode<T> *prev;
};


template <typename T>
class List;


template <typename T>
class Iterator{
public:
    Iterator(ListNode<T> *p=0) : pos_(p) { }

    T &operator*()
    { return pos_->data; }

    T *operator->()
    { return &(pos_->data); }

    bool operator!=(const Iterator &rhs)
    { return this->pos_ != rhs.pos_; }

    Iterator operator++(int)
    { pos_ = pos_->next; return *this; }

    Iterator operator--(int)
    { pos_ = pos_->prev; return *this; }
private:
    ListNode<T> *pos_;
};

template <typename T>
class Reverse_iterator{
public:
    Reverse_iterator(ListNode<T> *p=0) : pos_(p) { }

    T &operator*()
    { return pos_->data; }

    T *operator->()
    { return &(pos_->data); }

    bool operator!=(const Reverse_iterator &rhs)
    { return this->pos_ != rhs.pos_; }

    Reverse_iterator operator++(int)
    { pos_ = pos_->prev; return *this; }

    Reverse_iterator operator--(int)
    { pos_ = pos_->next; return *this; }

private:
    ListNode<T> *pos_;
};


template <typename T>
class List{
public:

    List() : head_(0), tail_(0), size_(0) { }
    int size() { return size_; }
    void push_back(const T&e);
    void push_front(const T&e);
    void pop_back();
    void pop_front();
    T& front(){ return head_->data;}
    T& back(){ return tail_->data;}
    ~List();

    Iterator<T> begin()
    { return Iterator<T>(head_); }

    Iterator<T>  end()
    { return Iterator<T>(0); }


    Reverse_iterator<T>rbegin()
    { return Reverse_iterator<T>(tail_); }

    Reverse_iterator<T> rend()
    { return Reverse_iterator<T>(0); }

private:
    ListNode<T>* insertInternal(const T&e, ListNode<T>*pos);
    void removeInternal(ListNode<T> *pos);
private:
    ListNode<T> *head_;
    ListNode<T> *tail_;

    int size_;
};


template <typename T>

void List<T>::push_back(const T &e){
    // inserts before the position,
    // 0 is the end() iterator
    // hence insert at the end
    insertInternal(e, NULL);
}

template <typename T>
void List<T>::push_front(const T &e){
    // insert before the head
    insertInternal(e, head_);
}

template <typename T>
ListNode<T> *List<T>::insertInternal(const T &e, ListNode<T> *pos){
    ListNode<T> *n = new ListNode<T>(e);

    size_++;
    // no operation below this should throw
    // as state of the list has changed and memory allocated

    n->next = pos;

    if(pos){
        n->prev = pos->prev;
        pos->prev = n;
    }else{
        // pos is null that is at the very end of the list
        n->prev = tail_;
        tail_ = n;
    }

    if(n->prev){
        n->prev->next = n;
    }else{
        // at the very begining of the list
        head_ = n;
    }

    return n;
}

template <typename T>
void List<T>::removeInternal(ListNode<T> *pos){
    if(pos){
        if(pos->prev)
            pos->prev->next = pos->next;

        if(pos->next)
            pos->next->prev = pos->prev;

        if(pos == head_)
            head_ = pos->next;

        if(pos == tail_)
            tail_ = pos->prev;

        delete pos;
        size_--;
    }
}

template <typename T>
void List<T>::pop_back(){
    removeInternal(tail_);
}

template <typename T>
void List<T>::pop_front(){
    removeInternal(head_);
}


template <typename T>
List<T>::~List(){
    ListNode<T> *current( head_ );

    while(current)
    {
        ListNode<T> *next( current->next );
        delete current;
        current = next;
    }
}





int main(){
    List<int>list1;
    list1.push_back(1);
    list1.push_back(2);
    auto it = list1.begin();
    it++;
    cout << *it;
}

