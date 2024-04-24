# Minecraft RPG
<hr>

Am dezvoltat cateva functionalitati ale jocului Minecraft prin programarea orientata pe obiecte in C++, intr-o maniera RPG.

Programul meu foloseste clasele: 
- Items
- ItemDB (singleton, database-ul care contine fiecare item intr-un vector de obiecte de tip Items)
- Entity (clasa interfata pentru clasele Mob, Player)
- ItemDBAccess (clasa abstracta, ofera access la database claselor care o mostenesc)
- Mob (mosteneste protected IDA, public Entity, reprezinta restul de entitatii non-playable)
- Hostile si Peaceful Mob, care mostenesc clasa Mob, folosesc constructor cu parametrii pentru Mob prin lista de initializare, reprezentand clasele de mobi
- Player (mosteneste protected IDA, public Entity, are functii statice, functia loot care foloseste random pentru obtinerea unui item random din ItemDB)
- Inventory (inventarul player-ului, foloseste lista de iteme pentru convenienta, Mobs au doar (optional) weapon si drop item, are variabila statica pentru marimea unui inventar)
<br>
