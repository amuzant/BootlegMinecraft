#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <vector>
#include <list>

using namespace std;

class MobException : public exception
{
public:
    const char* what() const throw() {return "Eroare: Mob custom/invalid cu hp invalid/nespecificat!\n";}
};

class MobInvalidHP : public exception
{
public:
    const char* what() const throw() {return "Eroare: Mob custom/invalid cu hp invalid (negativ)!\n";}
};

class MobUndeclaredHP : public exception
{
public:
    const char* what() const throw() {return "Eroare: Mob custom/invalid cu hp neinitializat!\n";}
};

class BadItem : public exception
{
public:
    const char* what() const throw() {return "Eroare: Item id invalid!\n";}
};

class Items
{
    int id;
    string type;
    string nume;
    int breakable_by_id; //block
    float damage; //weapon
public:
    Items()
    {
        id=0;
        type="";
        damage=0;
        breakable_by_id=0;
    }
    Items(string t,string n,float d=0,int b=0,int i=0)
    {
        id=i;
        type = t;
        nume = n;
        damage=d;
        breakable_by_id=b;
    }
    string getName();
    float getDamage();
    string getType();
    int getId();
    friend ostream& operator<<(ostream& out, const Items& item);
};

int Items::getId() {
    return id;
}

float Items::getDamage() {
    return damage;
}

string Items::getName()
{
    return nume;
}

string Items::getType()
{
    return type;
}

class ItemDB
{
protected:
    vector<Items> iteme;
    int itemindex=0;
    static ItemDB* instancePointer;
    ItemDB(){}
public:
    ItemDB(const ItemDB& obj) = delete;

    static ItemDB* getInstance()
    {
        if (instancePointer == NULL)
        {
            instancePointer = new ItemDB();
            return instancePointer;
        }
        else
        {
            return instancePointer;
        }
    }
    int adauga(const char* t,const char* n,float d=0,int b=0,int i=0);
    void afisare();
    int getSize();
    vector<Items> getItems();
    Items cauta(int itemId);
    bool areAllType(string t);
};

ItemDB* ItemDB::instancePointer=NULL;

bool ItemDB::areAllType(string t) {
    return all_of(iteme.cbegin(),iteme.cend(),[t](Items i){return t==i.getType();});
}

vector<Items> ItemDB::getItems()
{
    return iteme;
}

int ItemDB::getSize() {
    return iteme.size();
}
Items ItemDB::cauta(int itemId)
{
        if (itemId==0) return Items();
        if (itemId-1 <= iteme.size()) return iteme.at(itemId-1);
        else {cout<<itemId-1<<" "<<iteme.size(); (BadItem());}
}

int ItemDB::adauga(const char* t,const char* n,float d,int b,int i)
    {
        itemindex++;
        Items temp_item(t,n,d,b,itemindex);
        //cout<<"added"<<temp_item;
        bool itemExists=false;
        int cnt=0;
        if(iteme.size()!=0)
            for(auto i2=iteme.begin();i2<iteme.end();i2++)
            {cnt++;
                if(i2->getName()==temp_item.getName()) itemExists=true; break;}
        if(itemExists!=true) {cout<<"Am adaugat "<<temp_item.getName()<<" cu id-ul "<<itemindex<<endl;iteme.push_back(temp_item);return itemindex;}
        else {cout<<"Deja exista itemul "<<temp_item.getName()<<"!\n"; itemindex--;return cnt;}

    }


void ItemDB::afisare()
    {
        cout<<"Here's a list of the items available:\n";
        for(int i=0;i<iteme.size();i++)
            cout<<iteme[i];
        cout<<endl;
    }

ostream& operator<<(ostream& out, const Items& item)
{
    out<<"Item info:"<<endl;
    out<<"Id: "<<item.id<<endl;
    out<<"Name: "<<item.nume<<endl;
    out<<"Item type: "<<item.type<<endl;
    if(item.type=="Block")
    {
        out<<"Breakable by ";
        if(item.breakable_by_id!=0) out<<"item id: "<<item.breakable_by_id<<endl;
        else out<<"anything!\n";
    }
    out<<"------------"<<endl;
    return out;
}

