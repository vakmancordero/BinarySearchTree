#include "BinarySearchTree.h"
#include <QDebug>
#include <QFile>

BinarySearchTree::BinarySearchTree() {
    this->root = NULL;
}

void BinarySearchTree::add(int a) {

    Node* temp = new Node;

    temp->value = a;
    temp->left = NULL;
    temp->right = NULL;

    if (this->root == NULL) {

        temp->parent = NULL;

        this->root = temp;

    } else {

        Node* element = this->root;

        Node* parent = NULL;

        while(element != NULL) {

            parent = element;

            element = (a < element->value) ? element->left : element->right;

        }

        temp->parent = parent;

        if (a < parent->value) {

            parent->left = temp;

        } else {

            parent->right = temp;

        }
    }

    this->show();
}

void BinarySearchTree::preorder(Node* node) {

    if (node != NULL) {

       cout << node->value << " ";

       this->preorder(node->left);

       this->preorder(node->right);

    }

}

void BinarySearchTree::preorder() {

    cout << "Preorder: ";

    this->preorder(this->root);

    cout << endl;

}

void BinarySearchTree::postorder(Node* node) {

    if (node != NULL) {

        this->postorder(node->left);

        this->postorder(node->right);

        cout << node->value << " ";

    }

}

void BinarySearchTree::postorder(){

    cout << "Postorder: ";

    this->postorder(this->root);

    cout << endl;

}

void BinarySearchTree::inorder(Node* node) {

    if (node != NULL) {

       this->inorder(node->left);

       cout << node->value << "\n";

       this->inorder(node->right);

    }

}

void BinarySearchTree::inorder() {

    //cout << "Inorder: \n";

    this->inorder(this->root);

    cout << endl;

}

Node* BinarySearchTree::find(int value, Node* node) {

    if (node != NULL) {

        if (value == node->value) {

            return node;

        }

        if (value < node->value) {

            return find(value, node->left);

        } else {

            return find(value, node->right);

        }

    } else {

        return NULL;

    }

}

Node* BinarySearchTree::find(int value){

    return this->find(value, this->root);

}

Node* BinarySearchTree::findSuccessor(int value) {

    Node* startNode = this->find(value);

    Node* parent = startNode;

    startNode = startNode->right;

    while (startNode != NULL && startNode->left != NULL) {

        parent = startNode;

        startNode = startNode->left;

    }

    return startNode;

}

void BinarySearchTree::deleteNode(Node* node){

    Node *q = NULL;
    Node *r = NULL;

    if (node->left == NULL || node->right == NULL) {

        q = node;

    } else {

        q = this->findSuccessor(node->value);

    }

    if (q->left != NULL) {

        r = q->left;

    } else {

        r = q->right;

    }

    if (r != NULL) {

        r->parent = q->parent;

    }

    if (q->parent == NULL) {

        this->root = r;

    } else if (q == q->parent->left){

        q->parent->left = r;

    } else {

        q->parent->right = r;

    }

    if (q != node) {

        node->value = q->value;

    }
}

void BinarySearchTree::deleteNode(int value) {

    this->deleteNode(this->find(value));

    this->show();

}

int BinarySearchTree::countLevels(Node* node){

    int h1 = 0, h2 = 0;

    if (node == NULL) {
        return 0;
    }

    if (node->left) {

        h1 = countLevels(node->left);

    }

    if (node->right) {

        h2 = countLevels(node->right);

    }

    return (max(h1, h2) + 1);
}

int BinarySearchTree::countLevels(){

    return this->countLevels(this->root);

}

int BinarySearchTree::countNodes(Node* node) {

    if (node == NULL) {

        return 0;

    } else {

        return (countNodes(node->left) + countNodes(node->right) + 1);

    }
}

int BinarySearchTree::countNodes(){
    return this->countNodes(this->root);
}

int BinarySearchTree::countLeftNodes(Node* node) {

    if (node == NULL) {

        return 0;

    } else {

        return (countLeftNodes(node->left) + countLeftNodes(node->right)) + (node->left != NULL && node->right == NULL) ? 1 : 0;

    }
}

int BinarySearchTree::countLeftNodes() {

    return this->countLeftNodes(this->root);

}

void BinarySearchTree::graph(Node* node, QTextStream *stream) {

    if (node != NULL) {

        *stream << "\t\t" << "n" << node->value << "[label=\"" << node->value <<"\"];" << endl;

        if (node->left != NULL) {

            *stream << "\t\tn" << node->value << "--" << "n" << node->left->value << ";" << endl;

            this->graph(node->left, stream);

        } else {

            *stream << "\t\t" << "n" << node->value << "leftNull" << "[style=\"filled\",label=\"NULL\"];" << endl;

            *stream << "\t\tn" << node->value << "--" << "n" << node->value << "leftNull" << endl;

        }

        if (node->right != NULL) {

            *stream << "\t\tn" << node->value << "--" << "n" << node->right->value << ";" << endl;

            this->graph(node->right, stream);

        } else {

            *stream << "\t\t" << "n" << node->value << "rightNull" << "[style=\"filled\",label=\"NULL\"];" << endl;

            *stream << "\t\tn" << node->value << "--" << "n" << node->value << "rightNull" << endl;

        }

    }

}

QByteArray BinarySearchTree::prepareGraph() {

    QByteArray byteArray = QByteArray();

    QTextStream stream(&byteArray, QIODevice::ReadWrite);

    stream << "graph ""{" << endl;
    stream << "\tnode[fontsize=10,margin=0,width=\".4\", height=\".3\"];" << endl;
    stream << "\tsubgraph cluster17{" << endl;

    this->graph(this->root, &stream);

    stream << "\t}\n" << "}" << endl;

    stream.flush();

    return byteArray;

}

void BinarySearchTree::show() {

    QProcess* process = new QProcess();
    QByteArray byteArray = this->prepareGraph();

    QFile file("C:/Files/search.dot");
    file.open(QIODevice::WriteOnly);
    file.write(byteArray);
    file.close();

    process->start("dot", QStringList() << "-Tpng" << "C:/Files/search.dot" << "-o" << "C:/Files/search.png");
    process->waitForReadyRead(100);

    qDebug() << process->arguments();
    qDebug() << process->readAll();
    qDebug() << process->exitCode();

    /*
    QByteArray data;
    QPixmap pixmap = QPixmap();

    while(process->waitForReadyRead(100)){
        data.append(process->readAll());
    }

    pixmap.loadFromData(data);

    this->_scene->addPixmap(pixmap);
    this->_view->show();
    */

}
