Game:
Kontrole: W - gore, S - dole, A - lijevo, D - desno, RAZMAK - pucanje, Q - 1. laser, E - 2. laser

Projekt "Engine" je preuzet (nije moj).

Projekt "GraphicTutBen" je igra koju sam napravio i koja se pokreće preko "Engine" projekta.

32-bitna konfiguracija obavezna: Projekt se mora graditi i pokretati u 32-bitnoj konfiguraciji jer engine i neke dodatne biblioteke nemaju podršku za 64-bitne arhitekture.

Podržani operacijski sustav: Projekt je podržan samo na Windows operacijskim sustavima. Linux i macOS nisu podržani zbog ograničenja enginea i korištenih biblioteka.

Ovisnost o Engine projektu: Projekt GraphicTutBen ovisi o Engine projektu. U Visual Studio solution datoteci (GraphicTutBen.sln), ovisnosti su već postavljene, pa će se Engine automatski buildati prije GraphicTutBen-a.  

Ručno buildanje:  
Ako buildate projekte ručno (npr. putem CMake-a ili drugog build sustava), prvo buildajte Engine projekt kako biste generirali potrebne biblioteke.  
Zatim buildajte GraphicTutBen projekt koji koristi te biblioteke.  

Struktura projekta:
***************************************************************************************
GraphicTutBen/                        # Main project folder

├── Dev/                              # Development-related files

├── Engine/                           # Engine folder

├── GraphicTutBen/                    # Game folder

│   ├── Levels/                       # Level folder

│   │   ├── LevelOne.txt              # Level data file

│   ├── Shaders/                      # Folder for shader files, glsl

│   ├── Textures/                     # Folder for texture assets

├── GraphicTutBen.sln                 
***************************************************************************************

Za pokretanje:  
Za ispravno pokretanje projekta, sljedeće DLL datoteke iz direktorija Dev moraju biti kopirane u Debug i/ili Release direktorije, ovisno o konfiguraciji u kojoj gradite projekt:  
freeglut.dll  
glew32.dll  
libfreetype-6.dll  
SDL2.dll  
SDL2_ttf.dll  
zlib1.dll  
***************************************************************************************
LevelOne.txt u direktoriju GraphicTutBen/Levels/ definira valove neprijatelja u igri. Svaki val neprijatelja opisan je s tri reda koji specificiraju broj neprijateljskih brodova, njihov tip i putanju kretanja.  
Format vala
***************************************************************************************
Prvi red: NumberOfEnemyShips: <broj> - Broj neprijateljskih brodova u valu (cijeli broj, npr. 4).  
Drugi red: TypeOfEnemyShips: <tip> - Tip broda (npr. DRONE, GUN_SHIP, BATTLE_SHIP, DESTROYER).  
Treći red: EnemyTrajectory: <putanja> - Putanja kretanja (npr. VERTICAL, COS).  
***************************************************************************************
Svaka tri reda čine jedan val. Valovi se nižu jedan za drugim u datoteci.  
Na kraj datoteke dodajte tri nova reda za svaki novi val.  
Primjer dodavanja vala:
***************************************************************************************
NumberOfEnemyShips: 5  
TypeOfEnemyShips: DRONE  
EnemyTrajectory: COS  
***************************************************************************************
Uređivanje postojećeg vala:  
Pronađite tri reda koji odgovaraju valu koji želite promijeniti.  
Zamijenite vrijednosti:  
***************************************************************************************
NumberOfEnemyShips: Promijenite broj (npr. 4 u 6).  
TypeOfEnemyShips: Promijenite tip (npr. DRONE u BATTLE_SHIP).  
EnemyTrajectory: Promijenite putanju (npr. VERTICAL u COS).
***************************************************************************************

Opcija "Options" u glavnom izborniku igre nije implementirana.