class Inventory
{
    ItemDB* db;
    list<Items> iteme;
    static const int inv_size=27;
public:
    Inventory()
    {
        db=ItemDB::getInstance();
    }
    Inventory(Inventory &t)
    {
        iteme=t.iteme;
        db=t.db;
    }
    void show()
    {
        cout<<iteme.size()<<" total slots:"<<endl;
        for(auto i : iteme)
            cout<<"! "<<i.getName()<<endl;
        cout<<endl;
    }
    friend ostream& operator << (ostream &out, const Inventory &c);
    const void reset();
    const bool addItem(int itemId);
    void checkWeapon(int itemId);
};

const void Inventory::reset()
{
    iteme.clear();
}

const bool Inventory::addItem(int itemId)
{
    Items tempitem=db->cauta(itemId);
    if(iteme.size()<inv_size) {iteme.push_back(tempitem);return 1;}
    else cout<<"The item "<<tempitem.getName()<<" couldn't be added to your inventory. (Inventory Full)\n";
    return 0;
}

ostream& operator << (ostream &out, const Inventory &c)
{
    out<<c.iteme.size()<<" total slots:"<<endl;
    for(auto i : c.iteme)
        cout<<i.getName()<<" ";
    out<<endl;
    return out;
}

class Entity
{
public:
    virtual const float getHP()=0;
    virtual const float getDamage()=0;
    virtual const void removeHP(float hitDamage)=0;
    virtual void afisareItems()=0;
    ~Entity(){}
};

class ItemDBAccess
{
protected:
    ItemDB* db;
public:
    virtual void afisareItems()=0;
    ItemDBAccess(){
        db=ItemDB::getInstance();
    }
};
class Mob;

class Player : public Entity,protected ItemDBAccess
{
private:
    float hp;
    float damage;
    Inventory inventory;
    string nume;
    int weapon_id;
    static int nr_playeri_alive;
    static int lootcount;
public:
    Player(string n="Steve"){
        nume=n;
        hp=20;
        damage=1;
        weapon_id=0;
        nr_playeri_alive++;
    }
    Player(const Player& other){
        this->nume = other.nume;
        this->hp = other.hp;
        this->damage = other.damage;
        this->inventory = other.inventory;
        this->db=other.db;
        this->weapon_id=other.weapon_id;
    }
    const float getHP();
    const float getDamage();
    const void removeHP(float hitDamage);
    friend ostream& operator<<(ostream& out, const Player& player);
    const void addToInventory(int itemId);
    const void attack(Mob &m);
    const void showInventory();
    const void loot();
    const void setHP(int h);
    const void setDamage(int dmg);
    void checkWeapon(int itemId);
    void afisareItems();
    static int nrPlayeriAlive();
    static void lootCount();
protected:
    const bool alive();
};

int Player::nr_playeri_alive=0;

int Player::lootcount=0;

void Player::lootCount()
{
    cout<<"The loot command has been used a total of "<<lootcount<<" times!\n";
}

int Player::nrPlayeriAlive() {
    cout<<"There are currently: "<<nr_playeri_alive<<" players alive!\n";
}

void Player::afisareItems()
{
    cout<<"Here's a list of the items available to the player:\n";
    vector<Items> tempdb=db->getItems();
    for(int i=0;i<tempdb.size();i++)
        cout<<tempdb[i];
    cout<<endl;
}

const void Player::showInventory()
{
    inventory.show();
}

const void Player::setHP(int h)
{
    hp=h;
}

const void Player::setDamage(int dmg)
{
    damage=dmg;
}

const bool Player::alive()
{
    if(this->hp>0) return true;
    return false;
}

const float Player::getHP()
{
    return hp;
}

const float Player::getDamage()
{
    return damage;
}

const void Player::removeHP(float hitDamage)
{
    hp-=hitDamage;
    cout<<nume<<" took "<<hitDamage<<" Damage.\n";
    if(alive())
    {
        cout<<nume<<" has died.\n";
        //reset the inventory
        inventory.reset();
        //reset the damage
        damage=1;
        nr_playeri_alive--;
        cout<<"Do you want to respawn? (y\\n): ";
        char respawn;
        cin>>respawn;
        if(respawn=='y'||respawn=='Y')
        {
            //reset the hp
            hp=20;
            cout<<nume<<" has respawned!\n";
            nr_playeri_alive++;
        }
    }
}
ostream& operator<<(ostream& out, const Player& player)
{
    out<<player.nume<<"'s stats:"<<endl;
    out<<"HP: "<<player.hp<<endl;
    out<<"Hit damage: "<<player.damage<<endl;
    return out;
}

