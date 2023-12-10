
#include <cstdlib>

#include "Node.h"
#include "BinaryTreeAVL.h"

using namespace std;

void menuOpcoes() {
    cout << "\n\t\t-------------------------------" << endl;
    cout << "\t\t             Menu               " << endl;
    cout << "\t\t1 - Inserir " << endl;
    cout << "\t\t2 - Remover balanceando " << endl << endl;
    cout << "\t\t3 - Inserir balanceando " << endl << endl;
    cout << "\t\t-------------------------------  " << endl;
    cout << "\t\ti - Imprimir (em-ordem)" << endl;
    cout << "\t\tp - Imprimir (pos-ordem)" << endl;
    cout << "\t\to - Imprimir (pre-ordem)" << endl;
    cout << "\t\ts - Salvar " << endl;
    cout << "\t\tq - Quit " << endl;
    cout << "\t\t-------------------------------  " << endl;
    cout << "\t\tEscolhar uma opcao:";
}

int main() {
    int id;
    Users user;
    char opcao = 's';
    BinaryTreeAVL tree;
    //tree.loadProdutos();

    do {
        menuOpcoes();
        cin >> opcao;
        cout << "\t\t----------------------------\n";

        switch (opcao) {
            case '1':
                user.fill_data();
                tree.insert(user);
                break;
            case '2':
                cout << endl << endl << "*** Remoção de nó ***" << endl;
                cout << "Informe o id:";
                cin >> id;
                user.setId(id);
                tree.remove(user);
                cout << "*** Remoção feita com sucesso." << endl << endl;
                break;

            case '3':
            {
                user.fill_data();
                tree.insert(user);
                Node* newNode = tree.search(tree.getRoot(), user);
                tree.executeBalancing(newNode);
                
                cout << endl << endl;
                tree.print2D(tree.getRoot());
                cout << endl << endl;
                break;
            }

            case 'i':
            {
                cout << endl << endl << "*** Percurso na arvore ***" << endl;
                tree.inOrder(tree.getRoot());
                cout << endl << "*** Percurso feito." << endl << endl;
                break;
            }

            case 'p':
            {
                cout << endl << endl << "*** Percurso na arvore ***" << endl;
                tree.posOrder(tree.getRoot());
                cout << endl << "*** Percurso feito." << endl << endl;
                break;
            }

            case 'o':
            {
                cout << endl << endl << "*** Percurso na arvore ***" << endl;
                tree.preOrder(tree.getRoot());
                cout << endl << "*** Percurso feito." << endl << endl;
                break;
            }

            case 's':
            {
                cout << endl << endl << "*** Salvando no arquivo..." << endl;
                tree.saveDataInFileText();
                cout << "*** Salvo com sucesso." << endl << endl;
                break;
            }
            default:
                break;
        }
    } while (opcao != 'q' && opcao != 'Q');


    return 0;
}



