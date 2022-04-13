#include <iostream>
#include <vector>
using namespace std;

class IOInterface {
public:
    virtual istream &read(istream &in) = 0;
    virtual ostream &write(ostream &out) = 0;
};
class Entity : public IOInterface {
protected:
    string name;
    float xPosition, yPosition, zPosition, healPoints;
    string skinCode;

public:
    Entity();
    Entity(string name, float xPotision, float yPosition, float zPosition, string skinCode, float healPoints);
    Entity(const Entity &e);
    Entity &operator=(const Entity &e);
    friend istream &operator>>(istream &in, Entity &e);
    friend ostream &operator<<(ostream &out, const Entity &e);
    ~Entity();

    virtual istream &read(istream &in);
    virtual ostream &write(ostream &out);

    virtual void attack() = 0;
    //setters n getters
    const string &getName() const;
    void setName(const string &name);
    float getXPosition() const;
    void setXPosition(float xPosition);
    float getYPosition() const;
    void setYPosition(float yPosition);
    float getZPosition() const;
    void setZPosition(float zPosition);
    float getHealPoints() const;
    void setHealPoints(float healPoints);
    const string &getSkinCode() const;
    void setSkinCode(const string &skinCode);
};

Entity::Entity() : name("Anonim"), xPosition(0), yPosition(0), zPosition(0), skinCode("Anonim"), healPoints(0) {}
Entity::Entity(string name, float xPosition, float yPosition, float zPosition, string skinCode, float healPoints) : name(name), xPosition(xPosition), yPosition(yPosition), zPosition(zPosition), skinCode(skinCode), healPoints(healPoints) {}
Entity::Entity(const Entity &e) : name(e.name), xPosition(e.xPosition), yPosition(e.yPosition), zPosition(e.zPosition), skinCode(e.skinCode), healPoints(e.healPoints) {}
Entity::~Entity() {}
istream &Entity::read(istream &in) {
    cout << "\nNumele entitatii : ";
    in >> this->name;
    cout << "\nPunctele de viata (HP) : ";
    in >> this->healPoints;
    cout << "\nSkin code-ul : ";
    in >> this->skinCode;
    cout << "\nCoordonata x a entitatii : ";
    in >> this->xPosition;
    cout << "\nCoordonata y a entitatii : ";
    in >> this->yPosition;
    cout << "\nCoordonata z a entitatii : ";
    in >> this->zPosition;
    return in;
}
istream &operator>>(istream &in, Entity &e) {
    return e.read(in);
}
ostream &Entity::write(ostream &out) {
    cout << "\nNumele entitatii : ";
    out << this->name;
    cout << "\nPunctele de viata (HP) : ";
    out << this->healPoints;
    cout << "\nSkin code-ul : ";
    out << this->skinCode;
    cout << "\nCoordonata x a entitatii : ";
    out << this->xPosition;
    cout << "\nCoordonata y a entitatii : ";
    out << this->yPosition;
    cout << "\nCoordonata z a entitatii : ";
    out << this->zPosition;
    return out;
}
ostream &operator<<(ostream &out, Entity &e) {
    return e.write(out);
}
Entity &Entity::operator=(const Entity &e) {
    if (&e != this) {
        name = e.name;
        healPoints = e.healPoints;
        xPosition = e.xPosition;
        yPosition = e.yPosition;
        zPosition = e.zPosition;
        skinCode = e.skinCode;
    }
    return *this;
}
const string &Entity::getName() const {
    return name;
}
void Entity::setName(const string &name) {
    Entity::name = name;
}
float Entity::getXPosition() const {
    return xPosition;
}
void Entity::setXPosition(float xPosition) {
    Entity::xPosition = xPosition;
}
float Entity::getYPosition() const {
    return yPosition;
}
void Entity::setYPosition(float yPosition) {
    Entity::yPosition = yPosition;
}
float Entity::getZPosition() const {
    return zPosition;
}
void Entity::setZPosition(float zPosition) {
    Entity::zPosition = zPosition;
}
float Entity::getHealPoints() const {
    return healPoints;
}
void Entity::setHealPoints(float healPoints) {
    Entity::healPoints = healPoints;
}
const string &Entity::getSkinCode() const {
    return skinCode;
}
void Entity::setSkinCode(const string &skinCode) {
    Entity::skinCode = skinCode;
}

vector<Entity *> entitati;

//Poate ataca pe oricine
class AgressiveEntity : virtual public Entity {
protected:
    float valoareAtac;

public:
    AgressiveEntity();
    AgressiveEntity(string name, float xPotision, float yPosition, float zPosition, string skinCode, float healPoints, float valoareAtac);
    AgressiveEntity(const AgressiveEntity &ae);
    AgressiveEntity &operator=(const AgressiveEntity &ae);
    virtual istream &read(istream &in);
    virtual ostream &write(ostream &out);
    ~AgressiveEntity();
    void attack();
    //setters n getters
    float getValoareAtac() const;
    void setValoareAtac(float valoareAtac);
};
AgressiveEntity::AgressiveEntity() : valoareAtac(0) {}
AgressiveEntity::AgressiveEntity(string name, float xPotision, float yPosition, float zPosition, string skinCode, float healPoints, float valoareAtac) : Entity(name, xPotision, yPosition, zPosition, skinCode, healPoints), valoareAtac(valoareAtac) {}
AgressiveEntity::AgressiveEntity(const AgressiveEntity &ag) : Entity(ag), valoareAtac(ag.valoareAtac) {}
AgressiveEntity &AgressiveEntity::operator=(const AgressiveEntity &ag) {
    if (this != &ag) {
        Entity::operator=(ag);
        this->valoareAtac = ag.valoareAtac;
    }
    return *this;
}
istream &AgressiveEntity::read(istream &in) {
    Entity::read(in);
    cout << "\nValoare atac :";
    in >> this->valoareAtac;
    return in;
}
ostream &AgressiveEntity::write(ostream &out) {
    Entity::write(out);
    cout << "\nValoare atac :";
    out << this->valoareAtac;
    return out;
}
AgressiveEntity::~AgressiveEntity() {}
//functia ataca
class HybridEntity;
void AgressiveEntity::attack() {
    cout << "\n"
         << this->getName() << " ataca ! ";
    cout << "\nCe doriti sa atacati :";
    for (int i = 0; i < entitati.size(); i++) {
        if (entitati[i]->getName() != this->getName())
            cout << "\n"
                 << i + 1 << ". " << entitati[i]->getName();
    }
    cout << "\n";
    int y;
    cin >> y;
    cout << "\nAti ales : " << entitati[y - 1]->getName();
    entitati[y - 1]->setHealPoints(entitati[y - 1]->getHealPoints() - this->getValoareAtac());
    if (entitati[y - 1]->getHealPoints() <= 0)
        cout << "\n"
             << this->getName() << " killed " << entitati[y - 1]->getName();
    else
        cout << "\n"
             << entitati[y - 1]->getName() << " has " << entitati[y - 1]->getHealPoints() << " HP left !";
    //atac si la celelalte entitati , bool atacat pt hybrid !
}
float AgressiveEntity::getValoareAtac() const {
    return valoareAtac;
}
void AgressiveEntity::setValoareAtac(float valoareAtac) {
    AgressiveEntity::valoareAtac = valoareAtac;
}


