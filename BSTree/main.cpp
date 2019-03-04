#include <iostream>

using namespace std;


//Algorithm		Average	    Worst case
//Space		    O(n)	    O(n)
//Search		O(log n)	O(n)
//Insert		O(log n)	O(n)
//Delete		O(log n)	O(n)
//The major advantage of binary search trees over other data structures is that
// the related sorting algorithms and search algorithms such as in-order traversal can be very efficient

template <typename T>
struct Node{
    T data;
    Node* left;
    Node* right;
    Node(T x, Node*l, Node*r):data(x),left(l), right(r){}
};

template <typename T>
class BSTree{
private:
    Node<T>*root;
public:
    BSTree();
    bool search(const T& value);
    void erase(const T& value);
    bool insert(const T& value);
    void inorderTravel(const Node<T>* temp);
    void preOrderTravel(const Node<T>* temp);
    void postOrderTravel(const Node<T>* temp);
    void print();
private:
    bool del(const T& value, Node<T>*& temp);
};

template <typename T>
BSTree<T>::BSTree() {
    root = NULL;//注意这里一定不要写的太麻烦了，
}
template <typename T>
bool BSTree<T>::search(const T &value) {
    Node<T>*temp = root;
    while (temp){
        if(value < temp->data){
            temp = temp->left;
        }else if(value > temp->data){
            temp = temp->right;
        }else
            return true;
    }

    return false;
}
template <typename T>
bool BSTree<T>::insert(const T &value) {
    if(!root){
        root = new Node<T>(value,NULL,NULL);
        return true;
    }
    Node<T>*pos = root;
    Node<T>*father = NULL;
    while (pos){
        if(value < pos->data){
            father = pos; pos = pos->left;
        }else if(value > pos->data){
            father = pos; pos = pos->right;
        }else
            return false;
    }
    if(value < father->data){
        father->left = new Node<T>(value,NULL,NULL);
    }
    if(value > father->data){
        father->right = new Node<T>(value,NULL,NULL);
    }
    return true;
}
template <typename T>
void BSTree<T>::inorderTravel(const Node<T> *temp) {
    if(temp){
        inorderTravel(temp->left);
        cout << temp->data << " ";
        inorderTravel(temp->right);
    }
}
template <typename T>
void BSTree<T>::preOrderTravel(const Node<T> *temp) {
    if(temp){
        cout << temp->data << " ";
        preOrderTravel(temp->left);
        preOrderTravel(temp->right);
    }
}
template <typename T>
void BSTree<T>::postOrderTravel(const Node<T> *temp) {
    if(temp){
        postOrderTravel(temp->left);
        postOrderTravel(temp->right);
        cout << temp->data << " ";
    }
}
template <typename T>
void BSTree<T>::print() {
    inorderTravel(root);
    cout << endl;
}
template <typename T>
bool BSTree<T>::del(const T& value, Node<T>*& temp){
    if(!temp){
        return false;
    }
    if(temp->data == value){
        if(temp->left == NULL){
            Node<T>* s = temp;
            temp = temp->right;
            free(s);
        }else if(temp->right == NULL){
            Node<T>* s = temp;
            temp = temp->left;
            free(s);
        }else{
            Node<T>* dell_pre = temp;
            Node<T>* dell = temp->right;

            while (dell->left)
                dell_pre = dell, dell = dell->left;

            temp->data = dell->data;
            dell_pre->left = NULL;
            free(dell);
        }
        return true;
    }else if(value < temp->data)
        del(value,temp->left);
    else
        del(value,temp->right);
    return false;
}
template <typename T>
void BSTree<T>::erase(const T &value) {
    del(value,root);
}


int main(){
    BSTree<int> a;
    int test[] = {3, 2, 7, 4, -999, 0, 18 };
    for(auto r : test)
        a.insert(r);

    cout << a.search(7) << endl;

    a.print();
    a.erase(4);
    a.print();
}

