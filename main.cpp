#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *parent;
    Node *left;
    Node *right;
    int color; //0 black -> 1 red
};

class RBTree {
private:
    Node *root;
    Node *rootNull;

    void CasesOfInsertion(Node * k){
        Node * u;
        while (k->parent->color == 1) {

            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left; // uncle
                if (u->color == 1) {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    leftRotate(k->parent->parent);
                }
            } else {
                u = k->parent->parent->right; // uncle
                if (u->color == 1) {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = 0;
    }

    void LoopingForPrintTree(Node * root, string indent, bool last) {
        if (root != rootNull) {
            cout<<indent;
            if (last) {
                cout<<"R----";
                indent += "     ";
            } else {
                cout<<"L----";
                indent += "|    ";
            }

            string sColor = root->color?"RED":"BLACK";
            cout<<root->data<<"("<<sColor<<")"<<endl;
            LoopingForPrintTree(root->left, indent, false);
            LoopingForPrintTree(root->right, indent, true);
        }
    }

public:
    RBTree() {
        rootNull = new Node;
        rootNull->color = 0;
        rootNull->left = nullptr;
        rootNull->right = nullptr;
        root = rootNull;
    }

    void leftRotate(Node * x) {
        Node * y = x->right;
        x->right = y->left;
        if (y->left != rootNull) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node * x) {
        Node * y = x->left;
        x->left = y->right;
        if (y->right != rootNull) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    void insert(int key) {

        Node * node = new Node;
        node->parent = nullptr;
        node->data = key;
        node->left = rootNull;
        node->right = rootNull;
        node->color = 1; // new node must be red

        Node * y = nullptr;
        Node * x = this->root;

        while (x != rootNull) {
            y = x;
            if (node->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        node->parent = y;
        if (y == nullptr) {
            root = node;
        } else if (node->data < y->data) {
            y->left = node;
        } else {
            y->right = node;
        }
        if (node->parent == nullptr){
            node->color = 0;
            return;
        }
        if (node->parent->parent == nullptr) {
            return;
        }
        CasesOfInsertion(node);
    }

    void display() {
        if (root) {
            LoopingForPrintTree(this->root, "", true);
        }
    }

};

int main() {
    RBTree bst;
    char choose;

    while (true){
        cout<<"1-Insert\n2-Display\n3-exit\n";
        cin>>choose;
        switch (choose) {
            case '1':
                int key;
                cout<<"Enter Value : ";
                cin>>key;
                bst.insert(key);
                break;
            case '2':
                bst.display();
                break;
            case '3':
                return 0;
            default:
                cout<<"invalid number!\n";
        }
    }
}