class PeacefulEntity : virtual public Entity {
protected:
    float valoareAtac = 0;
    string reward;

public:
    PeacefulEntity();
    PeacefulEntity(string name, float xPotision, float yPosition, float zPosition, string skinCode, float healPoints, string reward);
    PeacefulEntity(const PeacefulEntity &peace);
    PeacefulEntity &operator=(const PeacefulEntity &peace);
    virtual istream &read(istream &in);
    virtual ostream &write(ostream &out);
    ~PeacefulEntity();
    void attack();
    const string &getReward() const;
    void setReward(const string &reward);
};
PeacefulEntity::PeacefulEntity() : Entity(), reward("Anonim") {}
PeacefulEntity::PeacefulEntity(string name, float xPotision, float yPosition, float zPosition, string skinCode, float healPoints, string reward) : Entity(name, xPotision, yPosition, zPosition, skinCode, healPoints), reward(reward) {}
PeacefulEntity::PeacefulEntity(const PeacefulEntity &peace) : Entity(peace), reward(peace.reward) {}
PeacefulEntity &PeacefulEntity::operator=(const PeacefulEntity &peace) {
    if (&peace != this) {
        Entity::operator=(peace);
        this->reward = reward;
    }
    return *this;
}
istream &PeacefulEntity::read(istream &in) {
    Entity::read(in);
    cout << "\nReward : ";
    in >> this->reward;
    return in;
}
ostream &PeacefulEntity::write(ostream &out) {
    Entity::write(out);
    cout << "\nReward : ";
    out << this->reward;
    return out;
}
PeacefulEntity::~PeacefulEntity() {}
const string &PeacefulEntity::getReward() const {
    return reward;
}
void PeacefulEntity::setReward(const string &reward) {
    PeacefulEntity::reward = reward;
}
void PeacefulEntity::attack() {
    cout << "\n"
         << this->name << " is too peaceful!";
}
vector<PeacefulEntity *> entitatePasnica;

//Ataca doar daca este atacat
class HybridEntity : public AgressiveEntity, public PeacefulEntity {
protected:
    float aparareArmura;
    bool attacked;

public:
    HybridEntity();
    HybridEntity(string name, float xPotision, float yPosition, float zPosition, string skinCode, float healPoints, string reward, float valoareAtac, float aparareArmura, bool attacked);
    HybridEntity(const HybridEntity &he);
    HybridEntity &operator=(const HybridEntity &he);
    ~HybridEntity();
    virtual void attack();
    void specialAttack();
    virtual istream &read(istream &in);
    virtual ostream &write(ostream &out);
    //setters n getters
    float getAparareArmura() const;
    void setAparareArmura(float aparareArmura);
    bool isAttacked() const;
    void setAttacked(bool attacked);
};
vector<HybridEntity *> hybrids;

HybridEntity::HybridEntity() : Entity(), AgressiveEntity(), PeacefulEntity(), aparareArmura(0), attacked(0) {}
HybridEntity::HybridEntity(string name, float xPotision, float yPosition, float zPosition, string skinCode, float healPoints, string reward, float valoareAtac, float aparareArmura, bool attacked) : Entity(name, xPotision, yPosition, zPosition, skinCode, healPoints), AgressiveEntity(name, xPotision, yPosition, zPosition, skinCode, healPoints, valoareAtac), PeacefulEntity(name, xPotision, yPosition, zPosition, skinCode, healPoints, reward), aparareArmura(aparareArmura), attacked(attacked) {}
HybridEntity::HybridEntity(const HybridEntity &he) : Entity(he), AgressiveEntity(he), PeacefulEntity(he), aparareArmura(he.aparareArmura), attacked(he.attacked) {}
HybridEntity &HybridEntity::operator=(const HybridEntity &he) {
    if (this != &he) {
        AgressiveEntity::operator=(he);
        this->aparareArmura = he.aparareArmura;
        this->reward = he.reward;
        this->attacked = he.attacked;
    }
    return *this;
}
HybridEntity::~HybridEntity(){};
void HybridEntity::attack() {
    if (this->healPoints > 0) {
        if (this->attacked) {
            cout << "\n"
                 << this->getName() << " ataca ! ";
            cout << "\nCe doriti sa atacati :";
            for (int i = 0; i < entitati.size(); i++) {
                if (entitati[i]->getName() != this->getName())
                    cout << "\n"
                         << i + 1 << ". " << entitati[i]->getName();
            }
            cout << "\n";
            int y;
            cin >> y;
            cout << "\nAti ales : " << entitati[y - 1]->getName();
            entitati[y - 1]->setHealPoints(entitati[y - 1]->getHealPoints() - this->getValoareAtac());
            if (entitati[y - 1]->getHealPoints() <= 0)
                cout << "\n"
                     << this->getName() << " killed " << entitati[y - 1]->getName();
            else
                cout << "\n"
                     << entitati[y - 1]->getName() << " has " << entitati[y - 1]->getHealPoints() << " HP left !";
        } else
            cout << "\nEntitatea nu a fost atacata ca sa atace la randul ei !";
    } else
        cout << "\nAceasta entitate a fost omorata !";
}
ostream &HybridEntity::write(ostream &out) {
    AgressiveEntity::write(out);
    cout << "\nReward : ";
    out << this->reward;
    cout << "\nAparare armura : ";
    out << this->aparareArmura;
    if (this->attacked)
        out << "\nEntitatea a fost atacata!";
    else
        out << "\nEntitatea nu a fost atacata!";
    return out;
}
istream &HybridEntity::read(istream &in) {
    AgressiveEntity::read(in);
    cout << "\nReward : ";
    in >> this->reward;
    cout << "\nAparare armura : ";
    in >> this->aparareArmura;
    cout << "\nEntitatea a fost atacata ( 0 - Fals / 1 - Adevarat ) : ";
    in >> this->attacked;
    return in;
}
float HybridEntity::getAparareArmura() const {
    return aparareArmura;
}
void HybridEntity::setAparareArmura(float aparareArmura) {
    HybridEntity::aparareArmura = aparareArmura;
}
bool HybridEntity::isAttacked() const {
    return attacked;
}
void HybridEntity::setAttacked(bool attacked) {
    HybridEntity::attacked = attacked;
}

