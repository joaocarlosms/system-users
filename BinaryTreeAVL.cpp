#include "BinaryTreeAVL.h"

BinaryTreeAVL::BinaryTreeAVL()
{
    this->root = NULL;
    this->quant = 0;
}

BinaryTreeAVL::BinaryTreeAVL(int quant, Node* root)
{
    this->root = root;
    this->quant = quant;
}

BinaryTreeAVL::BinaryTreeAVL(const BinaryTreeAVL& other)
{
    root = other.getRoot();
    quant = other.getQuant();
}

void BinaryTreeAVL::setQuant(int quant)
{
    this->quant = quant;
}

int BinaryTreeAVL::getQuant() const
{
    return quant;
}

void BinaryTreeAVL::setRoot(Node* root)
{
    this->root = root;
}

Node* BinaryTreeAVL::getRoot() const
{
    return root;
}

Node* BinaryTreeAVL::search(Node* subtree, const Users& user)
{
    if(subtree != NULL)
    {
        Users itemUser = subtree->getItem(); //VAR AUX;
        if(user.getId() > itemUser.getId())
            return search(subtree->getDir(), user);
        else if(user.getId() < itemUser.getId())
            return search(subtree->getEsq(), user);
        else
            return subtree;     
    } else {
        cout << "Element not found!\n";
        return NULL;
    }
}

Node* BinaryTreeAVL::inputLocal(Node* subtree, const Users& user)
{
    Users itemUser = subtree->getItem();
    if(user.getId() < itemUser.getId())
    {
        if(subtree->getEsq() != NULL)
            return inputLocal(subtree->getEsq(), user);
    } else {
        if(subtree->getDir() != NULL)
            return inputLocal(subtree->getDir(), user);
    }
    return subtree;     
}

void BinaryTreeAVL::insert(Users& user)
{
    Node *newNode = new Node();
    newNode->setItem(user);

    if(root == NULL)
    {
        root = new Node();
        root->setItem(user);
        quant++;
    } else {
        Node* father = this->inputLocal(root, user);
        Users itemFather = father->getItem();

        if(user.getId() < itemFather.getId())
        {
            father->setEsq(newNode);
            newNode->setFather(father);
            quant++;
        } 
        else if(user.getId() > itemFather.getId())
        {
            father->setDir(newNode);
            newNode->setFather(father);
            quant++;
        }
        else
            cout << "ERROR! This element already exists\n";
    }
}

Node* BinaryTreeAVL::smallerDescendent(Node* no)
{
    if(no != NULL)
    {
        if(no->getEsq() == NULL)
            return no;
        else 
            return smallerDescendent(no->getEsq());
    }
    return NULL;
}

Node* BinaryTreeAVL::getSuccessor(Node* no)
{
    if(no != NULL)
    {
        return smallerDescendent(no->getDir());
    } else {
        cout << "This node not own successor!\n";
        return NULL;
    }
}

Node* BinaryTreeAVL::higherDescendent(Node* no)
{
    if(no != NULL)
    {
        if(no->getDir() == NULL)
            return no;
        else 
            return higherDescendent(no->getDir());
    }
    return NULL;
}

Node* BinaryTreeAVL::getPrevious(Node* no)
{
    if(no != NULL)
        return higherDescendent(no->getEsq());
    else {
        cout << "This node not own previous";
        return NULL;
    }
}

void BinaryTreeAVL::removeZeroChilds(Node* left)
{
    Node* father = left->getFather();
    if(father == NULL)
    {
        root = NULL;
    } else {
        Users itemFather = father->getItem();
        Users itemLeft = father->getItem();

        if(itemLeft.getId() < itemFather.getId())
            father->setEsq(NULL);
        else 
            father->setDir(NULL);
    }   
}

void BinaryTreeAVL::removeOneChild(Node* left)
{
    Node* father = left->getFather();
    Node* child = left->getOnlyOneChild();

    if(father == NULL)
        root = child;
    else {
        if(child != NULL)
        {
            child->setFather(father);
            if(child->getItem().getId() < father->getItem().getId())
                father->setEsq(child);
            else
                father->setDir(child);
        }
    }
}

