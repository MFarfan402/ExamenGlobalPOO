#include <iostream>
using namespace std;


class SimpleList {
    public: 
        struct Node 
        {
            int number;
            Node* nextNode;
        } *first, * last;
        void PrintList(bool);
        void InsertNode(int);
        int SearchNode(int);
        bool ModifyNode(int, int);
        SimpleList(){};
        bool DeleteNode(int);
};

class Queue : public SimpleList {
    public: 
        bool DeleteNode();
        Queue(){};
};


int ShowListsMenu();
void ShowOperationMenu(SimpleList, Queue, bool);

int main()
{
    SimpleList list;
    Queue queue;
    int listOption = 0;
    while (listOption != 3)
    {
        listOption = ShowListsMenu();
        if (listOption == 1) ShowOperationMenu(list, queue, true);
        else if (listOption == 2) ShowOperationMenu(list, queue, false);
    } 
    cout << "\n\n\tSaliendo del programa\n\n\n";
}

int ShowListsMenu()
{
    int option = 0;
    do
    {
        system("cls");
        cout << "\n\n\tSeleccione la lista con la que desea operar.\n\n";
        cout << "[1]. Lista simple.\n[2]. Cola. (FiFo)\n[3]. Salir del programa.\n\n";
        cin >> option;
    } while (option < 1 || option > 3);
    system("cls");
    return option;
}
void ShowOperationMenu(SimpleList simpleList, Queue queue, bool isList)
{
    int option = 0, operationNumber = 0, auxiliarNumber = 0, endSesion = 0;
    do {
        do
        {
            cout << "\n\n\n\tOperaciones disponibles para ";
            (isList) ? cout << "lista simple enlazada.\n\n" : cout << "cola (primero en entrar, primero en salir).\n\n";
            cout << "[1]. Insertar nodo.\n[2]. Buscar nodo.\n[3]. Modificar nodo.\n[4]. Eliminar nodo.\n";
            cout << "[5]. Imprimir lista\n[6]. Regresar al menu anterior\n\n";
            cin >> option;
            system("cls");
        } while (option < 1 || option > 6);
        
        switch (option)
        {
        case 1:
            cout << "\n\tNumero a insertar:\t"; cin >> operationNumber;
            (isList) ? simpleList.InsertNode(operationNumber) : queue.InsertNode(operationNumber);
            cout << "\nNumero insertado correctamente.\n\n";
            break;
        case 2:
            cout << "\n\tNumero a buscar:\t"; cin >> operationNumber;
            auxiliarNumber = (isList) ? simpleList.SearchNode(operationNumber) : queue.SearchNode(operationNumber);
            (auxiliarNumber == NULL) ?
                cout << "\nNo se encuentra el numero en la lista" :
                cout << "\nEl numero se encuentra en la posicion " << auxiliarNumber;
            break;
        case 3:
            cout << "\n\tNumero a modificar:\t"; cin >> operationNumber;
            cout << "\tNumero nuevo:\t\t"; cin >> auxiliarNumber;
            if (isList)
            {
                simpleList.ModifyNode(operationNumber, auxiliarNumber) ?
                cout << "\nNumero modificado correctamente" :
                cout << "\nNo se encuentra el numero en la lista";
            }
            else
            {
                queue.ModifyNode(operationNumber, auxiliarNumber) ?
                    cout << "\nNumero modificado correctamente" :
                    cout << "\nNo se encuentra el numero en la lista";
            }
            break;
        case 4:
            if (isList)
            {
                cout << "\n\tNumero a eliminar:\t"; cin >> operationNumber;
                simpleList.DeleteNode(operationNumber) ?
                    cout << "\n\nNumero eliminado" :
                    cout << "\n\nNo se encuentra el numero en la lista";
            }
            else
            {
                queue.DeleteNode() ?
                    cout << "\n\nNumero eliminado usando la propiedad FirstIn, FirstOut." :
                    cout << "\n\nNo se encuentra el numero en la lista";
            }
            break;
        case 5:
            cout << "\n\tLista de elementos:\n\n";
            (isList) ? simpleList.PrintList(true) : queue.PrintList(false);
            break;
        case 6:
            do 
            {
                system("cls");
                cout << "\n\tSe perderan todos los elementos, deseas salir:\n\n";
                cout << "[1]. Si, regresar al menu anterior.\n[2]. No, continuar.\n\n";
                cin >> endSesion;
            } while (endSesion < 1 || endSesion > 2);
            break;
        default:
            cout << "\n\nOpcion no identificada";
        }
    } while (option != 6 || endSesion != 1);
}

void SimpleList::InsertNode(int number)
{
    Node* newNode = new Node();
    newNode->number = number;
    if (first == NULL)
    {
        first = newNode;
        first->nextNode = NULL;
        last = newNode;
    }
    else
    {
        last->nextNode = newNode;
        newNode->nextNode = NULL;
        last = newNode;
    }
}
void SimpleList::PrintList(bool isList)
{
    if (first == NULL)
    {
        cout << "La lista esta vacia";
        return;
    }
    Node* actualNode = new Node();
    actualNode = first;
    while (actualNode != NULL)
    {
        cout << actualNode->number;
        (isList) ? cout << " -> " : cout << " <- ";
        actualNode = actualNode->nextNode;
    }
    if (isList) cout << "NULL";
}
int SimpleList::SearchNode(int number)
{
    if (first == NULL)
    {
        cout << "La lista esta vacia";
        return NULL;
    }

    Node* actualNode = new Node();
    actualNode = first;
    int position = 0;
    while (actualNode != NULL)
    {
        position++;
        if (actualNode->number == number)
            return position;
        else
            actualNode = actualNode->nextNode;
    }
    return NULL;
}
bool SimpleList::ModifyNode(int oldNumber, int newNumber)
{
    if (first == NULL)
    {
        cout << "La lista esta vacia";
        return false;
    }
    Node* actualNode = new Node();
    actualNode = first;
    while (actualNode != NULL)
    {
        if (actualNode->number == oldNumber)
        {
            actualNode->number = newNumber;
            return true;
        } 
        else
            actualNode = actualNode->nextNode;
    }
    return false;
}
bool SimpleList::DeleteNode(int number)
{
    if (first == NULL)
    {
        cout << "La lista esta vacia";
        return false;
    }
    Node* actualNode = new Node();
    actualNode = first;
    if (first->number == number)
    {
        first = actualNode->nextNode;
        return true;
    }
    while (actualNode->nextNode != NULL)
    {
        if (actualNode->nextNode->number == number)
        {
            actualNode->nextNode = actualNode->nextNode->nextNode;
            return true;
        }
        else
            actualNode = actualNode->nextNode;
    }
    return false;
}
bool Queue::DeleteNode()
{
    if (first == NULL)
    {
        cout << "La lista esta vacia";
        return false;
    }
    Node* actualNode = new Node();
    first = first->nextNode;
    return true;
}

