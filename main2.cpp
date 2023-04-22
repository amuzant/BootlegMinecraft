#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

class Inventory
{
    int sizee;
    int* data;
    public:
    Inventory():data(nullptr),sizee(0){}
    Inventory(int k, int x=0)
        {
            int* v=new int[k];
            for(int i=0;i<k;i++)
                v[i]=x;
            sizee=k;
            data=v;
            v=nullptr;
            delete v;
        }
    ~Inventory()
        {
            delete[] data;
        }
    Inventory(Inventory &t)
    {
        sizee=t.sizee;
        data=new int[sizee];
        for(int i=0;i<sizee;i++)
            data[i]=t.data[i];
    }
    void show()
    {
        cout<<sizee<<" total slots:"<<endl;
        for(int i=0;i<sizee;i++)
            cout<<data[i]<<" ";
        cout<<endl;
    }
    Inventory operator=(Inventory const &obj)
    {
        if (this!=&obj)
        {
            if(data!=nullptr) delete[] data;
            sizee=obj.sizee;
            data=new int[sizee];
            for(int i=0;i<sizee;i++)
                data[i]=obj.data[i];
        }
        return *this;
    }
    friend ostream& operator << (ostream &out, const Inventory &c);
    friend istream& operator >> (istream &in, Inventory &c);
    const void reset();
    const void addItem(int itemId);
};

const void Inventory::reset()
{
    for(int i=0;i<sizee;i++)
        data[i]=0;
}

const void Inventory::addItem(int itemId)
{
    int i=0;
    bool itemAdded=false;
    while(i<sizee)
    {
        if(data[i]==0)
        {
            data[i]=itemId;
            itemAdded=true;
            cout<<"The item (add function for itemid) "<<itemId<<" has been added successfully.\n";
            break;
        }
    }
    if(itemAdded==false) cout<<"The item (add function for itemid) "<<itemId<<" couldn't be added to your inventory. (Inventory Full)\n";
}

ostream& operator << (ostream &out, const Inventory &c)
{
    for(int i=0;i<c.sizee;i++)
        out<<c.data[i]<<" ";
    out<<endl;
    return out;
}

istream& operator >> (istream &in, Inventory &c)
{
    in>>c.sizee;
    for(int i=0;i<c.sizee;i++)
        in>>c.data[i];
    return in;
}

class Items
{
    int id;
    char* type;
    char* nume;
    int breakable_by_id;
    int damage;
    Items* next=nullptr;
public:
    Items()
    {
        id=0;
        type=0;
        damage=0;
        breakable_by_id=0;
        next=nullptr;
    }
    ~Items()
    {
        delete[] type;
        delete[] nume;    
    }
    Items(const char* t,const char* n,int d=0,int b=0,int i=0)
    {
        id=i;

        type = new char[strlen(t)+1];
        strcpy(type,t);
        type[strlen(t)]='\0';

        nume = new char[strlen(n)+1];
        strcpy(nume,n);
        nume[strlen(n)]='\0';

        damage=d;
        breakable_by_id=b;
    }
    void setNext(Items* item);
    Items* getNext(Items* item);
    const char* getName(Items* item);
    friend ostream& operator<<(ostream& out, const Items& item);
    Items& operator=(Items const &obj)
    {
        if (this!=&obj)
        {
            if(next!=nullptr) delete[] next;
            if(type!=nullptr) delete[] type;
            if(nume!=nullptr) delete[] nume;
            this->nume=obj.nume;
            this->next=obj.next;
            this->type=obj.type;
            this->id=obj.id;
            this->breakable_by_id=obj.breakable_by_id;
            this->damage=obj.damage;
        }
        return *this;
    }
};

void Items::setNext(Items* item)
{
    this->next=item;
}

Items* Items::getNext(Items* item)
{
    return item->next;
}

const char* Items::getName(Items* item)
{
    return item->nume;
}