const void Player::addToInventory(int itemId)
{
    cout<<"Adding "<<db->cauta(itemId).getName()<<" to your inventory."<<endl;
    if(inventory.addItem(itemId)) checkWeapon(itemId);
}

const void Player::loot()
{   int size=db->getSize();
    int tempitemid=(rand()%size)+1;
    cout<<"New loot acquired: "<<db->cauta(tempitemid).getName()<<endl;
    addToInventory(tempitemid);
    lootcount++;
}

void Player::checkWeapon(int itemId) {
    Items temp_weapon=db->cauta(itemId);
    if(db->cauta(itemId).getDamage()>=db->cauta(weapon_id).getDamage())
    {
        weapon_id=itemId;
        if(temp_weapon.getType()=="Weapon")
        cout<<temp_weapon.getName()<<" is now "<<nume<<"'s (Player) best weapon, dealing "<<temp_weapon.getDamage()<<" damage!\n";
        else {hp+=temp_weapon.getDamage(); cout<<"Healed "<<nume<<" for "<<temp_weapon.getDamage()<<" HP!\n";}
    }
}

class Mob : public Entity,protected ItemDBAccess
{
protected:
    string nume;
    float hp;
    float damage;
    int drop_item;
    bool hostile=0;
    int weapon_id=0;
public:
    Mob()
    {
        cout<<"You haven't specified the mob type, so we made a cow instead\n";
        hp=20,hostile=0,drop_item=db->adauga("Food","Carne de vaca");
        nume = "Cow";
    }
    Mob(string name,int h=-1,bool ho=0)
    {
        nume=name;
        try {
            if (nume == "Cow")
                hp = 10, drop_item=db->adauga("Food","Carne de vaca",3);
            else if (nume == "Pig")
                hp = 10, drop_item=db->adauga("Food","Carne de porc",2);
            else if (nume == "Villager")
                hp = 10;
            else if (nume == "Wolf")
                hp = 8;
            else if (nume == "Zombie")
                hp = 20, drop_item=db->adauga("Food","Rotten flesh",1), damage = 4.5, hostile=1;
            else if (nume == "Creeper")
                hp = 20, drop_item=db->adauga("Utility","Gunpowder"), hostile=1;
            else if (nume == "Skeleton")
                hp = 20, drop_item=db->adauga("Utility","Os"), damage = 5, hostile=1;
            else if (h >= 0)
                hp = h, hostile=ho,drop_item=0;
            else throw(MobException());
        }
        catch(MobException& e)
        {
            try {
                if (h == -1) throw (MobUndeclaredHP());
                else throw (MobInvalidHP());
            }
            catch(exception& e)
            {
                cout<<e.what();
            }
        }
    }
    void showStats();
    const bool alive();
    const void attack(Player &p);
    const void removeHP(float hitDamage);
    const string getName();
    const float getDamage();
    const int getItem();
    const float getHP();
    void afisareItems();
    void setDamage(float dmg);
    friend ostream& operator<<(ostream& out, const Mob& mob);
    Mob& operator=(const Mob& other) {
        if(this != &other) {
            this->nume=other.nume;
            this->hp=other.hp;
            this->damage=other.damage;
            this->drop_item=other.drop_item;
            this->hostile=other.hostile;
        }
        return *this;
    }
    void giveWeapon(int itemId);
};
void Mob::giveWeapon(int itemId) {
    if(hostile==1) {
        Items temp_weapon = db->cauta(itemId);
        Items old_weapon = db->cauta(weapon_id);
        if (temp_weapon.getDamage() >= old_weapon.getDamage()) {
            weapon_id = itemId;
            damage -= old_weapon.getDamage();
            damage += temp_weapon.getDamage();
            cout << temp_weapon.getName() << " has been added to " << nume << "'s (Mob) Inventory!\n";
            cout << "Weapon damage: " << old_weapon.getDamage() << "->" << temp_weapon.getDamage() << "\n";
            setDamage(damage);
        }
    }
}

