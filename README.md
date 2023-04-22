# Tema1-POO

Am dezvoltat cateva functionalitati ale jocului Minecraft prin programarea orientata pe obiecte.

Programul meu foloseste cinci clase: Inventory, Items + ItemList (LinkedList cu Items ca nod), Mob, Player

Compunerea este realizata in urmatoarele moduri:
Items* in ItemList (ca un nod)
Inventory in Player (fiecare player are un inventar)

Functionalitati:

Inventory:<br>
Resetarea acestuia<br>
Adaugarea itemelor in acesta<br>
Suprascrierea operatorilor >>, << pentru adaugarea datelor mai convenient, fiind un vector.

Items:<br>
Setarea si returnarea nodului urmator<br>
Obtinerea numelui itemelor<br>
Suprascrierea << pentru afisarea tuturor campurilor<br>
Suprascrierea = pentru transferarea tuturor campurilor

ItemList:<br>
Functie de adaugare al unui nod(item) nou<br>
Functie de afisare al intregii liste de iteme<br>
Suprascrierea = pentru transferarea tuturor campurilor (si nodurilor, dar nu pare sa functioneze)

Player:<br>
Suprascrierea << pentru afisarea statsurilor complete (uitasem sa scriu)<br>
Setarea si obtinerea HP-ului<br>
Setarea si obtinerea (Hit) Damage-ului<br>
Scaderea HP-ului<br>
Atacarea unui Mob<br>
Verificarea daca este in viata (HP)<br>
Afisarea inventarului

Mob:<br>
Suprascrierea << pentru afisarea statsurilor complete (uitasem sa scriu)<br>
Verificarea daca este in viata (HP)<br>
Atacarea unui Player<br>
Obtinerea numelui (Cow, Pig etc.)<br>
Obtinerea (hit) damage-ului acestuia<br>
Obtinerea id-ului itemului care este dropat la moarte <br>
Obtinerea HP-ului

Cateva functionalitati nu au reusit sa le implementez din cauza faptului ca nu imi reusea transferul listei inlantuite in interiorul claselor de player, respectiv mob, pentru a avea access ambele la inventar. Insa consider ca am indeplinit cerintele.