class ItemList
{
    Items* head=nullptr;
    Items* tail=nullptr;
    int itemindex=0;
public:
    void adauga(const char* t,const char* n,int d=0,int b=0,int i=0);
    void afisare();
    ~ItemList()
    {
        delete[] head;
        delete[] tail;
    }
    /**/
    ItemList& operator=(ItemList const &obj)
    {
        if (this!=&obj)
        {
            if(head!=nullptr) delete[] head;
            if(tail!=nullptr) delete[] tail;
            Items *i=new Items();
            Items *j=new Items();
            i=obj.head;
            j=this->head;
            while(i!=nullptr)
            {
                j=i;
                cout<<j->getNext(j);
                i=i->getNext(i);
                j=j->getNext(j);
            }
            i=nullptr;
            j=nullptr;
            delete i;
            delete j;
            this->head=obj.head;
            this->tail=obj.tail;
            this->itemindex=obj.itemindex;

        }
        return *this;
    }
};

void ItemList::adauga(const char* t,const char* n,int d,int b,int i)
    {
        itemindex++;
        Items* item=new Items(t,n,d,b,itemindex);
        if(head==nullptr) head=item;
        if(tail!=nullptr) tail->setNext(item);
        tail=item;
        item=nullptr;
        delete item;
    }
void ItemList::afisare()
    {
        cout<<"Here's a list of the items available:\n";
        Items *i=new Items();
        i=head;
        while(i!=nullptr)
        {
            cout<<*i;
            i=i->getNext(i);
        }
        delete i;
        cout<<endl;
    }

ostream& operator<<(ostream& out, const Items& item)
{
    out<<"Item info:"<<endl;
    out<<"Id: "<<item.id<<endl;
    out<<"Name: "<<item.nume<<endl;
    out<<"Item type: "<<item.type<<endl;
    if(strcmp("Block",item.type)==0) 
    {
        out<<"Breakable by ";
        if(item.breakable_by_id!=0) out<<"item id: "<<item.breakable_by_id<<endl;
        else out<<"anything!\n";
    }
    return out;
}

class Mob;

class Player
{
private:
    float hp;
    float damage;
    Inventory inventory;
    ItemList lista_iteme;
public:
    Player(){
        hp=20;
        damage=1;
        inventory=27;
    }
    Player(const Player& other){
        this->hp = other.hp;
        this->damage = other.damage;
        this->inventory = other.inventory;
    }
    const float getHP();
    const float getDamage();
    const void removeHP(float hitDamage);
    friend ostream& operator<<(ostream& out, const Player& player);
    const void addToInventory(int itemId);
    const void attack(Mob &m);
    const bool alive();
    const void showInventory();
    const void loot();
    const void setList(ItemList lista);
    const void afisItemList();
    const void setHP(int h);
    const void setDamage(int dmg);
};
const void Player::afisItemList()
{
    lista_iteme.afisare();
}

const void Player::setList(ItemList lista)
{
    lista_iteme=lista;
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
    cout<<"Player took "<<hitDamage<<" Damage.\n";
    if(hp<=0)
    {
        cout<<"Player has died.\n";
        //reset the inventory
        inventory.reset();
        //reset the damage
        damage=1;
        cout<<"Do you want to respawn? (y\\n): ";
        char respawn;
        cin>>respawn;
        if(respawn=='y'||respawn=='Y')
        {
            //reset the hp
            hp=20;
            cout<<"Player has respawned!\n";
        }
    }
}
ostream& operator<<(ostream& out, const Player& player)
{
    out<<"Player stats:"<<endl;
    out<<"HP: "<<player.hp<<endl;
    out<<"Hit damage: "<<player.damage<<endl;
    return out;
}

const void Player::addToInventory(int itemId)
{
    cout<<"adding "<<itemId<<" to your inventory."<<endl;
    inventory.addItem(itemId);
}

const void Player::loot()
{

}

