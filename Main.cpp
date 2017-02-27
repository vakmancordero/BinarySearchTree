#include "BinarySearchTree.h"

#include <QTextStream>
#include <QString>
#include <QFile>

using namespace std;

void deleteElement();
void addElement();
void findElement();

int main() {

    cout << "Universidad Politecnica de Chiapas" << endl;
    cout << "Ingenieria en Desarrollo de Software" << endl;
    cout << "\nEstructuras de datos avanzadas" << endl;
    cout << "BinaryTreeSearch" << endl;

    cout << "\nArturo Cordero Muniz - 8o A" << endl;

    BinarySearchTree* binaryTree = new BinarySearchTree();

    QString fileName = "C:\\Files\\Dataset\\Dataset.I.02.txt";

    QFile inputFile(fileName);

    bool inside = true;

    while (inside) {

        int option;

        cout << "\n----- Opciones -----\n" << endl;
        cout << "1. Agregar un nuevo elemento." << endl;
        cout << "2. Eliminar un elemento." << endl;
        cout << "3. Listar elementos." << endl;
        cout << "4. Buscar un elemento." << endl;
        cout << "5. Exportar BinaryTree." << endl;
        cout << "6. Insertar por conjunto de datos." << endl;
        cout << "7. Salir." << endl;

        cout << "\nIngrese la opcion que desee realizar << ";

        cin >> option;

        switch (option) {

            case 1:

                cout << "Agregar..." << endl;

                cout << "\nIngrese un numero entero a agregar << ";

                int toAdd;

                cin >> toAdd;

                binaryTree->add(toAdd);

                break;

            case 2:

                cout << "Eliminar..." << endl;

                cout << "\nIngrese un numero entero a eliminar << ";

                int toDelete;

                cin >> toDelete;

                binaryTree->deleteNode(toDelete);

                break;

            case 3:

                cout << "Listar..." << endl;

                binaryTree->inorder();

                break;

            case 4:

                cout << "Buscar..." << endl;

                cout << "\nIngrese el numero entero a buscar << ";

                int toFind;

                cin >> toFind;

                int found;

                Node* nodeFound;

                nodeFound = binaryTree->find(toFind);

                if (nodeFound != NULL) {

                    found = nodeFound->value;

                    if (found == toFind) {

                        cout << "Elemento encontrado!" << endl;

                    } else {

                        cout << "El elemento no existe :'(" << endl;

                    }

                } else {

                    cout << "El elemento no existe :'(" << endl;

                }

                break;

            case 5:

                cout << "Exportando..." << endl;

                binaryTree->show();

                break;

            case 6:

                cout << "Insertando datos..." << endl;

                if (inputFile.open(QIODevice::ReadOnly)) {

                   QTextStream in(&inputFile);

                   while (!in.atEnd()) {

                      int number = in.readLine().trimmed().toInt();

                      binaryTree->add(number);

                   }
                   inputFile.close();
                }

                break;

            case 7:

                cout << "Saliendo..." << endl;

                inside = false;

                break;

            default:

                cout << "Opción incorrecta :(" << endl;

                break;
        }

    }

    cout << "Here" << endl;

}
