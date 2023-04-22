# Tema1-POO

Am dezvoltat cateva functionalitati ale jocului Minecraft prin programarea orientata pe obiecte.

Programul meu foloseste cinci clase: Inventory, Items + ItemList (LinkedList cu Items ca nod), Mob, Player

Compunerea este realizata in urmatoarele moduri:
Items* in ItemList (ca un nod)
Inventory in Player (fiecare player are un inventar)

Functionalitati:

Inventory:
Resetarea acestuia
Adaugarea itemelor in acesta
Suprascrierea operatorilor >>, << pentru adaugarea datelor mai convenient, fiind un vector.

Items:
Setarea si returnarea nodului urmator
Obtinerea numelui itemelor
Suprascrierea << pentru afisarea tuturor campurilor
Suprascrierea = pentru transferarea tuturor campurilor

ItemList:
Functie de adaugare al unui nod(item) nou
Functie de afisare al intregii liste de iteme
Suprascrierea = pentru transferarea tuturor campurilor (si nodurilor, dar nu pare sa functioneze)

Player:
Setarea si obtinerea HP-ului
Setarea si obtinerea (Hit) Damage-ului
Scaderea HP-ului
Atacarea unui Mob
Verificarea daca este in viata (HP)
Afisarea inventarului

Mob:
Verificarea daca este in viata (HP)
Atacarea unui Player
Obtinerea numelui (Cow, Pig etc.)
Obtinerea (hit) damage-ului acestuia
Obtinerea id-ului itemului care este dropat la moarte 
Obtinerea HP-ului

Cateva functionalitati nu au reusit sa le implementez din cauza faptului ca nu imi reusea transferul listei inlantuite in interiorul claselor de player, respectiv mob, pentru a avea access ambele la inventar. Insa consider ca am indeplinit cerintele.