class Mob
{
    char* nume;
    float hp;
    float damage;
    int drop_item;
    bool hostile;
    ItemList lista_iteme;
public:
    Mob()
    {
        cout<<"You haven't specified the mob type, so we made a cow instead\n";
        hp=20,hostile=0,drop_item=1;
        nume = new char[3];
        strcpy(nume,"Cow");
    }
    ~Mob()
    {
        delete[] nume;
    }
    Mob(const char* name)
    {
        nume = new char[strlen(name)+1];
        strcpy(nume,name);
        

        if(strcmp(nume,"Cow")==0)
            hp=10,hostile=0,drop_item=1;
        else if(strcmp(nume,"Pig")==0)
            hp=10,hostile=0,drop_item=2;
        else if(strcmp(nume,"Villager")==0)
            hp=10,hostile=0;
        else if(strcmp(nume,"Wolf")==0)
            hp=8,hostile=0; 
        else if(strcmp(nume,"Zombie")==0)
            hp=20,hostile=1,drop_item=3,damage=4.5;
        else if(strcmp(nume,"Creeper")==0)
            hp=20,hostile=1,drop_item=4;
        else if(strcmp(nume,"Skeleton")==0)
            hp=20,hostile=1,drop_item=5,damage=5;
        else
            {hp=20,hostile=0,drop_item=1;
            cout<<"You haven't selected a valid mob, so we made a cow instead\n";}
        nume[strlen(name)]='\0';
    }
    const bool alive();
    const void attack(Player &p); 
    const void removeHP(float hitDamage);
    const char* getName();
    const int getDamage();
    const int getItem();
    const float getHP();
    const void setList(ItemList lista);
    const void afisItemList();
    friend ostream& operator<<(ostream& out, const Mob& mob);
    Mob& operator=(const Mob& other) {
        if(this != &other) {
            if(nume!=nullptr) delete[] nume;

            nume = new char[strlen(other.nume)];
            strcpy(this->nume,other.nume);

            this->hp=other.hp;
            this->damage=other.damage;
            this->drop_item=other.drop_item;
            this->hostile=other.hostile;
        }
        return *this;
    }
};

ostream& operator<<(ostream& out, const Mob& mob)
{
    
    out<<"Mob stats:"<<endl;
    out<<"HP: "<<mob.hp<<endl;
    out<<"Hit damage: "<<mob.damage<<endl;

    //tipul mobului
    out<<"Type: ";
    if(mob.hostile==1) out<<"Hostile (";
    else out<<"Peaceful (";
    out<<mob.nume<<")"<<endl;

    return out;
}

const void Mob::afisItemList()
{
    lista_iteme.afisare();
}
const float Mob::getHP()
{
    return hp;
}
const int Mob::getDamage()
{
    return damage;
}

const int Mob::getItem()
{
    return drop_item;
}

const char* Mob::getName()
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

const void Mob::setList(ItemList lista)
{
    lista_iteme=lista;
}

const void Player::attack(Mob &m)
{
        if(this->alive()==true)
        {
            m.removeHP(damage);
            if(m.alive()==false) {addToInventory(m.getItem());}
        }    
    }

int singleplayer,current_player=0;
const char* nume_p1;const char* nume_p2;
int main()
{
    cout<<"Welcome to bootleg Minecraft!\n";
    
    ItemList lista_iteme;
    lista_iteme.adauga("Block","Wood",1,0);
    lista_iteme.adauga("Weapon","Sabie generica",3,0);
    lista_iteme.adauga("Weapon","Sabie buna",5,0);
    lista_iteme.adauga("Weapon","Sabie legendara",7,0);
    lista_iteme.afisare();

    //p1.setList(lista_iteme);
    //p1.afisItemList();

    //m1.setList(lista_iteme);
    //m1.afisItemList();
    
    Player steve;
    cout<<steve.getHP()<<endl;
    cout<<steve;
    steve.removeHP(3);
    steve.setDamage(rand()%20);
    steve.getDamage();
    Mob zombie("Zombie");
    zombie.attack(steve);
    cout<<steve;
    steve.attack(zombie);
    cout<<zombie.getHP();
    steve.setDamage(zombie.getHP()+1);
    steve.attack(zombie);
    steve.showInventory();
    
    
    return 0;
}