class Unealta {
protected:
    string nume;
    int durabilitate;
    float valoareAtac;

public:
    Unealta();
    Unealta(const string &nume, int durabilitate, float valoareAtac);
    Unealta(const Unealta &ul);
    Unealta &operator=(const Unealta &ul);
    friend istream &operator>>(istream &in, Unealta &ul);
    friend ostream &operator<<(ostream &out, const Unealta &ul);

    const string &getNume() const;
    void setNume(const string &nume);
    int getDurabilitate() const;
    void setDurabilitate(int durabilitate);
    float getValoareAtac() const;
    void setValoareAtac(float valoareAtac);
    ~Unealta();
};
Unealta::Unealta(const string &nume, int durabilitate, float valoareAtac) : nume(nume), durabilitate(durabilitate), valoareAtac(valoareAtac) {}
Unealta::Unealta() : nume("Anonim"), durabilitate(0), valoareAtac(0) {}
Unealta::Unealta(const Unealta &ul) : nume(ul.nume), durabilitate(ul.durabilitate), valoareAtac(ul.valoareAtac) {}
Unealta &Unealta::operator=(const Unealta &ul) {
    if (this != &ul) {
        this->valoareAtac = ul.valoareAtac;
        this->durabilitate = ul.durabilitate;
        this->nume = ul.nume;
    }
}
istream &operator>>(istream &in, Unealta &ul) {
    cout << "\nNume : ";
    in >> ul.nume;
    cout << "\nDurabilitate : ";
    in >> ul.durabilitate;
    cout << "\nValoare atac : ";
    in >> ul.valoareAtac;
    return in;
}
ostream &operator<<(ostream &out, const Unealta &ul) {
    cout << "\nNume : ";
    out << ul.nume;
    cout << "\nDurabilitate : ";
    out << ul.durabilitate;
    cout << "\nValoare atac : ";
    out << ul.valoareAtac;
    return out;
}
Unealta::~Unealta() {}
const string &Unealta::getNume() const {
    return nume;
}
void Unealta::setNume(const string &nume) {
    Unealta::nume = nume;
}
int Unealta::getDurabilitate() const {
    return durabilitate;
}
void Unealta::setDurabilitate(int durabilitate) {
    Unealta::durabilitate = durabilitate;
}
float Unealta::getValoareAtac() const {
    return valoareAtac;
}
void Unealta::setValoareAtac(float valoareAtac) {
    Unealta::valoareAtac = valoareAtac;
}
vector<Unealta *> unelte;


//Poate ataca pe oricine , chiar si alt player
class Player : public Entity {
    int numberOfItems;
    Unealta *items;

public:
    Player();
    Player(string name, float xPotision, float yPosition, float zPosition, string skinCode, float healPoints, int numberOfItems, Unealta *items);
    Player(const Player &p);
    Player &operator=(const Player &p);
    virtual istream &read(istream &in);
    virtual ostream &write(ostream &out);
    void attack();
    ~Player();
    //setters n getters
    int getNumberOfItems() const;
    void setNumberOfItems(int numberOfItems);
    Unealta *getItems() const;
    void setItems(Unealta *items);
};
Player::Player() : Entity(), numberOfItems(0), items(0) {}
Player::Player(string name, float xPotision, float yPosition, float zPosition, string skinCode, float healPoints, int numberOfItems, Unealta *items) : Entity(name, xPotision, yPosition, zPosition, skinCode, healPoints), numberOfItems(numberOfItems) {
    this->items = new Unealta[numberOfItems];
    for (int i = 0; i < this->numberOfItems; i++)
        this->items[i] = items[i];
}
Player::Player(const Player &p) : Entity(p), numberOfItems(p.numberOfItems), items(p.items) {}
Player &Player::operator=(const Player &p) {
    if (this != &p) {
        if (items)
            delete items;
        Entity::operator=(p);
        numberOfItems = p.numberOfItems;
        items = p.items;
    }
    return *this;
}
istream &Player::read(istream &in) {
    Entity::read(in);
    cout << "\nNumarul de iteme din inventar : ";
    in >> this->numberOfItems;
    if (items)
        delete[] items;
    items = new Unealta[numberOfItems];
    for (int i = 0; i < numberOfItems; i++) {
        cout << "\nItemul cu numarul " << i + 1 << ": \n";
        for (int y = 0; y < unelte.size(); y++)
            cout << "\n"
                 << y + 1 << ". Pentru unealta cu numele " << unelte[y]->getNume();
        int z;
        cin >> z;
        this->items[i] = *unelte[z - 1];
    }
    return in;
}
ostream &Player::write(ostream &out) {
    Entity::write(out);
    cout << "\nNumarul de iteme din inventar : ";
    out << this->numberOfItems;
    cout << "\nItem : ";
    for (int i = 0; i < numberOfItems; i++)
        cout << items[i].getNume() << " ";
    return out;
}

void Player::attack() {
    if (healPoints) {
        cout << "\n"
             << this->getName() << " ataca ";
        cout << "\nCe doriti sa atacati :";
        for (int i = 0; i < entitati.size(); i++) {
            if (entitati[i]->getName() != this->getName())
                cout << "\n"
                     << i + 1 << ". " << entitati[i]->getName();
        }

        cout << "\n";
        int y;
        cin >> y;
        cout << "\nAti ales : " << entitati[y - 1]->getName();
        cout << "\nCu ce item doriti sa atacati : ";
        for (int i = 0; i < numberOfItems; i++)
            cout << "\n"
                 << i + 1 << ". Pentru unealta cu numele " << items[i].getNume();
        int z;
        cin >> z;
        float valoareAtac = items[z - 1].getValoareAtac();
        entitati[y - 1]->setHealPoints(entitati[y - 1]->getHealPoints() - valoareAtac);
        float hp = entitati[y - 1]->getHealPoints();

        for (int i = 0; i < hybrids.size(); i++)
            if (entitati[y - 1]->getName() == hybrids[i]->getName()) {
                hybrids[i]->setAttacked(1);
                hybrids[i]->setHealPoints(entitati[y - 1]->getHealPoints() + hybrids[i]->getAparareArmura() / 100 * valoareAtac);
                hp = hybrids[i]->getHealPoints();
            }

        if (entitati[y - 1]->getHealPoints() <= 0) {
            cout << "\n"
                 << this->getName() << " killed " << entitati[y - 1]->getName();
            for (int j = 0; j < entitatePasnica.size(); j++)
                if (entitati[y - 1]->getName() == entitatePasnica[j]->getName())
                    cout << "\n"
                         << name << " a obtinut " << entitatePasnica[j]->getReward();

        }

        else
            cout << "\n"
                 << entitati[y - 1]->getName() << " has " << hp << " HP left !";
    } else
        cout << "\nAceasta entitate a fost omorata ! ";
}
Player::~Player() {}
int Player::getNumberOfItems() const {
    return numberOfItems;
}
void Player::setNumberOfItems(int numberOfItems) {
    Player::numberOfItems = numberOfItems;
}
Unealta *Player::getItems() const {
    return items;
}
void Player::setItems(Unealta *items) {
    Player::items = items;
}

