#ifndef NODE_H
#define NODE_H 

#include "Users.h"

using namespace std;

class Node {
private:
    Node* father;
    Node* esq;
    Users item;
    Node* dir;

    int factor;

public:
    Node();
    Node(Node* father, Node* esq, Node* dir, Users item);
    Node(const Node& orig);
    void setFather(Node* father);
    Node* getFather() const;
    void setEsq(Node* esq);
    Node* getEsq() const;
    void setDir(Node* dir);
    Node* getDir() const;
    void setItem(Users item);
    Users getItem() const;
    void setFactor(int factor);
    int getFactor() const;

    int getNumberChilds();
    Node* getOnlyOneChild();
};

#endif //NODE_H