void Mob::setDamage(float dmg) {
    damage=dmg;
}
void Mob::showStats() {
    {
        cout<<"Mob stats:"<<endl;
        cout<<"HP: "<<hp<<endl;
        cout<<"Drop item: "<<db->cauta(drop_item).getName()<<'\n';
        if(hostile==1) cout<<"Hit damage: "<<damage<<endl;

        //tipul mobului
        cout<<"Type: ";
        if(hostile==1) cout<<"Hostile (";
        else cout<<"Peaceful (";
        cout<<nume<<")"<<endl;
    }
}

ostream& operator<<(ostream& out, const Mob& mob)
{

    out<<"Mob stats:"<<endl;
    out<<"HP: "<<mob.hp<<endl;
    out<<"Drop item: "<<mob.db->cauta(mob.drop_item).getName()<<'\n';
    if(mob.hostile==1) out<<"Hit damage: "<<mob.damage<<endl;

    //tipul mobului
    out<<"Type: ";
    if(mob.hostile==1) out<<"Hostile (";
    else out<<"Peaceful (";
    out<<mob.nume<<")"<<endl;

    return out;
}

void Mob::afisareItems() {
        cout<<"Here's a list of the items available to the Mob (weapons only):\n";
        vector<Items> tempdb=db->getItems();
        for(int i=0;i<tempdb.size();i++)
            if(tempdb[i].getType()=="Weapon") cout<<tempdb[i];
        cout<<endl;
}

const float Mob::getHP()
{
    return hp;
}
const float Mob::getDamage()
{
    return damage;
}

const int Mob::getItem()
{
    return drop_item;
}

const string Mob::getName()
{
    return nume;
}
const bool Mob::alive()
{
    if(this->hp>0) return true;
    return false;
}
const void Mob::attack(Player &p)
{
        if(this->alive()==true)
        {
            p.removeHP(this->damage);
        }
    }
const void Mob::removeHP(float hitDamage)
{
    hp-=hitDamage;
    cout<<"Mob took "<<hitDamage<<" Damage.\n";
    if(hp<=0)
    {
        cout<<this->getName()<<" has died.\n";

    }
}


const void Player::attack(Mob &m)
{
        if(this->alive()==true)
        {
            m.removeHP(damage);
            if(m.alive()==false) {addToInventory(m.getItem());}
        }
    }

class HostileMob:public Mob
{
    int weapon_id;
    int damage;
public:
    HostileMob(string nume="",float hp=-1,float dmg=2,int weapon=0):Mob(nume,hp, 1)
    {
        weapon_id=weapon;
        damage=dmg;
        setDamage(damage);
    }
    void giveWeapon(int itemId);
    friend ostream& operator<<(ostream& out, const HostileMob& mob);
    void showStats();
};

void HostileMob::showStats() {
    cout<<"Mob stats:"<<endl;
    cout<<"HP: "<<hp<<endl;
    if(drop_item!=0 )cout<<"Drop item: "<<db->cauta(drop_item).getName()<<endl;
    cout<<"Hit damage: "<<damage<<endl;
    if(weapon_id!=0) cout<<"(+"<<db->cauta(weapon_id).getDamage()<<" from "<<db->cauta(weapon_id).getName()<<")\n";

    //tipul mobului
    cout<<"Type: ";
    cout<<"Hostile (";
    cout<<nume<<")"<<endl;
}

void HostileMob::giveWeapon(int itemId) {
    Items temp_weapon=db->cauta(itemId);
    Items old_weapon=db->cauta(weapon_id);
    if(temp_weapon.getDamage()>=old_weapon.getDamage())
    {
        weapon_id=itemId;
        damage-=old_weapon.getDamage();
        damage+=temp_weapon.getDamage();
        cout<<temp_weapon.getName()<<" has been added to "<<nume<<"'s (Mob) Inventory!\n";
        cout<<"Weapon damage: "<<old_weapon.getDamage()<<"->"<<temp_weapon.getDamage()<<"\n";
        setDamage(damage);
    }
}

