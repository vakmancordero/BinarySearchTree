#ifndef BST_H
#define BST_H
#include <iostream>
#include <qtextstream>
#include <qprocess>

using namespace std;

struct Node {
    Node *parent;
    Node *left;
    Node *right;
    int value;
};

class BinarySearchTree {

    public:

        BinarySearchTree();

        void add(int a);

        void preorder();
        void postorder();
        void inorder();

        void deleteNode(int value);
        void deleteNode(Node* node);
        void show();

        int countNodes();
        int countLevels();
        int countLeftNodes();

        Node* find(int value);

    protected:

    private:
        int countNodes(Node* p);
        int countLevels(Node* p);
        int countLeftNodes(Node *p);

        void preorder(Node* p);
        void postorder(Node* p);
        void inorder(Node* p);

        Node* findSuccessor(int value);

        QByteArray prepareGraph();
        void graph(Node* node,  QTextStream* stream);
        Node* find(int value, Node* node);

        Node* root;
};

#endif
