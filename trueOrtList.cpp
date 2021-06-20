#include <iostream>
#include <string>

using namespace std;

struct nodeTiaraSpikes
{
    string discipline;
    int assessment;
    nodeTiaraSpikes* BottomElemnt;
};

struct nodeMain
{
    string nameStudent;
    float average;
    nodeMain* AfterElement;
    nodeTiaraSpikes* BottomElemnt;
};

class OrthogonalList
{
private:
    nodeMain* pheadMain;
    nodeTiaraSpikes* pheadTiara;

    // Функции для построения ортогонального списка
    nodeTiaraSpikes* constructionTiara();
    // Удаление ортогонального списка
    void tiarClear();
    // Функции вывода
    float printTiara();
public:
    OrthogonalList();
    ~OrthogonalList();
    // Функции для построения ортогонального списка
    void constructionMain();
    // Удаление ортогонального списка
    void mainClear();
    // Функции вывода
    void printMain();
    // Функция поиска звена
    nodeMain* searchMain(string);
    nodeTiaraSpikes* searchTiara(string);
    void setPheadTiar(nodeTiaraSpikes* Res) { pheadTiara = Res; };
    // Функции добавления звеньев
    void addMain(string);
    void addTiaraAfter(nodeTiaraSpikes*, string, int);
    void addTiaraBefore(nodeTiaraSpikes*, string, int);
    // Удаление звеньев
    void deleteLinkAfter(nodeTiaraSpikes*);
    void deleteLink(nodeTiaraSpikes*);
};

OrthogonalList::OrthogonalList()
{
    pheadMain = new(nodeMain);
}

OrthogonalList::~OrthogonalList()
{
    delete pheadMain;
}

void OrthogonalList::constructionMain()
{
    nodeMain* temp;
    string name;

    temp = pheadMain;
    temp->AfterElement = NULL;

    cout << "Input name student:" << endl;
    cin >> name;
    while (name != "0")
    {
        temp->AfterElement = new (nodeMain){ name, 0, NULL, constructionTiara()};
        temp = temp->AfterElement;
        cout << "Input name student:" << endl;
        cin >> name;
    }
}

nodeTiaraSpikes* OrthogonalList::constructionTiara()
{
    nodeTiaraSpikes* temp;
    string discipline;
    int assessment;

    pheadTiara = new(nodeTiaraSpikes);
    temp = pheadTiara;
    temp->BottomElemnt = NULL;

    cout << "Input name discipline:" << endl;
    cin >> discipline;
    cout << "Input assessment student:" << endl;
    cin >> assessment;
    while (discipline != "0")
    {
        temp->BottomElemnt = new(nodeTiaraSpikes){ discipline, assessment, NULL};
        temp = temp->BottomElemnt;
        cout << "Input discipline student:" << endl;
        cin >> discipline;
        cout << "Input assessment student:" << endl;
        cin >> assessment;
    }
    return pheadTiara;
}

void OrthogonalList::mainClear()
{
    nodeMain* temp, * temp1;
    temp = pheadMain;
    temp1 = temp->AfterElement;
    while (temp1 != NULL)
    {
        temp = temp1;
        temp1 = temp1->AfterElement;
        pheadTiara = temp->BottomElemnt;
        tiarClear();
        delete temp;
    }
}

void OrthogonalList::tiarClear()
{
    nodeTiaraSpikes* temp, * temp1;
    temp = pheadTiara;
    temp1 = temp->BottomElemnt;
    while (temp1 != NULL)
    {
        temp = temp1;
        temp1 = temp1->BottomElemnt;
        delete temp;
    }
}

void OrthogonalList::printMain()
{
    cout << "Print info all student:" << endl;
    nodeMain* temp;
    temp = pheadMain->AfterElement;
    while (temp != NULL)
    {
        cout << endl << "Students: " << temp->nameStudent << endl;
        pheadTiara = temp->BottomElemnt;
        temp->average = printTiara();
        cout << "Average rating: " << temp->average;
        temp = temp->AfterElement;
    }
    cout << endl;
}

float OrthogonalList::printTiara()
{
    float tempAverage = 0;
    int up = 0, down = 0;
    nodeTiaraSpikes* temp;
    temp = pheadTiara;
    temp = temp->BottomElemnt;
    while (temp != NULL)
    {
        up += temp->assessment;
        down++;
        cout << "Discipline: " << temp->discipline << " | Assessment: " << temp->assessment << endl;
        temp = temp->BottomElemnt;
    }
    tempAverage = up / down;
    return tempAverage;
}

nodeMain* OrthogonalList::searchMain(string name)
{
    nodeMain* Res, * temp;
    Res = NULL;
    temp = pheadMain->AfterElement;
    while (Res == NULL && temp != NULL)
    {
        if (temp->nameStudent == name) Res = temp;
        else temp = temp->AfterElement;
    }
    return Res;
}

nodeTiaraSpikes* OrthogonalList::searchTiara(string discipline)
{
    nodeTiaraSpikes* Res, * temp;
    Res = NULL;
    temp = pheadTiara->BottomElemnt;
    while (Res == NULL && temp != NULL)
    {
        if (temp->discipline == discipline) Res = temp;
        else temp = temp->BottomElemnt;
    }
    return Res;
}