void BinaryTreeAVL::removeNchilds(Node* left)
{
    Node* previous = this->getPrevious(left);

    Users user = previous->getItem();
    this->remove(user);

    left->setItem(previous->getItem());
}

void BinaryTreeAVL::remove(Users& user)
{
    Node* left = this->search(root, user);

    if(left != NULL)
    {
        int numberChilds = left->getNumberChilds();
        if(numberChilds == 0)
            this->removeZeroChilds(left);
        else if(numberChilds == 1)
            this->removeOneChild(left);
        else
            this->removeNchilds(left);
        
        quant--;
    }
}

int BinaryTreeAVL::getHeight(Node* no)
{
    if(no == NULL)
        return 0;
    else {
        int h_esq = this->getHeight(no->getEsq());
        int h_dir = this->getHeight(no->getDir());
    
        if(h_esq > h_dir)
            return h_esq + 1;
        else
            return h_dir + 1;
    }
}

int BinaryTreeAVL::getFactorBalancing(Node* no)
{
    int h_esq = 0, h_dir = 0;
    Node* subEsq = no->getEsq();
    Node* subDir = no->getDir();

    if(subEsq != NULL)
        h_esq = this->getHeight(subEsq);
    if(subDir != NULL)
        h_dir = this->getHeight(subDir);
    
    int factor = h_dir - h_esq;
    no->setFactor(factor);
    
    return factor;
}

Node* BinaryTreeAVL::getP(Node* join)
{
    Node* father = join->getFather();
    while(father != NULL)
    {
        int factor = this->getFactorBalancing(father);
        if(abs(factor) >= 2)
        {
            return father;
        }   
        //percorre cada node pai ate que encontre um node;
        father = father->getFather(); //com um factor de balanceamento maior ou igual a 2;
    }
    return NULL;
}

Node* BinaryTreeAVL::getQ(Node* P)
{
    if(P != NULL) 
    {
        if(P->getFactor() > 0)
            return P->getDir();
        else
            return P->getEsq();
    }
    return NULL;
}

Node* BinaryTreeAVL::getR(Node* Q)
{
    if(Q != NULL)
    {   
        if(Q->getFactor() > 0)
            return Q->getDir();
        else
            return Q->getEsq();
    }
    return NULL;
}

void BinaryTreeAVL::onlyRotation_EsqEsq(Node* P, Node* Q)
{
    Node* fatherP = P->getFather();
    Node* A = Q->getDir(); //aux armazena node da direita de Q;

    Q->setDir(P);
    P->setEsq(A);

    Q->setFather(fatherP);
    if(Q->getItem().getId() > fatherP->getItem().getId())
        fatherP->setDir(Q);
    else
        fatherP->setEsq(Q);
}

void BinaryTreeAVL::onlyRotation_DirDir(Node* P, Node* Q)
{
    Node* fatherP = P->getFather();
    Node* A = Q->getEsq();

    Q->setEsq(P);
    P->setDir(A);

    Q->setFather(fatherP);
    if(Q->getItem().getId() > fatherP->getItem().getId())
        fatherP->setDir(Q);
    else
        fatherP->setEsq(Q);
}

void BinaryTreeAVL::updateBalanceFactors(Node* no)
{
    int left_height = this->getHeight(no->getEsq());
    int right_height = this->getHeight(no->getDir());
    int balance_factor = right_height - left_height;

    no->setFactor(balance_factor);
}

void BinaryTreeAVL::doubleRotation_EsqDir(Node* P, Node* Q, Node* R)
{
    if(P != NULL && Q != NULL && R != NULL)
    {   
        Node* fatherP = P->getFather();
        Node* R_dir = R->getDir();
        Node* R_esq = R->getEsq();

        R->setEsq(Q);
        R->setDir(P);
        Q->setFather(R);
        P->setFather(R);
        P->setEsq(R_dir);
        Q->setDir(R_esq);
        R->setFather(fatherP);

        if(R_dir != NULL)
            R_dir->setFather(P);

        if(fatherP == NULL) // case father of P be equal the root
            root = R;
        else
        {
            if(R->getItem().getId() > fatherP->getItem().getId())
                fatherP->setDir(R);
            else
                fatherP->setEsq(R);
        }
        updateBalanceFactors(P);
        updateBalanceFactors(Q);
        updateBalanceFactors(R);
    }
    else
        cout << "Invalid Operation! The nodes is NULL";
}

