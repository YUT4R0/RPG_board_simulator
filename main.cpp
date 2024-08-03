#include <cstdlib>
#include <iostream>
#include <string>

#define TAB_SIZE 10
#define HT_SIZE 43
#define RANGE 3
#define BASE 31

typedef std::string Name;
typedef std::string Race;
typedef int Position;
typedef unsigned long long Force;
typedef unsigned long long ull;

class NodeS {
public:
    long long value;
    NodeS *next;
    NodeS(long long val) : value(val), next(nullptr) {}
};

template<typename T> class SortedLinkedList {
private:
    NodeS *head;
public:
    SortedLinkedList() : head(nullptr) {}
    ~SortedLinkedList()
    {
        NodeS *current = head;
        NodeS *nextNode = nullptr;
        while (current != nullptr) {
            nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
    void insert(long long value)
    {
        NodeS *newNode = new NodeS(value);
        if (head == nullptr || head->value <= value) {
            newNode->next = head;
            head = newNode;
        } else {
            NodeS *current = head;
            while (current->next != nullptr && current->next->value > value)
                current = current->next;
            newNode->next = current->next;
            current->next = newNode;
        }
    }
    long long getMax() const
    {
        return head->value;
    }
    void display() const
    {
        NodeS *current = head;
        while (current != nullptr) {
            std::cout << current->value << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
    bool isEmpty() const
    {
        return head == nullptr;
    }
    void clear()
    {
        NodeS *current = head;
        while (current != nullptr) {
            NodeS *nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
    }
};

std::string toLowerCase(const std::string &str)
{
    std::string lowerStr = str;
    for (size_t i = 0; i < lowerStr.length(); ++i)
        if (lowerStr[i] >= 'A' && lowerStr[i] <= 'Z')
            lowerStr[i] = lowerStr[i] + ('a' - 'A');
    return lowerStr;
}

template<typename T> class OutputNode {
public:
    T data;
    OutputNode<T> *next;
    OutputNode() : next(nullptr) {}
};

template<typename T> class OutputList {
private:
    OutputNode<T> *first;
    OutputNode<T> *last;
public:
    OutputList() : first(new OutputNode<T>), last(first) {}
    void insert(T data)
    {
        last->next = new OutputNode<T>;
        last = last->next;
        last->data = data;
        last->next = nullptr;
    }
    void show()
    {
        OutputNode<T> *current = first->next;
        while (current != nullptr) {
            std::cout << current->data << std::endl;
            current = current->next;
        }
    }
};

template<typename T> class Node {
public:
    T data;
    Node<T> *next;
    Node() : next(nullptr) {}
};

template<typename T> class Stack {
private:
    Node<T> *top;
    int size;
    int force;
public:
    Stack() : top(nullptr), size(0) {}
    bool isEmpty()
    {
        return size == 0;
    }
    bool isSoldier()
    {
        return size == 1;
    }
    bool isTroop()
    {
        return size > 1; 
    }
    int getSize()
    {
        return size;
    }
    void push(T data)
    {
        Node<T> *newNode = new Node<T>;
        newNode->data = data;
        if (isEmpty() || newNode->data.getForce() > top->data.getForce()) {
            newNode->next = top;
            top = newNode;
        } else {
            Node<T> *current = top;
            while (current->next != nullptr && current->next->data.getForce() >= newNode->data.getForce())
                current = current->next;
            newNode->next = current->next;
            current->next = newNode;
        }
        ++size;
    }
    T pop()
    {
        Node<T> *temp = top;
        T poppedData = temp->data;
        top = top->next;
        delete temp;
        temp = nullptr;
        --size;
        return poppedData;
    }
    void show()
    {
        Node<T> *current = top;
        while (current != nullptr) {
            std::cout << current->data.getName() << "\n";
            current = current->next;
        }
    }
    std::string showTop()
    {
        if (isEmpty())
            return "";
        std::string soldadoNoTopo;
        soldadoNoTopo = top->data.getName();
        return soldadoNoTopo;
    }
    T &takeLeader()
    {
        return top->data;
    }
    T popQueueLeader()
    {
        T dataLeader = takeLeader();
        return dataLeader.capturados.dequeue();
    }
    ull troopForce()
    {
        ull force = 0;
        Node<T> *current = top;
        while (current != nullptr) {
            force += current->data.getForce();
            current = current->next;
        }
        return force;
    }
};

template<typename T> class Queue {
private:
    Node<T> *front;
    Node<T> *rear;
    int current_LEN;
public:
    Queue() : front(nullptr), rear(nullptr), current_LEN(0)
    {
        front = rear;
    }
    bool isEmpty()
    {
        return current_LEN == 0;
    }
    int getSize()
    {
        return current_LEN;
    }
    void enqueue(T data)
    {
        Node<T> *newNode = new Node<T>;
        newNode->data = data;
        newNode->next = nullptr;
        if (isEmpty())
            front = rear = newNode;
        else {
            rear->next = newNode;
            rear = newNode;
        }
        ++current_LEN;
    }
    T dequeue()
    {
        Node<T> *temp = front;
        T dequeuedData = temp->data;
        front = front->next;
        delete temp;
        --current_LEN;
        return dequeuedData;
    }
    void show()
    {
        Node<T> *current = front;
        while (current != nullptr) {
            std::cout << current->data.getName() << "\n";
            current = current->next;
        }
    }

    ull queueForce() {
    ull force = 0;
    Node<T> *current = front;
    while (current != nullptr) {
        force += current->data.getForce();
        current = current->next;
    }
    return force;
    }
};

template<typename T> class List {
private:
    Node<T> *first;
    Node<T> *last;
    int size;

    Node<T> *getNodeByPos(int pos) {
    Node<T> *current = first->next;
    for (int i = 0; i < pos; ++i) {
        current = current->next;
    }
    return current;
    }
    Node<T> *predecessor(Node<T> *target) {
    Node<T> *current = first;
    while (current->next != target && current != nullptr) {
        current = current->next;
    }
    return current;
    }

    void removeNode(Node<T> *target) {
    Node<T> *pred = predecessor(target);
    pred->next = target->next;
    if (pred->next == nullptr) {
        last = pred;
    }
    delete target;
    --size;
    }

public:
    List() : first(new Node<T>), last(first), size(0) {}

    int getSize()
    {
        return size;
    }
    bool isEmpty()
    {
        return size == 0;
    }
    void insert(T data)
    {
        last->next = new Node<T>;
        last = last->next;
        last->next = nullptr;
        last->data = data;
        ++size;
    }
    void print() const
    {
        Node<T> *current = first->next;
        while (current != nullptr) {
            current->data.print();
            current = current->next;
        }
    }
    T getItemByPos(int pos)
    {
        if (!isEmpty()) {
            Node<T> *current = first->next;
            for (int i = 0; i < pos; ++i) {
            current = current->next;
        }
        return current->data;
        } else
            return first->data;
    }
    void removeItemByPos(int pos)
    {
        if (!isEmpty()) {
            Node<T> *target = getNodeByPos(pos);
            if (target != nullptr)
                removeNode(target);
            
        }
    }
    T *getItemByValue(Name value) 
    {
        Node<T> *current = first->next;
        while (current != nullptr) {
            if (current->data.getName() == value)
                return &current->data;
            else
                current = current->next;
        }
        return nullptr;
    }
    void removeItemByValue(Name value)
    {
        Node<T> *current = first->next;
        while (current != nullptr) {
            if (current->data.getName() == value) {
                removeNode(current);
                break;
            }
            current = current->next;
        }
    }
    T *getFirstItem()
    {
        if (!isEmpty())
            return &first->next->data;
        return nullptr;
    }
    Node<T> *getFirstNode()
    {
        return first->next;
    }
};

class Soldier {
private:
    Name name;
    Race race;
    Force aux, force, troopForce;
    Position i, j;
public:
    Queue<Soldier> capturados;
    Stack<Soldier> unidade;
    Soldier() : name(""), race(""), force(0), i(0), j(0) {}
    Soldier(Name _name, Race _race, Force _force, Position _i, Position _j)
        : name(_name), race(_race), force(_force), i(_i), j(_j)
    {
        this->aux = force;
    }
    Name getName() const
    {
        return name;
    }
    Race getRace() const
    {
        return race;
    }
    Position getPosition_i() const
    {
        return i;
    }
    Position getPosition_j() const
    {
        return j;
    }
    std::string showSoldierTroop()
    {
        std::string nome = unidade.showTop();
        std::string frc = std::to_string(getTroopForce());
        std::string printSoldierTroop =
            "[[" + nome + " " + getRace() + " " + frc + "]]";
        return printSoldierTroop;
    }
    std::string showSoldier()
    {
        std::string frc = std::to_string(unidade.takeLeader().getForce());
        std::string printSoldier = "[" + unidade.takeLeader().getName() + " " +
                                     getRace() + " " + frc + "]";
        return printSoldier;
    }
    void setForce()
    {
        this->force = force + capturados.queueForce();
    }
    void setTroopForce()
    {
        this->troopForce = unidade.troopForce();
    }
    void setNewForce()
    {
        this->force = aux + capturados.queueForce();
    }
    std::string getLowerCaseNameRace() const
    {
        return toLowerCase(name + race);
    }
    void print() const
    {
        std::cout << "Name: " << name << ", Race: " << race << ", Force: " << force
                    << std::endl;
    }
    Force getForce()
    {
        return force;
    }
    Force getTroopForce()
    {
        return troopForce;
    }
};

template<typename T> class HashTable {
private:
    List<T> array[HT_SIZE];
    ull fastExp(ull base, ull expoent, ull mod)
    {
        ull ans = 1;
        while (expoent) {
            if (expoent & 1)
                ans = ((ans % mod) * (base % mod)) % mod;
            base = ((base % mod) * (base % mod)) % mod;
            expoent >>= 1;
        }
        return ans % mod;
    }
    ull hash(std::string value)
    {
        ull hash = 0;
        ull keySize = value.size();
        for (ull i = 0; i < keySize; i++)
            hash = (hash + value[i] * (fastExp(BASE, keySize - i - 1, HT_SIZE))) % HT_SIZE;
        return hash % HT_SIZE;
    }
public:
    HashTable() {}
    void insert(T data)
    {
        int index = hash(data.getLowerCaseNameRace());
        array[index].insert(data);
    }
    T *getDataByKey(Name key)
    {
        int index = hash(key);
        return array[index].getItemByValue(key);
    }
    T popDataByKey(Name key)
    {
        int index = hash(key);
        T data = *array[index].getItemByValue(key);
        array[index].removeItemByValue(key);
        return data;
    }
    void printAll() const
    {
        for (int i = 0; i < HT_SIZE; ++i)
            array[i].print();
    }
    float transferForce(Soldier soldadoConsultante)
    {
        std::string key = soldadoConsultante.getLowerCaseNameRace();
        ull index = hash(key);
        Node<Soldier> *currentNode = array[index].getFirstNode();
        ull forcaTotalTransferencia = 0;
        while (currentNode != nullptr) {
            Soldier &alma = currentNode->data;
            ull forcaDasAlmas = alma.getForce();
            forcaTotalTransferencia += forcaDasAlmas;
            currentNode = currentNode->next;
        }
        return 0.7 * forcaTotalTransferencia;
    }
};

class Tabuleiro {
private:
    Soldier *mapa[TAB_SIZE][TAB_SIZE];
    int linhas;
    int colunas;
    OutputList<std::string> outputList;
    HashTable<Soldier> santuario;
    SortedLinkedList<ull> listaOrdenada;

public:
    Tabuleiro(int m, int n) : linhas(m), colunas(n) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
        mapa[i][j] = nullptr;
        }
    }
    }

    bool posEmpty(int i, int j)
    {
        return mapa[i][j] == nullptr;
    }

    bool verificaSupremacia(int i, int j, std::string race) {
    for (int x = 0; x < TAB_SIZE; ++x) {
        for (int y = 0; y < TAB_SIZE; ++y) {
        if (!(x == i && y == j)) {
            if (mapa[x][y] != nullptr && mapa[x][y]->getRace() != race) {
            return false;
            }
        }
        }
    }
    return true;
    }

    bool verificaEliminacao(int i, int j, std::string race) {
    for (int x = 0; x < TAB_SIZE; ++x) {
        for (int y = 0; y < TAB_SIZE; ++y) {
        if (!(x == i && y == j)) {
            if (mapa[x][y] != nullptr && mapa[x][y]->getRace() == race) {
            return false;
            }
        }
        }
    }
    return true;
    }

    ull maxAtaqueUnidadeSimulacao(int i1, int j1, int i2, int j2,
                                ull forcaAtacante, ull forcaDefesa) {
    ull forcaSimulada = forcaAtacante;
    ull condicaoSantuario = (2.0 / 3.0) * forcaDefesa;

    if (forcaAtacante > forcaDefesa) {
        if (!mapa[i2][j2]->unidade.takeLeader().capturados.isEmpty()) {
        return forcaAtacante;
        } else if (mapa[i2][j2]->unidade.takeLeader().capturados.isEmpty()) {
        if (mapa[i2][j2]->unidade.isTroop()) {
            forcaSimulada += mapa[i2][j2]->getTroopForce();
            return forcaSimulada;
        } else if (mapa[i2][j2]->unidade.isSoldier()) {
            forcaSimulada += mapa[i2][j2]->unidade.takeLeader().getForce();
            return forcaSimulada;
        }
        }
    } else if (forcaAtacante <= condicaoSantuario) {
        float forcaDasAlmas = 0;
        forcaDasAlmas =
            santuario.transferForce(mapa[i1][j1]->unidade.takeLeader());
        forcaDasAlmas += forcaAtacante;

        if (forcaDasAlmas > forcaDefesa) {
        if (!mapa[i2][j2]->unidade.takeLeader().capturados.isEmpty()) {
            return forcaAtacante;
        } else if (mapa[i2][j2]->unidade.takeLeader().capturados.isEmpty()) {
            if (mapa[i2][j2]->unidade.isTroop()) {
            forcaSimulada += mapa[i2][j2]->getTroopForce();
            return forcaSimulada;
            } else if (!mapa[i2][j2]->unidade.isTroop()) {
            forcaSimulada += mapa[i2][j2]->unidade.takeLeader().getForce();
            return forcaSimulada;
            }
        }
        } else if (forcaDasAlmas < forcaDefesa) {
        return forcaSimulada;
        } else if (forcaDasAlmas == forcaDefesa) {
        return forcaSimulada;
        }
    } else if (forcaAtacante < forcaDefesa) {
        return forcaSimulada;
    } else if (!(forcaAtacante <= condicaoSantuario) &&
                 forcaAtacante < forcaDefesa) {
        return forcaSimulada;
    } else if (forcaAtacante == forcaDefesa) {
        return forcaSimulada;
    }
    return 0;
    }

    void realizaContraAtaque(int &i1, int &j1, int &i2, int &j2) {

    if (mapa[i2][j2]->unidade.isTroop()) {
        if (!mapa[i2][j2]->unidade.takeLeader().capturados.isEmpty()) {
        santuario.insert(
            mapa[i2][j2]->unidade.takeLeader().capturados.dequeue());
        } else {
        mapa[i1][j1]->unidade.takeLeader().capturados.enqueue(
            mapa[i2][j2]->unidade.pop());

        mapa[i2][j2]->setTroopForce();

        mapa[i1][j1]->unidade.takeLeader().setNewForce();
        mapa[i1][j1]->setTroopForce();
        }
    } else if (mapa[i2][j2]->unidade.isSoldier()) {
        // HERE
        if (!mapa[i2][j2]->unidade.takeLeader().capturados.isEmpty()) {
        santuario.insert(
            mapa[i2][j2]->unidade.takeLeader().capturados.dequeue());

        } else {

        std::string racaEliminada = mapa[i2][j2]->getRace();
        std::string l2 = std::to_string(i2);
        std::string c2 = std::to_string(j2);

        mapa[i1][j1]->unidade.takeLeader().capturados.enqueue(
            mapa[i2][j2]->unidade.takeLeader());
        mapa[i1][j1]->unidade.takeLeader().setNewForce();
        mapa[i1][j1]->setTroopForce();

        delete mapa[i2][j2];

        mapa[i2][j2] = mapa[i1][j1];
        mapa[i1][j1] = nullptr;

        outputList.insert(
            "unidade " + mapa[i2][j2]->unidade.takeLeader().getName() + "+" +
            mapa[i2][j2]->getRace() + " avanca para (" + l2 + ", " + c2 + ")");
        if (verificaEliminacao(i2, j2, racaEliminada)) {
            outputList.insert(racaEliminada + " foi eliminada");
        } else if (verificaSupremacia(i2, j2, mapa[i2][j2]->getRace())) {
            outputList.insert(mapa[i2][j2]->getRace() +
                            " tem supremacia sobre Tau!");
        }
        }
    }
    }

    void realizaAtaque(int &i1, int &j1, int &i2, int &j2) {

    if (mapa[i2][j2]->unidade.isTroop()) {

        if (!mapa[i2][j2]->unidade.takeLeader().capturados.isEmpty()) {

        outputList.insert("Ataque bem sucedido");
        santuario.insert(
            mapa[i2][j2]->unidade.takeLeader().capturados.dequeue());

        } else {

        outputList.insert("Ataque bem sucedido");
        mapa[i1][j1]->unidade.takeLeader().capturados.enqueue(
            mapa[i2][j2]->unidade.pop());

        mapa[i2][j2]->setTroopForce();

        mapa[i1][j1]->unidade.takeLeader().setNewForce();
        mapa[i1][j1]->setTroopForce();
        }
    }

    if (mapa[i2][j2]->unidade.isSoldier()) {
        // HERE
        if (!mapa[i2][j2]->unidade.takeLeader().capturados.isEmpty()) {
        outputList.insert("Ataque bem sucedido");
        santuario.insert(
            mapa[i2][j2]->unidade.takeLeader().capturados.dequeue());

        } else {

        std::string racaEliminada = mapa[i2][j2]->getRace();
        std::string l2 = std::to_string(i2);
        std::string c2 = std::to_string(j2);

        mapa[i1][j1]->unidade.takeLeader().capturados.enqueue(
            mapa[i2][j2]->unidade.takeLeader());
        mapa[i1][j1]->unidade.takeLeader().setNewForce();
        mapa[i1][j1]->setTroopForce();

        delete mapa[i2][j2];

        mapa[i2][j2] = mapa[i1][j1];

        mapa[i1][j1] = nullptr;

        outputList.insert("Ataque bem sucedido");
        outputList.insert(
            "unidade " + mapa[i2][j2]->unidade.takeLeader().getName() + "+" +
            mapa[i2][j2]->getRace() + " avanca para (" + l2 + ", " + c2 + ")");
        if (verificaEliminacao(i2, j2, racaEliminada)) {
            outputList.insert(racaEliminada + " foi eliminada");
        } else if (verificaSupremacia(i2, j2, mapa[i2][j2]->getRace())) {
            outputList.insert(mapa[i2][j2]->getRace() +
                            " tem supremacia sobre Tau!");
        }
        }
    }
    }

    void simulaAtaque(int &i1, int &j1, int &i2, int &j2, ull ataque,
                    ull defesa) {
    ull condicaoSantuario = (2.0 / 3.0) * defesa;

    if (ataque > defesa) {
        realizaAtaque(i1, j1, i2, j2);
    } else if (ataque <= condicaoSantuario) {
        float forcaDasAlmas = 0;
        forcaDasAlmas =
            santuario.transferForce(mapa[i1][j1]->unidade.takeLeader());
        forcaDasAlmas += ataque;
        if (forcaDasAlmas > defesa) {
        realizaAtaque(i1, j1, i2, j2);
        } else if (forcaDasAlmas < defesa) {
        outputList.insert("Contra-ataque!");
        realizaContraAtaque(i2, j2, i1, j1);
        }
    } else if (!(ataque <= condicaoSantuario) && ataque < defesa) {
        realizaContraAtaque(i2, j2, i1, j1);
    }
    }

    bool movimentoValido(int i, int j, int i2, int j2) {
    if (i < 0 || i >= TAB_SIZE || j < 0 || j >= TAB_SIZE || i2 < 0 ||
        i2 >= TAB_SIZE || j2 < 0 || j2 >= TAB_SIZE) {
        return false;
    }

    int distancia_vertical = abs(i - i2);
    int distancia_horizontal = abs(j - j2);

    if (distancia_vertical + distancia_horizontal == RANGE)
        return true;
    else
        return false;
    }

    void movaUnidade(int i1, int j1, int i2, int j2) {
    if (movimentoValido(i1, j1, i2, j2)) {
        if (mapa[i1][j1] != nullptr) {
        if (mapa[i1][j1] != nullptr && mapa[i2][j2] == nullptr) {
            mapa[i2][j2] = mapa[i1][j1];
            mapa[i1][j1] = nullptr;
        } else if (mapa[i1][j1]->getRace() == mapa[i2][j2]->getRace()) {
            if (mapa[i1][j1]->unidade.isTroop() &&
                mapa[i2][j2]->unidade.isTroop()) {
            while (!mapa[i1][j1]->unidade.isEmpty()) {
                mapa[i2][j2]->unidade.push(mapa[i1][j1]->unidade.pop());
            }
            mapa[i1][j1] = nullptr;
            mapa[i2][j2]->setTroopForce();
            } else if (!mapa[i1][j1]->unidade.isTroop() &&
                     mapa[i2][j2]->unidade.isTroop()) {
            mapa[i2][j2]->unidade.push(mapa[i1][j1]->unidade.pop());
            mapa[i1][j1] = nullptr;
            mapa[i2][j2]->setTroopForce();

            } else if (mapa[i1][j1]->unidade.isTroop() &&
                     !mapa[i2][j2]->unidade.isTroop()) {

            while (!mapa[i1][j1]->unidade.isEmpty()) {
                mapa[i2][j2]->unidade.push(mapa[i1][j1]->unidade.pop());
            }

            mapa[i1][j1] = nullptr;
            mapa[i2][j2]->setTroopForce();

            } else if (!mapa[i1][j1]->unidade.isTroop() &&
                     !mapa[i2][j2]->unidade.isTroop()) {
            mapa[i2][j2]->unidade.push(mapa[i1][j1]->unidade.pop());
            mapa[i1][j1] = nullptr;
            mapa[i2][j2]->setTroopForce();
            }
        } else if (mapa[i1][j1]->getRace() != mapa[i2][j2]->getRace()) {
            if (mapa[i1][j1]->unidade.isTroop() &&
                mapa[i2][j2]->unidade.isTroop()) {
            simulaAtaque(i1, j1, i2, j2, mapa[i1][j1]->getTroopForce(),
                         mapa[i2][j2]->getTroopForce());
            } else if (mapa[i1][j1]->unidade.isTroop() &&
                     mapa[i2][j2]->unidade.isSoldier()) {
            simulaAtaque(i1, j1, i2, j2, mapa[i1][j1]->getTroopForce(),
                         mapa[i2][j2]->unidade.takeLeader().getForce());
            } else if (mapa[i1][j1]->unidade.isSoldier() &&
                     mapa[i2][j2]->unidade.isTroop()) {
            simulaAtaque(i1, j1, i2, j2,
                         mapa[i1][j1]->unidade.takeLeader().getForce(),
                         mapa[i2][j2]->getTroopForce());
            } else if (mapa[i1][j1]->unidade.isSoldier() &&
                     mapa[i2][j2]->unidade.isSoldier()) {
            simulaAtaque(i1, j1, i2, j2,
                         mapa[i1][j1]->unidade.takeLeader().getForce(),
                         mapa[i2][j2]->unidade.takeLeader().getForce());
            }
        }
        }
    }
    }

    bool posicaoInvalida(int i, int j) {
    return i < 0 || i >= TAB_SIZE || j < 0 || j >= TAB_SIZE;
    }

    void adicionarSoldado(int i, int j, Soldier *soldado) {

    if (!posicaoInvalida(i, j)) {

        if (mapa[i][j] != nullptr &&
            mapa[i][j]->getRace() == soldado->getRace()) {

        mapa[i][j]->unidade.push(*soldado);
        mapa[i][j]->setTroopForce();

        } else if (mapa[i][j] != nullptr &&
                 mapa[i][j]->getRace() != soldado->getRace()) {
        } else if (mapa[i][j] == nullptr) {
        mapa[i][j] = soldado;
        mapa[i][j]->unidade.push(*mapa[i][j]);
        mapa[i][j]->setTroopForce();
        }
    }
    }

    void imprimeTerritorio(int i, int j) {
    if (!posicaoInvalida(i, j)) {
        if (mapa[i][j] != nullptr) {
        if (mapa[i][j]->unidade.isTroop())
            outputList.insert(mapa[i][j]->showSoldierTroop());
        else {
            outputList.insert(mapa[i][j]->showSoldier());
        }
        } else if (mapa[i][j] == nullptr) {
        outputList.insert("[ ]");
        }
    } else {
        outputList.insert("[ ]");
    }
    }

    void processaForca(int i, int j) {
    if (!posicaoInvalida(i, j)) {
        if (mapa[i][j] != nullptr) {
        ull forca;
        if (mapa[i][j]->unidade.isTroop()) {
            forca = mapa[i][j]->getTroopForce();
        } else {
            forca = mapa[i][j]->getForce();
        }

        std::string frc = std::to_string(forca);
        outputList.insert(frc);
        } else if (mapa[i][j] == nullptr) {
        outputList.insert("-1");
        }
    } else {
        outputList.insert("-1");
    }
    }

    ull forcaTotalRaca(std::string raca) {
    ull forca = 0;
    for (int i = 0; i < TAB_SIZE; ++i) {
        for (int j = 0; j < TAB_SIZE; ++j) {
        if (mapa[i][j] != nullptr && mapa[i][j]->getRace() == raca) {
            forca += mapa[i][j]->getTroopForce();
        }
        }
    }
    return forca;
    }

    ull maxAtaque(int linha, int coluna) {
    ull result;
    if (mapa[linha][coluna] != nullptr) {
        for (int i = 0; i < TAB_SIZE; ++i) {
        for (int j = 0; j < TAB_SIZE; ++j) {
            if (mapa[i][j] != nullptr &&
                mapa[i][j]->getRace() != mapa[linha][coluna]->getRace()) {
            if (movimentoValido(linha, coluna, i, j)) {
                if (mapa[i][j]->unidade.isTroop()) {
                listaOrdenada.insert(maxAtaqueUnidadeSimulacao(
                    linha, coluna, i, j,
                    mapa[linha][coluna]->unidade.takeLeader().getForce(),
                    mapa[i][j]->unidade.troopForce()));
                } else if (mapa[i][j]->unidade.isSoldier()) {
                listaOrdenada.insert(maxAtaqueUnidadeSimulacao(
                    linha, coluna, i, j,
                    mapa[linha][coluna]->unidade.takeLeader().getForce(),
                    mapa[i][j]->unidade.takeLeader().getForce()));
                }
            }
            }
        }
        }
    }
    if (!listaOrdenada.isEmpty()) {
        result = listaOrdenada.getMax();
        return result;
    }

    else if (listaOrdenada.isEmpty() || mapa[linha][coluna] == nullptr) {
        return -1;
    }

    return 0;
    }

    std::string processaComandos() {
    std::string linha;
    while (true) {
        if (std::getline(std::cin, linha)) {
        bool MOVA = linha.find("MOVA ") != std::string::npos;
        bool FORCA_RACA = linha.find("FORCA_RACA ") != std::string::npos;
        bool FORCA = linha.find("FORCA ") != std::string::npos;
        bool TERR = linha.find("TERR ") != std::string::npos;
        bool MAX_ATAQUE = linha.find("MAX_ATAQUE ") != std::string::npos;
        bool FIM = linha.find("FIM") != std::string::npos;

        if (MOVA) {
            size_t pos = 5;
            size_t next_pos = linha.find(" ", pos);
            int i1 = std::stoi(linha.substr(pos, next_pos - pos));

            pos = next_pos + 1;
            next_pos = linha.find(" ", pos);
            int j1 = std::stoi(linha.substr(pos, next_pos - pos));

            pos = next_pos + 1;
            next_pos = linha.find(" ", pos);
            int i2 = std::stoi(linha.substr(pos, next_pos - pos));

            pos = next_pos + 1;
            int j2 = std::stoi(linha.substr(pos));

            movaUnidade(i1, j1, i2, j2);
        } else if (FORCA_RACA) {
            if (linha.find("AZURI") != std::string::npos) {
            ull forca;
            std::string raca = "AZURI";
            forca = forcaTotalRaca(raca);
            std::string forcaString = std::to_string(forca);
            outputList.insert(forcaString);
            } else if (linha.find("UMASHI") != std::string::npos) {
            ull forca;
            std::string raca = "UMASHI";
            forca = forcaTotalRaca(raca);
            std::string forcaString = std::to_string(forca);
            outputList.insert(forcaString);
            } else if (linha.find("IANTECO") != std::string::npos) {
            ull forca;
            std::string raca = "IANTECO";
            forca = forcaTotalRaca(raca);
            std::string forcaString = std::to_string(forca);
            outputList.insert(forcaString);
            }
        } else if (FORCA) {
            std::string resto = linha.substr(6);
            size_t pos = resto.find(" ");
            int i = std::stoi(resto.substr(0, pos));
            int j = std::stoi(resto.substr(pos + 1));
            processaForca(i, j);
        } else if (TERR) {
            std::string resto = linha.substr(5);
            size_t pos = resto.find(" ");
            int i = std::stoi(resto.substr(0, pos));
            int j = std::stoi(resto.substr(pos + 1));

            imprimeTerritorio(i, j);
        } else if (MAX_ATAQUE) {
            std::string resto = linha.substr(11);
            size_t pos = resto.find(" ");
            int i = std::stoi(resto.substr(0, pos));
            int j = std::stoi(resto.substr(pos + 1));
            long long int forcaResultante = maxAtaque(i, j);
            std::string forcaResult = std::to_string(forcaResultante);
            outputList.insert(forcaResult);
            listaOrdenada.clear();
        } else if (FIM) {
            return "FIM";
        }
        }
    }
    }
    std::string processaSantuario() {
    std::string linha;
    while (true) {
        if (std::getline(std::cin, linha)) {
        size_t pos = 0;

        pos = linha.find(" ");
        std::string nome = linha.substr(0, pos);
        std::string resto =
            (pos == std::string::npos) ? "" : linha.substr(pos + 1);

        if (nome == "CMD") {
            return "CMD";
            break;
        }
        pos = resto.find(" ");
        std::string raca = resto.substr(0, pos);
        resto = (pos == std::string::npos) ? "" : resto.substr(pos + 1);

        pos = resto.find(" ");
        std::string forcaStr =
            (pos == std::string::npos) ? resto : resto.substr(0, pos);
        long long int forca = 0;

        try {
            forca = std::stoll(forcaStr);
        } catch (const std::invalid_argument &e) {
            continue;
        }
        Soldier *alma = new Soldier(nome, raca, forca, -1, -1);
        santuario.insert(*alma);
        } else {
        break;
        }
    }
    return "";
    }

    void processarSoldadoCapturado(const std::string &resto, Soldier *unidade) {
    if (!resto.empty()) {
        size_t pos = resto.find(" ");
        std::string infoCapturado = resto.substr(0, pos);
        std::string restoAtualizado =
            (pos == std::string::npos) ? "" : resto.substr(pos + 1);

        pos = restoAtualizado.find(" ");
        std::string nomeCapturado = restoAtualizado.substr(0, pos);
        restoAtualizado =
            (pos == std::string::npos) ? "" : restoAtualizado.substr(pos + 1);

        pos = restoAtualizado.find(" ");
        std::string racaCapturado = restoAtualizado.substr(0, pos);
        restoAtualizado =
            (pos == std::string::npos) ? "" : restoAtualizado.substr(pos + 1);

        if (!restoAtualizado.empty()) {
        ull forcaCapturado = std::stoll(restoAtualizado);

        Soldier *capturado =
            new Soldier(nomeCapturado, racaCapturado, forcaCapturado, -1, -1);
        unidade->capturados.enqueue(*capturado);

        processarSoldadoCapturado(restoAtualizado, unidade);
        }
    }
    };

    void ProcessaSoldado() {
    std::string linha;
    linha = "";
    if (std::getline(std::cin, linha)) {
        size_t pos = linha.find(" ");
        std::string nome = linha.substr(0, pos);
        std::string resto = linha.substr(pos + 1);

        pos = resto.find(" ");
        std::string raca = resto.substr(0, pos);
        resto = resto.substr(pos + 1);

        pos = resto.find(" ");
        int posicao_i = std::stoi(resto.substr(0, pos));
        resto = resto.substr(pos + 1);

        pos = resto.find(" ");
        int posicao_j = std::stoi(resto.substr(0, pos));
        resto = resto.substr(pos + 1);

        long long int forca = std::stoll(resto);

        Soldier *unidade = new Soldier(nome, raca, forca, posicao_i, posicao_j);
        processarSoldadoCapturado(resto, unidade);

        unidade->setForce();

        adicionarSoldado(posicao_i, posicao_j, unidade);

        resto = "";
        linha = "";
    }
    }

    void Run() {
    std::string comando;
    ProcessaSoldado();
    while (comando != "FIM") {
        comando = "";
        std::cin >> comando;
        std::cin.ignore();
        if (comando == "UTA") {
            ProcessaSoldado();
        }
        if (comando == "STO") {
            comando = processaSantuario();
        }
        if (comando == "CMD") {
            comando = processaComandos();
        }
    }
    outputList.show();
    }
};

int main() {
    Tabuleiro tabuleiro(TAB_SIZE, TAB_SIZE);
    tabuleiro.Run();
    return 0;
}