vector<Player *> players;
vector<AgressiveEntity *> agressive_entity;

int main() {
    AgressiveEntity Zombie("Zombie", 3, 2, 1, "d21", 100, 10);
    PeacefulEntity Sheep("Sheep", 53, 345, 23, "d212", 100, "wool");
    HybridEntity Spider("Spider", 21, 123, 132, "345", 100, "string", 122, 3, 0);

    agressive_entity.push_back(new AgressiveEntity(Zombie));
    Unealta sabiePiatra("sabiePiatra", 230, 15);
    Unealta sabieDiamant("sabieDiamant", 530, 25);
    Unealta sabieLemn("sabieLemn", 30, 5);
    Unealta sabieAur("sabieAur", 230, 20);
    Unealta sabieFier("sabieFier", 430, 17);
    Unealta lanceFier("lanceFier", 330, 18);
    Unealta tarnacopFier("tarnacopFier", 330, 3);
    Unealta tarnacopLemn("tarnacopLemn", 130, 1);
    Unealta tarnacopAur("tarnacopAur", 230, 4);
    Unealta tarnacopDiamant("tarnacopDiamant", 530, 5);
    Unealta tarnacopPiatra("tarnacopPiatra", 330, 4);

    unelte.push_back(new Unealta(lanceFier));
    unelte.push_back(new Unealta(tarnacopAur));
    unelte.push_back(new Unealta(tarnacopDiamant));
    unelte.push_back(new Unealta(tarnacopFier));
    unelte.push_back(new Unealta(tarnacopLemn));
    unelte.push_back(new Unealta(tarnacopPiatra));
    unelte.push_back(new Unealta(sabiePiatra));
    unelte.push_back(new Unealta(sabieDiamant));
    unelte.push_back(new Unealta(sabieLemn));
    unelte.push_back(new Unealta(sabieAur));
    Unealta iteme[] = {sabiePiatra, sabieDiamant, sabieAur};
    Player Player1("Player1", 2, 3, 1, "123fds", 100, 3, iteme);
    players.push_back(new Player(Player1));
    entitati.push_back(new AgressiveEntity(Zombie));
    entitati.push_back(new PeacefulEntity(Sheep));
    entitati.push_back(new HybridEntity(Spider));
    entitati.push_back(new Player(Player1));


    hybrids.push_back(new HybridEntity(Spider));
    entitatePasnica.push_back(new PeacefulEntity(Sheep));

    // Player1.attack();
    //  hybrids[0]->attack();
    //  Player1.attack();

    int ok = 1;
    while (ok) {
        cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
        cout << "\n1. Citire entitate  \n2. Afisare entitate\n3. Actualizare date entitate\n4. Stergere entitate\n5. Ataca entitate\n6. Iesire \n";
        int command1;
        cin >> command1;
        switch (command1) {
                //citire date
            case 1: {
                cout << "\nCe doriti sa cititi ?\nEntitate : ";
                cout << "\n1. Pasnica\n2. Agresiva\n3. Hibrida\n4. Player\n5. Unealta \n6. Intoarcere la meniul principal\n";
                int command2;
                cin >> command2;
                switch (command2) {
                    case 1: {
                        PeacefulEntity p;
                        cin >> p;
                        entitati.push_back(new PeacefulEntity(p));
                        entitatePasnica.push_back(new PeacefulEntity(p));
                        cout << "\nEntitate adaugata cu succes !";
                        break;
                    }
                    case 2: {
                        AgressiveEntity a;
                        cin >> a;
                        entitati.push_back(new AgressiveEntity(a));
                        agressive_entity.push_back(new AgressiveEntity(a));
                        cout << "\nEntitate adaugata cu succes !";
                        break;
                    }
                    case 3: {
                        HybridEntity h;
                        cin >> h;
                        entitati.push_back(new HybridEntity(h));
                        hybrids.push_back(new HybridEntity(h));
                        cout << "\nEntitate adaugata cu succes !";
                        break;
                    }
                    case 4: {
                        Player p;
                        cin >> p;
                        entitati.push_back(new Player(p));
                        players.push_back(new Player(p));
                        cout << "\nEntitate adaugata cu succes !";

                        break;
                    }
                    case 5: {
                        Unealta u;
                        cin >> u;
                        unelte.push_back(new Unealta(u));
                        cout << "\nUnealta adaugata cu succes !\n";

                        break;
                    }
                    case 6: {
                        break;
                    } break;
                    default: {
                        cout << "\nAti introdus a valoare incorecta !";
                        break;
                    }
                }

                break;
            }
                //afisare date
            case 2: {
                cout << "\nCe doriti sa afisati : ";
                cout << "\n1. Pasnica\n2. Agresiva\n3. Hibrida\n4. Player\n5. Unealta \n6. Intoarcere la meniul principal\n";
                int command2;
                cin >> command2;
                switch (command2) {
                    case 1: {
                        if (entitatePasnica.size()) {
                            cout << "\nDate despre ce entitate pasnica doriti sa afisati\n";
                            for (int i = 0; i < entitatePasnica.size(); i++)
                                cout << i + 1 << ". pentru " << entitatePasnica[i]->getName() << "\n";
                            int y;
                            cin >> y;
                            if (y > entitatePasnica.size() || y <= 0) {
                                cout << "\nInput invalid";
                                break;
                            }
                            cout << *entitatePasnica[y - 1];
                        } else
                            cout << "\nNu exista entitati pasnice create !";
                        break;
                    }
                    case 2: {
                        if (agressive_entity.size()) {
                            cout << "\nDate despre ce entitate agresiva doriti sa afisati\n";
                            for (int i = 0; i < agressive_entity.size(); i++)
                                cout << i + 1 << ". pentru " << agressive_entity[i]->getName() << "\n";
                            int y;
                            cin >> y;
                            if (y > agressive_entity.size() || y <= 0) {
                                cout << "\nInput invalid";
                                break;
                            }
                            cout << *agressive_entity[y - 1];
                        } else
                            cout << "\nNu sunt entitati agresive create !";
                        break;
                    }
                    case 3: {
                        if (hybrids.size()) {
                            cout << "\nDate despre ce entitate hibrid doriti sa afisati\n";
                            for (int i = 0; i < hybrids.size(); i++)
                                cout << i + 1 << ". pentru " << hybrids[i]->getName() << "\n";
                            int y;
                            cin >> y;
                            if (y > hybrids.size() || y <= 0) {
                                cout << "\nInput invalid";
                                break;
                            }
                            cout << *hybrids[y - 1];
                        } else
                            cout << "\nNu sunt entitati hibrid create !";
                        break;
                    }
                    case 4: {
                        if (players.size()) {
                            cout << "\nDate despre ce player doriti sa afisati\n";
                            for (int i = 0; i < players.size(); i++)
                                cout << i + 1 << ". pentru " << players[i]->getName() << "\n";
                            int y;
                            cin >> y;
                            if (y > players.size() || y <= 0) {
                                cout << "\nInput invalid";
                                break;
                            }
                            cout << *players[y - 1];
                        } else
                            cout << "\nNu sunt playeri creati !";

                        break;
                    }
                    case 5: {
                        if (unelte.size()) {
                            cout << "\nDate despre ce unealta doriti sa afisati\n";
                            for (int i = 0; i < unelte.size(); i++)
                                cout << i + 1 << ". pentru " << unelte[i]->getNume() << "\n";
                            int y;
                            cin >> y;
                            if (y > unelte.size() || y <= 0) {
                                cout << "\nInput invalid";
                                break;
                            }
                            cout << *unelte[y - 1];
                        } else
                            cout << "\nNu exista unelte create !";

                        break;
                    }
                    case 6: {
                        break;
                    }
                    default: {
                        cout << "\nAti introdus a valoare incorecta !";
                        break;
                    } break;
                }
                break;
            }
                //actualizare date
            case 3: {
                cout << "\nCe doriti sa actualizati ?\nEntitate : ";
                cout << "\n1. Pasnica\n2. Agresiva\n3. Hibrida\n4. Player\n5. Unealta \n6. Intoarcere la meniul principal\n";
                int command2;
                cin >> command2;
                switch (command2) {
                        //entitate pasnica
                    case 1: {
                        cout << "\nDate despre ce entitate pasnica doriti sa actualizati ?\n";
                        for (int i = 0; i < entitatePasnica.size(); i++)
                            cout << i + 1 << ". pentru " << entitatePasnica[i]->getName() << "\n";
                        int y;
                        cin >> y;
                        cout << "\nCe date doriti sa actualizati la " << entitatePasnica[y - 1]->getName() << " : ";
                        cout << "\n1. Numele\n2. Coordonata x\n3. Coordonata y\n4. Coordonata z\n5. Skin code-ul \n6. Heal Point-ul\n7. Reward\n8. Intoarcere la meniul de baza\n";
                        int command3;
                        cin >> command3;
                        switch (command3) {
                            case 1: {
                                cout << "\nNume nou :";
                                string name;
                                cin >> name;
                                for (int j = 0; j < entitati.size(); j++)
                                    if (entitati[j]->getName() == entitatePasnica[y - 1]->getName()) {
                                        entitati[j]->setName(name);
                                        break;
                                    }
                                entitatePasnica[y - 1]->setName(name);
                                cout << "\nNume actualizat !";
                                break;
                            }
                            case 2: {
                                cout << "\nNoua coordonata x :";
                                int x;
                                cin >> x;
                                for (int j = 0; j < entitati.size(); j++)
                                    if (entitati[j]->getName() == entitatePasnica[y - 1]->getName()) {
                                        entitati[j]->setXPosition(x);
                                        break;
                                    }
                                entitatePasnica[y - 1]->setXPosition(x);
                                cout << "\nCoordonata x actualizata !";
                                break;
                            }
                            case 3: {
                                cout << "\nNoua coordonata y :";
                                int x;
                                cin >> x;
                                for (int j = 0; j < entitati.size(); j++)
                                    if (entitati[j]->getName() == entitatePasnica[y - 1]->getName()) {
                                        entitati[j]->setYPosition(x);
                                        break;
                                    }
                                entitatePasnica[y - 1]->setYPosition(x);
                                cout << "\nCoordonata y actualizata !";
                                break;
                            }
                            case 4: {
                                cout << "\nNoua coordonata z :";
                                int x;
                                cin >> x;
                                for (int j = 0; j < entitati.size(); j++)
                                    if (entitati[j]->getName() == entitatePasnica[y - 1]->getName()) {
                                        entitati[j]->setZPosition(x);
                                        break;
                                    }
                                entitatePasnica[y - 1]->setZPosition(x);
                                cout << "\nCoordonata z actualizata !";
                                break;
                            }
                            case 5: {
                                cout << "\nSkin code nou :";
                                string name;
                                cin >> name;
                                for (int j = 0; j < entitati.size(); j++)
                                    if (entitati[j]->getName() == entitatePasnica[y - 1]->getName()) {
                                        entitati[j]->setSkinCode(name);
                                        break;
                                    }
                                entitatePasnica[y - 1]->setSkinCode(name);
                                cout << "\nSkin code actualizat !";

                                break;
                            }
                            case 6: {
                                cout << "\nHeal point nou :";
                                float healPoint;
                                cin >> healPoint;
                                for (int j = 0; j < entitati.size(); j++)
                                    if (entitati[j]->getName() == entitatePasnica[y - 1]->getName()) {
                                        entitati[j]->setHealPoints(healPoint);
                                        break;
                                    }
                                entitatePasnica[y - 1]->setHealPoints(healPoint);
                                cout << "\nHeal point actualizat !";
                                break;
                            }
                            case 7: {
                                cout << "\nReward nou :";
                                string Reward;
                                cin >> Reward;
                                for (int j = 0; j < entitati.size(); j++)
                                    if (entitati[j]->getName() == entitatePasnica[y - 1]->getName()) {
                                        if (PeacefulEntity *peacefulEntity = dynamic_cast<PeacefulEntity *>(entitati[j]))
                                            peacefulEntity->setReward(Reward);
                                    }
                                entitatePasnica[y - 1]->setReward(Reward);
                                cout << "\nReward actualizat !";
                                break;
                            }
                            case 8: {
                                break;
                            }
                            default: {
                                cout << "\nAti introdus o valoare gresita !\n";
                                break;
                            }
                        }
                        break;
                    }
                        //entitate agresiva
                    case 2: {
                        cout << "\nDate despre ce entitate agresiva doriti sa actualizati ?\n";
                        for (int i = 0; i < agressive_entity.size(); i++)
                            cout << i + 1 << ". pentru " << agressive_entity[i]->getName() << "\n";
                        int y;
                        cin >> y;
                        cout << "\nCe date doriti sa actualizati la " << agressive_entity[y - 1]->getName() << " : ";
                        cout << "\n1. Numele\n2. Coordonata x\n3. Coordonata y\n4. Coordonata z\n5. Skin code-ul \n6. Heal Point-ul\n7. Valoarea atacului\n8. Intoarcere la meniul de baza\n";
                        int command3;
                        cin >> command3;
                        switch (command3) {
                            case 1: {
                                cout << "\nNume nou :";
                                string name;
                                cin >> name;
                                for (int j = 0; j < entitati.size(); j++)
                                    if (entitati[j]->getName() == agressive_entity[y - 1]->getName()) {
                                        entitati[j]->setName(name);
                                        break;
                                    }
                                agressive_entity[y - 1]->setName(name);
                                cout << "\nNume actualizat !";
                                break;
                            }
                            case 2: {
                                cout << "\nNoua coordonata x :";
                                int x;
                                cin >> x;
                                for (int j = 0; j < entitati.size(); j++)
                                    if (entitati[j]->getName() == agressive_entity[y - 1]->getName()) {
                                        entitati[j]->setXPosition(x);
                                        break;
                                    }
                                agressive_entity[y - 1]->setXPosition(x);
                                cout << "\nCoordonata x actualizata !";
                                break;
                            }
                            case 3: {
                                cout << "\nNoua coordonata y :";
                                int x;
                                cin >> x;
                                for (int j = 0; j < entitati.size(); j++)
                                    if (entitati[j]->getName() == agressive_entity[y - 1]->getName()) {
                                        entitati[j]->setYPosition(x);
                                        break;
                                    }
                                agressive_entity[y - 1]->setYPosition(x);
                                cout << "\nCoordonata y actualizata !";
                                break;
                            }
                            case 4: {
                                cout << "\nNoua coordonata z :";
                                int x;
                                cin >> x;
                                for (int j = 0; j < entitati.size(); j++)
                                    if (entitati[j]->getName() == agressive_entity[y - 1]->getName()) {
                                        entitati[j]->setZPosition(x);
                                        break;
                                    }
                                agressive_entity[y - 1]->setZPosition(x);
                                cout << "\nCoordonata z actualizata !";
                                break;
                            }
                            case 5: {
                                cout << "\nSkin code nou :";
                                string name;
                                cin >> name;
                                for (int j = 0; j < entitati.size(); j++)
                                    if (entitati[j]->getName() == agressive_entity[y - 1]->getName()) {
                                        entitati[j]->setSkinCode(name);
                                        break;
                                    }
                                agressive_entity[y - 1]->setSkinCode(name);
                                cout << "\nSkin code actualizat !";

                                break;
                            }
                            case 6: {
                                cout << "\nHeal point nou :";
                                float healPoint;
                                cin >> healPoint;
                                for (int j = 0; j < entitati.size(); j++)
                                    if (entitati[j]->getName() == agressive_entity[y - 1]->getName()) {
                                        entitati[j]->setHealPoints(healPoint);
                                        break;
                                    }
                                agressive_entity[y - 1]->setHealPoints(healPoint);
                                cout << "\nHeal point actualizat !";
                                break;
                            }
                            case 7: {
                                cout << "\nValoare atacului nou :";
                                float valoareAtac;
                                cin >> valoareAtac;
                                for (int j = 0; j < entitati.size(); j++)
                                    if (entitati[j]->getName() == agressive_entity[y - 1]->getName()) {
                                        if (AgressiveEntity *agressiveEntity = dynamic_cast<AgressiveEntity *>(entitati[j]))
                                            agressiveEntity->setValoareAtac(valoareAtac);
                                    }
                                agressive_entity[y - 1]->setValoareAtac(valoareAtac);
                                cout << "\nReward actualizat !";
                                break;
                            }
                            default: {
                                cout << "\nAti introdus o varianta gresita!\n";
                                break;
                            } break;
                        }
                        break;
                    }
                        //entitate hybrid
                    case 3: {
                        cout << "\nDate despre ce entitate hibrida doriti sa actualizati ?\n";
                        for (int i = 0; i < hybrids.size(); i++)
                            cout << i + 1 << ". pentru " << hybrids[i]->getName() << "\n";
                        int y;
                        cin >> y;
                        cout << "\nCe date doriti sa actualizati la " << hybrids[y - 1]->getName() << " : ";
                        cout << "\n1. Numele\n2. Coordonata x\n3. Coordonata y\n4. Coordonata z\n5. Skin code-ul \n6. Heal Point-ul\n7. Valoarea atacului\n8. Reward\n9. Aparare\n10. Intoarcere la meniul de baza\n";
                        int command3;
                        cin >> command3;
                        switch (command3) {
                            case 1: {
                                cout << "\nNume nou :";
                                string name;
                                cin >> name;
                                for (int j = 0; j < entitati.size(); j++)
                                    if (entitati[j]->getName() == hybrids[y - 1]->getName()) {
                                        entitati[j]->setName(name);
                                        break;
                                    }
                                hybrids[y - 1]->setName(name);
                                cout << "\nNume actualizat !";
                                break;
                            }
                            case 2: {
                                cout << "\nNoua coordonata x :";
                                int x;
                                cin >> x;
                                for (int j = 0; j < entitati.size(); j++)
                                    if (entitati[j]->getName() == hybrids[y - 1]->getName()) {
                                        entitati[j]->setXPosition(x);
                                        break;
                                    }
                                hybrids[y - 1]->setXPosition(x);
                                cout << "\nCoordonata x actualizata !";
                                break;
                            }
                            case 3: {
                                cout << "\nNoua coordonata y :";
                                int x;
                                cin >> x;
                                for (int j = 0; j < entitati.size(); j++)
                                    if (entitati[j]->getName() == hybrids[y - 1]->getName()) {
                                        entitati[j]->setYPosition(x);
                                        break;
                                    }
                                hybrids[y - 1]->setYPosition(x);
                                cout << "\nCoordonata y actualizata !";
                                break;
                            }
                            case 4: {
                                cout << "\nNoua coordonata z :";
                                int x;
                                cin >> x;
                                for (int j = 0; j < entitati.size(); j++)
                                    if (entitati[j]->getName() == hybrids[y - 1]->getName()) {
                                        entitati[j]->setZPosition(x);
                                        break;
                                    }
                                hybrids[y - 1]->setZPosition(x);
                                cout << "\nCoordonata z actualizata !";
                                break;
                            }
                            case 5: {
                                cout << "\nSkin code nou :";
                                string name;
                                cin >> name;
                                for (int j = 0; j < entitati.size(); j++)
                                    if (entitati[j]->getName() == hybrids[y - 1]->getName()) {
                                        entitati[j]->setSkinCode(name);
                                        break;
                                    }
                                hybrids[y - 1]->setSkinCode(name);
                                cout << "\nSkin code actualizat !";

                                break;
                            }
                            case 6: {
                                cout << "\nHeal point nou :";
                                float healPoint;
                                cin >> healPoint;
                                for (int j = 0; j < entitati.size(); j++)
                                    if (entitati[j]->getName() == hybrids[y - 1]->getName()) {
                                        entitati[j]->setHealPoints(healPoint);
                                        break;
                                    }
                                hybrids[y - 1]->setHealPoints(healPoint);
                                cout << "\nHeal point actualizat !";
                                break;
                            }
                            case 7: {
                                cout << "\nValoare atacului nou :";
                                float valoareAtac;
                                cin >> valoareAtac;
                                for (int j = 0; j < entitati.size(); j++)
                                    if (entitati[j]->getName() == hybrids[y - 1]->getName()) {
                                        if (HybridEntity *hybridEntity = dynamic_cast<HybridEntity *>(entitati[j]))
                                            hybridEntity->setValoareAtac(valoareAtac);
                                    }
                                hybrids[y - 1]->setValoareAtac(valoareAtac);
                                cout << "\nValoare atacului actualizata !";
                                break;
                            }
                            case 8: {
                                cout << "\nReward nou :";
                                string Reward;
                                cin >> Reward;
                                for (int j = 0; j < entitati.size(); j++)
                                    if (entitati[j]->getName() == hybrids[y - 1]->getName()) {
                                        if (HybridEntity *hybridEntity = dynamic_cast<HybridEntity *>(entitati[j]))
                                            hybridEntity->setReward(Reward);
                                    }
                                hybrids[y - 1]->setReward(Reward);
                                cout << "\nReward actualizat !";
                                break;
                            }
                            case 9: {
                                cout << "\nArmura noua :";
                                float armura;
                                cin >> armura;
                                for (int j = 0; j < entitati.size(); j++)
                                    if (entitati[j]->getName() == hybrids[y - 1]->getName()) {
                                        if (HybridEntity *hybridEntity = dynamic_cast<HybridEntity *>(entitati[j]))
                                            hybridEntity->setAparareArmura(armura);
                                    }
                                hybrids[y - 1]->setAparareArmura(armura);
                                cout << "\nArmura actualizata !";
                                break;
                            }
                            case 10: {
                                break;
                            }
                            default: {
                                cout << "\nAti introdus o varianta gresita !";
                                break;
                            } break;
                        }
                        break;
                    }
                        //player
                    case 4: {
                        cout << "\nDate despre ce player doriti sa actualizati ?\n";
                        for (int i = 0; i < players.size(); i++)
                            cout << i + 1 << ". pentru " << players[i]->getName() << "\n";
                        int y;
                        cin >> y;
                        cout << "\nCe date doriti sa actualizati la " << players[y - 1]->getName() << " : ";
                        cout << "\n1. Numele\n2. Coordonata x\n3. Coordonata y\n4. Coordonata z\n5. Skin code-ul \n6. Heal Point-ul\n7. Numarul de iteme\n8. Iteme\n9. Inapoi la meniul principal\n";
                        int command3;
                        cin >> command3;
                        switch (command3) {
                            case 1: {
                                cout << "\nNume nou :";
                                string name;
                                cin >> name;
                                for (int j = 0; j < entitati.size(); j++)
                                    if (entitati[j]->getName() == players[y - 1]->getName()) {
                                        entitati[j]->setName(name);
                                        break;
                                    }
                                players[y - 1]->setName(name);
                                cout << "\nNume actualizat !";
                                break;
                            }
                            case 2: {
                                cout << "\nNoua coordonata x :";
                                int x;
                                cin >> x;
                                for (int j = 0; j < entitati.size(); j++)
                                    if (entitati[j]->getName() == players[y - 1]->getName()) {
                                        entitati[j]->setXPosition(x);
                                        break;
                                    }
                                players[y - 1]->setXPosition(x);
                                cout << "\nCoordonata x actualizata !";
                                break;
                            }
                            case 3: {
                                cout << "\nNoua coordonata y :";
                                int x;
                                cin >> x;
                                for (int j = 0; j < entitati.size(); j++)
                                    if (entitati[j]->getName() == players[y - 1]->getName()) {
                                        entitati[j]->setYPosition(x);
                                        break;
                                    }
                                players[y - 1]->setYPosition(x);
                                cout << "\nCoordonata y actualizata !";
                                break;
                            }
                            case 4: {
                                cout << "\nNoua coordonata z :";
                                int x;
                                cin >> x;
                                for (int j = 0; j < entitati.size(); j++)
                                    if (entitati[j]->getName() == players[y - 1]->getName()) {
                                        entitati[j]->setZPosition(x);
                                        break;
                                    }
                                players[y - 1]->setZPosition(x);
                                cout << "\nCoordonata z actualizata !";
                                break;
                            }
                            case 5: {
                                cout << "\nSkin code nou :";
                                string name;
                                cin >> name;
                                for (int j = 0; j < entitati.size(); j++)
                                    if (entitati[j]->getName() == players[y - 1]->getName()) {
                                        entitati[j]->setSkinCode(name);
                                        break;
                                    }
                                players[y - 1]->setSkinCode(name);
                                cout << "\nSkin code actualizat !";

                                break;
                            }
                            case 6: {
                                cout << "\nHeal point nou :";
                                float healPoint;
                                cin >> healPoint;
                                for (int j = 0; j < entitati.size(); j++)
                                    if (entitati[j]->getName() == players[y - 1]->getName()) {
                                        entitati[j]->setHealPoints(healPoint);
                                        break;
                                    }
                                players[y - 1]->setHealPoints(healPoint);
                                cout << "\nHeal point actualizat !";
                                break;
                            }
                            case 7: {
                                cout << "\nNumar de iteme noi :";
                                int number;
                                cin >> number;
                                for (int j = 0; j < entitati.size(); j++)
                                    if (entitati[j]->getName() == players[y - 1]->getName()) {
                                        if (Player *player1 = dynamic_cast<Player *>(entitati[j]))
                                            player1->setNumberOfItems(number);
                                    }
                                players[y - 1]->setNumberOfItems(number);
                                cout << "\nNumar de iteme actualizata !";
                                break;
                            }
                            case 8: {
                                //actualizare iteme
                                Unealta iteme2[100];
                                int r = 0;
                                for (int i = 0; i < players[y - 1]->getNumberOfItems(); i++) {
                                    cout << "\nItemul nou cu numarul " << i + 1 << " este ";
                                    for (int k = 0; k < unelte.size(); k++)
                                        cout << "\n"
                                             << k + 1 << ". " << unelte[k]->getNume();
                                    int h;
                                    cin >> h;
                                    Unealta ul(*unelte[h - 1]);
                                    iteme2[r] = ul;
                                    r++;
                                }//PROBLEMA AICI
                                players[y - 1]->setItems(iteme2);
                                break;
                            }
                            case 9: {
                                break;
                            }
                            default: {
                                cout << "\nVarianta introdusa gresita !";
                            }
                        }

                        break;
                    }
                        //Unealta
                    case 5: {
                        cout << "\nDate despre ce unealta doriti sa actualizati ?\n";
                        for (int i = 0; i < unelte.size(); i++)
                            cout << i + 1 << ". pentru " << unelte[i]->getNume() << "\n";
                        int y;
                        cin >> y;
                        cout << "\nCe date doriti sa actualizati la " << unelte[y - 1]->getNume() << " : ";
                        cout << "\n1. Numele\n2. Durabilitate x\n3. Valoare atac \n4. Inapoi la meniul principal\n";
                        int command3;
                        cin >> command3;
                        switch (command3) {
                            case 1: {
                                string nume;
                                cout << "\nNume nou  ";
                                cin >> nume;
                                unelte[y - 1]->setNume(nume);
                                cout << "\nNume actualizat cu succes !";
                                break;
                            }
                            case 2: {
                                int durabilitate;
                                cout << "\nDurabilitate noua  ";
                                cin >> durabilitate;
                                unelte[y - 1]->setDurabilitate(durabilitate);
                                cout << "\nDurabilitate actualizata cu succes !";
                                break;
                            }
                            case 3: {
                                float valoareAtac;
                                cout << "\n Valoare atac noua ";
                                cin >> valoareAtac;
                                unelte[y - 1]->setValoareAtac(valoareAtac);
                                break;
                            }
                            case 4: {
                                break;
                            }
                            default: {
                                cout << "\nAti introdus o variant agresita !";
                                break;
                            }
                        }
                        break;
                    }
                    case 6: {
                        break;
                    }
                    default: {
                        cout << "\nAti introdus a valoare incorecta !";
                        break;
                    }
                }

                break;
            }
                //stergere date
            case 4: {
                cout << "\nCe doriti sa stergeti :\n1. Entitate pasnica\n2. Entitate agresiva\n3. Entitate hibrida\n4. Unealta\n5. Player\n6. Inapoi la meniul principal\n";
                int command2;
                cin >> command2;
                switch (command2) {
                        //entitate pasnica
                    case 1: {
                        if (entitatePasnica.size()) {
                            cout << "\nCe entitate pasnica doriti sa stergeti ";
                            for (int i = 0; i < entitatePasnica.size(); i++)
                                cout << "\n"
                                     << i + 1 << " pentru " << entitatePasnica[i]->getName();
                            int y;
                            cin >> y;
                            for (int i = 0; i < entitati.size(); i++)
                                if (entitati[i] == entitatePasnica[y - 1])
                                    entitati.erase(entitati.begin() + i);
                            entitatePasnica.erase(entitatePasnica.begin() + y - 1);


                        } else
                            cout << "\nNu exista entitati pasnice !";
                        break;
                    }
                        //entitate agresiva
                    case 2: {
                        if (agressive_entity.size()) {
                            cout << "\nCe entitate agresiva doriti sa stergeti ";
                            for (int i = 0; i < agressive_entity.size(); i++)
                                cout << "\n"
                                     << i + 1 << " pentru " << agressive_entity[i]->getName();
                            int y;
                            cin >> y;
                            for (int i = 0; i < entitati.size(); i++)
                                if (entitati[i] == agressive_entity[y - 1])
                                    entitati.erase(entitati.begin() + i);
                            agressive_entity.erase(agressive_entity.begin() + y - 1);


                        } else
                            cout << "\nNu exista entitati agresive !";
                        break;
                    }
                        //hibrid

                    case 3: {
                        if (hybrids.size()) {
                            cout << "\nCe entitate hibrida doriti sa stergeti ";
                            for (int i = 0; i < hybrids.size(); i++)
                                cout << "\n"
                                     << i + 1 << " pentru " << hybrids[i]->getName();
                            int y;
                            cin >> y;
                            for (int i = 0; i < entitati.size(); i++)
                                if (entitati[i] == hybrids[y - 1])
                                    entitati.erase(entitati.begin() + i);
                            hybrids.erase(hybrids.begin() + y - 1);


                        } else
                            cout << "\nNu exista entitati hibride !";

                        break;
                    }
                        //unealta
                    case 4: {
                        if (unelte.size()) {
                            cout << "\nCe unealta doriti sa stergeti ";
                            for (int i = 0; i < unelte.size(); i++)
                                cout << "\n"
                                     << i + 1 << " pentru " << unelte[i]->getNume();
                            int y;
                            cin >> y;
                            unelte.erase(unelte.begin() + y - 1);


                        } else
                            cout << "\nNu exista entitati hibride !";
                        break;
                    }

                    case 5: {
                        if (players.size()) {
                            cout << "\nCe player doriti sa stergeti ";
                            for (int i = 0; i < players.size(); i++)
                                cout << "\n"
                                     << i + 1 << " pentru " << players[i]->getName();
                            int y;
                            cin >> y;
                            players.erase(players.begin() + y - 1);


                        } else
                            cout << "\nNu exista playeri !";
                        break;
                    }
                    case 6: {
                        break;
                    }
                    default: {
                        cout << "\nAti introdus o varianta gresista !";
                        break;
                    }
                }
                break;
            }
                //ataca
            case 5: {
                cout << "\nCu ce entitate doriti sa atacati ?\n1. Agressive entity\n2. Hybrid entity\n3. Player\n4. Inapoi la meniul principal\n";
                int command2;
                cin >> command2;
                switch (command2) {
                        //ae
                    case 1: {
                        if (agressive_entity.size()) {
                            cout << "\nCu ce entitate agresiva doriti sa atacati  ";
                            for (int i = 0; i < agressive_entity.size(); i++)
                                cout << "\n"
                                     << i + 1 << ". pentru" << agressive_entity[i]->getName() << "\n";
                            int k;
                            cin >> k;
                            agressive_entity[k - 1]->attack();
                        } else
                            cout << "\nNu exista entita agresive !";
                        break;
                    }
                        //hy
                    case 2: {
                        if (hybrids.size()) {
                            cout << "\nCu ce entitate hibrida doriti sa atacati  ";
                            for (int i = 0; i < hybrids.size(); i++)
                                cout << "\n"
                                     << i + 1 << ". pentru" << hybrids[i]->getName() << "\n";
                            int k;
                            cin >> k;
                            hybrids[k - 1]->attack();
                        } else
                            cout << "\nNu exista entitati hybride!";

                        break;
                    }
                        //pl
                    case 3: {
                        if (players.size()) {
                            cout << "\nCu ce entitate hibrida doriti sa atacati  ";
                            for (int i = 0; i < players.size(); i++)
                                cout << "\n"
                                     << i + 1 << ". pentru" << players[i]->getName() << "\n";
                            int k;
                            cin >> k;
                            players[k - 1]->attack();
                        } else
                            cout << "\nNu exista players!";
                        break;
                    }
                    case 4: {
                        break;
                    }
                    default: {
                        cout << "\nAti introdus o varianta gresita !";
                        break;
                    }
                }
                break;
            }
            case 6: {
                ok = 0;
                break;
            }
            default: {
                break;
            } break;
        }
    }
    return 0;
}