void OrthogonalList::addMain(string name)
{

    nodeMain* temp, * Res;
    Res = pheadMain->AfterElement;
    while (Res->AfterElement != NULL)
    {
        Res = Res->AfterElement;
    }
    temp = Res->AfterElement;
    temp = new(nodeMain){ name, 0, NULL, constructionTiara()};
    Res->AfterElement = temp;
}

void OrthogonalList::addTiaraAfter(nodeTiaraSpikes* Res, string discipline, int assessment)
{
    nodeTiaraSpikes* temp;
    temp = new(nodeTiaraSpikes){ discipline, assessment, Res->BottomElemnt};
    Res->BottomElemnt = temp;
}

void OrthogonalList::addTiaraBefore(nodeTiaraSpikes* Res, string discipline, int assessment)
{
    nodeTiaraSpikes* temp;
    temp = new(nodeTiaraSpikes){ discipline, assessment, Res->BottomElemnt };
    Res->BottomElemnt = temp;
    Res->assessment = assessment;
    Res->discipline = discipline;
    Res->BottomElemnt = temp;
}

void OrthogonalList::deleteLinkAfter(nodeTiaraSpikes* Res)
{
    nodeTiaraSpikes* temp;
    temp = Res->BottomElemnt;
    if (Res->BottomElemnt != NULL)
    {
        Res->BottomElemnt = (Res->BottomElemnt)->BottomElemnt;
        delete temp;
    }
}

void OrthogonalList::deleteLink(nodeTiaraSpikes* Res)
{
    nodeTiaraSpikes* temp;
    if (Res->BottomElemnt != NULL)
    {
        temp = Res->BottomElemnt;
        Res->discipline = (Res->BottomElemnt)->discipline;
        Res->assessment = (Res->BottomElemnt)->assessment;
        Res->BottomElemnt = (Res->BottomElemnt)->BottomElemnt;
        delete temp;
    }
    else
    {
        cout << "Unable to delete" << endl;
    }
}

int choice_info();

int main()
{
    OrthogonalList orList;
    orList.constructionMain();

    nodeMain* Res;
    nodeTiaraSpikes* ResTiar;
    

    int choice = 0;
    while (true)
    {
        orList.printMain();
        choice = choice_info();
        if (choice == 1)
        {
            string name;
            cout << "Input name student:" << endl;
            cin >> name;
            orList.addMain(name);
        }
        if (choice == 2)
        {
            string name;
            cout << "Input search name student:" << endl;
            cin >> name;
            Res = orList.searchMain(name);
            if (Res != NULL)
            {
                string discipline;
                orList.setPheadTiar(Res->BottomElemnt);
                cout << "Input discipline after add link:" << endl;
                cin >> discipline; 
                ResTiar = orList.searchTiara(discipline);
                if (ResTiar != NULL)
                {
                    cout << "Input discipline:" << endl;
                    cin >> discipline;
                    int assessment;
                    cout << "Input assessment student:" << endl;
                    cin >> assessment;
                    orList.addTiaraAfter(ResTiar, discipline, assessment);
                }
            }
            else cout << "There is no such student" << endl;
        }
        if (choice == 3)
        {
            string name;
            cout << "Input search name student:" << endl;
            cin >> name;
            Res = orList.searchMain(name);
            if (Res != NULL)
            {
                string discipline;
                orList.setPheadTiar(Res->BottomElemnt);
                cout << "Input discipline after add link:" << endl;
                cin >> discipline;
                int assessment;
                cout << "Input assessment student:" << endl;
                cin >> assessment;
                ResTiar = orList.searchTiara(discipline);
                if (ResTiar != NULL)
                {
                    orList.addTiaraAfter(ResTiar, discipline, assessment);
                }
            }
            else cout << "There is no such student" << endl;
        }
        if (choice == 4)
        {
            string name;
            cout << "Input search name student:" << endl;
            cin >> name;
            Res = orList.searchMain(name);
            if (Res != NULL)
            {
                string discipline;
                orList.setPheadTiar(Res->BottomElemnt);
                cout << "Input discipline after delete link:" << endl;
                cin >> discipline;
                ResTiar = orList.searchTiara(discipline);
                if (ResTiar != NULL)
                {
                    orList.deleteLinkAfter(ResTiar);
                }
            }
            else cout << "There is no such student" << endl;
        }
        if (choice == 5)
        {
            string name;
            cout << "Input search name student:" << endl;
            cin >> name;
            Res = orList.searchMain(name);
            if (Res != NULL)
            {
                string discipline;
                orList.setPheadTiar(Res->BottomElemnt);
                cout << "Input discipline delete link:" << endl;
                cin >> discipline;
                ResTiar = orList.searchTiara(discipline);
                if (ResTiar != NULL)
                {
                    orList.deleteLink(ResTiar);
                }
            }
            else cout << "There is no such student" << endl;
        }
        if (choice == 0)
        {
            break;
        }
    }
    orList.mainClear();
}

int choice_info()
{
    int choice = 0;
    cout << "Choice:" << endl;
    cout << "Add student: 1" << endl;
    cout << "Add discipline: 2" << endl;
    cout << "Add discipline after: 3" << endl;
    cout << "Delete discipline After: 4" << endl;
    cout << "Delete Link: 5" << endl;
    cout << "Exit: 0" << endl;
    cin >> choice;
    return choice;
}