void BinaryTreeAVL::doubleRotation_DirEsq(Node* P, Node* Q, Node* R)
{
    if(P != NULL && Q != NULL && R != NULL)
    {   
        Node* fatherP = P->getFather();
        Node* R_esq = R->getEsq();
        Node* R_dir = R->getDir();

        R->setDir(Q);
        R->setEsq(P);
        Q->setFather(R);
        P->setFather(R);
        P->setDir(R_esq);
        Q->setEsq(R_dir);
        R->setFather(fatherP);

        if(R_esq != NULL)
            R_esq->setFather(P);
        
        if(fatherP == root) // case father of P be equal the root
        {
            root = R;
        }
        else
        {
            if(R->getItem().getId() > fatherP->getItem().getId())
                fatherP->setDir(R);
            else
                fatherP->setEsq(R);
        }
        updateBalanceFactors(P);
        updateBalanceFactors(Q);
        updateBalanceFactors(R);
    }
    else
        cout << "Invalid Operation! The nodes is NULL";
}

void BinaryTreeAVL::executeBalancing(Node* join)
{
    Node* P = this->getP(join);

    if (P != NULL)
    {
        Node* Q = this->getQ(P);

        if (Q != NULL)
        {
            if (P->getFactor() > 0 && Q->getFactor() >= 0) // Caso de rotação ++
                this->onlyRotation_DirDir(P, Q);
            else if (P->getFactor() < 0 && Q->getFactor() <= 0) // Caso de rotação --
                this->onlyRotation_EsqEsq(P, Q);
            else if (P->getFactor() > 0 && Q->getFactor() < 0) // Caso de rotação dupla Direita-Esquerda
            {
                Node* R = this->getR(Q);
                if (R != NULL)
                    this->doubleRotation_DirEsq(P, Q, R);
            }
            else if (P->getFactor() < 0 && Q->getFactor() > 0) // Caso de rotação dupla Esquerda-Direita
            {
                Node* R = this->getR(Q);
                if (R != NULL)
                    this->doubleRotation_EsqDir(P, Q, R);
            }
        }
    }
}

void BinaryTreeAVL::print2DUtil(Node* root, int space) {
    const int COUNT = 5; // Adjust this value for spacing

    if (root == nullptr)
        return;

    space += COUNT;
    print2DUtil(root->getDir(), space);

    for (int i = COUNT; i < space; i++) {
        cout << " ";
    }

    cout << root->getItem().getId() << "\n";
    print2DUtil(root->getEsq(), space);
}

void BinaryTreeAVL::print2D(Node *root) {
    print2DUtil(root, 0);
}


void BinaryTreeAVL::visitItems(Node* no)
{
    if(no != NULL)
    {
        cout << "(" << no->getItem().getId() << "," << no->getItem().getName() <<
            "," << no->getItem().getEmail() << "," << no->getItem().getYo() << "), ";

    }
}

void BinaryTreeAVL::preOrder(Node* no)
{
    if(no != NULL)
    {
        this->visitItems(no);
        preOrder(no->getEsq());
        preOrder(no->getDir());
    }
}

void BinaryTreeAVL::inOrder(Node* no)
{
    if(no != NULL)
    {
        inOrder(no->getEsq());
        this->visitItems(no);
        inOrder(no->getDir());
    }
}

void BinaryTreeAVL::posOrder(Node* no)
{
    if(no != NULL)
    {
        posOrder(no->getEsq());
        posOrder(no->getDir());
        this->visitItems(no);
    }
}

void BinaryTreeAVL::preOrderFile(Node* no)
{
    if(no != NULL)
    {
        saveText = saveText + no->getItem().printForSaveFile() + "\n";
        preOrderFile(no->getEsq());
        preOrder(no->getDir());
    }
}

void BinaryTreeAVL::saveDataInFileText()
{
    string pathPaste = "DataText.txt";
    ofstream saveFile;
    saveFile.open(pathPaste, ios::app);

    if(!saveFile.is_open())
        cout << "ERROR! File not found\n";
    else {
        preOrderFile(root);
    }

    saveFile.close();
}