ostream& operator<<(ostream& out, const HostileMob& mob)
{

    out<<"Mob stats:"<<endl;
    out<<"HP: "<<mob.hp<<endl;
    if(mob.drop_item!=0 )out<<"Drop item: "<<mob.db->cauta(mob.drop_item).getName()<<endl;
    out<<"Hit damage: "<<mob.damage<<endl;
    if(mob.weapon_id!=0) out<<"(+"<<mob.db->cauta(mob.weapon_id).getDamage()<<" from "<<mob.db->cauta(mob.weapon_id).getName()<<")\n";

    //tipul mobului
    out<<"Type: ";
    out<<"Hostile (";
    out<<mob.nume<<")"<<endl;

    return out;
}

class PeacefulMob:public Mob
{
public:
    PeacefulMob(string nume="",float hp=-1):Mob(nume,hp,0)
    {
    }
    friend ostream& operator<<(ostream& out, const PeacefulMob& mob);
    void showStats();
};

void PeacefulMob::showStats() {
    cout<<"Mob stats:"<<endl;
    cout<<"HP: "<<hp<<endl;
    if(drop_item!=0 )cout<<"Drop item: "<<db->cauta(drop_item).getName()<<endl;

    //tipul mobului
    cout<<"Type: ";
    cout<<"Peaceful (";
    cout<<nume<<")"<<endl;
}

ostream& operator<<(ostream& out, const PeacefulMob& mob)
{

    out<<"Mob stats:"<<endl;
    out<<"HP: "<<mob.hp<<endl;
    out<<"Drop item: "<<mob.db->cauta(mob.drop_item).getName()<<endl;

    //tipul mobului
    out<<"Type: ";
    out<<"Peaceful (";
    out<<mob.nume<<")"<<endl;

    return out;
}

int main()
{
    cout<<"Welcome to bootleg Minecraft!\n";

    ItemDB* lista_iteme=ItemDB::getInstance();
    lista_iteme->adauga("Block","Wood",1,0);
    lista_iteme->adauga("Weapon","Sabie generica",3,0);
    lista_iteme->adauga("Weapon","Sabie buna",5,0);
    lista_iteme->adauga("Weapon","Sabie legendara",7,0);
    lista_iteme->afisare();

    Mob abc("Zombie");
    cout<<abc;
HostileMob ab("Zombie2",7,0);
cout<<ab.getHP();
    ab.giveWeapon(4);
    ab.afisareItems();

    Player* steve= new Player("and");
    steve->loot();
    steve->loot();
    steve->loot();
    steve->loot();
    steve->loot();
    steve->loot();
    steve->loot();
    steve->loot();
    steve->loot();
    steve->loot();
    steve->loot();
    steve->showInventory();
    steve->lootCount();

    Entity* steve2= new Player("rei");
    Entity* mob2=new Mob("Zombie");
    steve->nrPlayeriAlive();
steve2->afisareItems();
    mob2->afisareItems();

    Mob* p1=new PeacefulMob("Cow");
    Mob* h1=new HostileMob("Skeleton");
    p1->showStats();
    h1->showStats();
    cout<<abc;

    HostileMob h2=HostileMob("Creeper");
    Mob* hh2=&h2;
    PeacefulMob p2=PeacefulMob("Cow");
    PeacefulMob* pp2=&p2;

    hh2->showStats();
    pp2->showStats();

    Entity* et = new Player();

    Player* player = dynamic_cast<Player*>(et);
    if (player)
        player->loot();
    else
        cout<<"Entitatea nu este un player!"<<std::endl;


    Mob* mob = dynamic_cast<Mob*>(et);
    if (mob)
        mob->giveWeapon(2);
     else
        cout<<"Entitatea nu este un mob!"<<endl;


//    Player steve;
//    cout<<steve.getHP()<<endl;
//    cout<<steve;
//    steve.removeHP(3);
//    steve.setDamage(rand()%20);
//    cout<<steve.getDamage();
//    Mob zombie("Zombie");
//    zombie.attack(steve);
//    cout<<steve;
//    steve.attack(zombie);
//    cout<<zombie.getHP();
//    steve.setDamage(zombie.getHP()+1);
//    steve.attack(zombie);
//    steve.showInventory();
//    steve.removeHP(20);
//    steve.addToInventory(5);
//    steve.showInventory();
//    steve.addToInventory(3);
//    steve.showInventory();
    lista_iteme->areAllType("Weapon");
    return 0;
}
