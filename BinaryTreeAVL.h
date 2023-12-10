#ifndef BINARYTREEAVL_H
#define BINARYTREEAVL_H

#include "Users.h"
#include "Node.h"
#include <iostream>
#include <fstream>
#include <ostream>

using namespace std;

class BinaryTreeAVL {
private:
    int quant;
    Node* root;

    string saveText = " ";

    Node* inputLocal(Node* subtree, const Users& user);
    Node* smallerDescendent(Node* no);
    Node* higherDescendent(Node* no);
public:
    BinaryTreeAVL();
    BinaryTreeAVL(int quant, Node* root);
    BinaryTreeAVL(const BinaryTreeAVL& orig);
    void setQuant(int quant);
    int getQuant() const;
    void setRoot(Node* root);
    Node* getRoot() const;

    Node* search(Node* subtree, const Users& user);
    void insert(Users &user);
    Node* getSuccessor(Node* no);
    Node* getPrevious(Node* no);

    void removeZeroChilds(Node* left);
    void removeOneChild(Node* left);
    void removeNchilds(Node* left);
    void remove(Users& user);

    int getHeight(Node* no);
    int getFactorBalancing(Node* no);
    Node* getP(Node* no);
    Node* getQ(Node* P);
    Node* getR(Node* R);
    void onlyRotation_EsqEsq(Node* P, Node* Q);
    void onlyRotation_DirDir(Node* P, Node* Q);
    void  doubleRotation_EsqDir(Node* P, Node* Q, Node* R);
    void doubleRotation_DirEsq(Node* P, Node* Q, Node* R);
    void executeBalancing(Node* join);
    void updateBalanceFactors(Node* no);
    void print2DUtil(Node* root, int space);
    void print2D(Node* root);

    void preOrder(Node* no);
    void inOrder(Node* no);
    void posOrder(Node* no);
    void visitItems(Node* no);

    void preOrderFile(Node* no);
    void saveDataInFileText();
};  

#endif //BINARYTREEAVL_H