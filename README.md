# Bootleg Minecraft
<hr>

Am dezvoltat cateva functionalitati ale jocului Minecraft prin programarea orientata pe obiecte in C++.

Programul meu foloseste clasele: 
- Items
- ItemDB (singleton, database-ul care contine fiecare item intr-un vector de obiecte de tip Items, functia areAllType foloseste all_of prin un lambda expression)
- Inventory (inventarul player-ului, foloseste lista de iteme pentru convenienta, mobs au doar (optional) weapon si drop item, are variabila statica pentru marimea unui inventar)
- Entity (clasa interfata pentru clasele Mob, Player)
- ItemDBAccess (clasa abstracta, ofera access la database claselor care o mostenesc)
- Mob (mosteneste protected IDA, public Entity)
- Player (mosteneste protected IDA, public Entity, are functii statice, functia loot care foloseste random pentru obtinerea unui item random)
- Hostile si Peaceful Mob, care mostenesc clasa Mob, folosesc constructor cu parametrii pentru Mob prin lista de initializare
<br>
De asemenea am exceptiile custom MobException folosita pentru a identifica fie MobInvalidHP (hp negativ in construirea unei instante pentru un mob custom) sau MobUndeclaredHP (hp nedeclarat pentru un mob custom)
<br>
