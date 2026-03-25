Proiect POO - Tema Licitatii
Student: Dumitrascu Ioana Alexandra
Grupa: 132
Descrierea proiectului:
Programul gestioneaza procesul de licitare pentru diverse obiecte. Acesta permite adaugarea de candidati cu un anumit buget si depunerea de oferte. Sistemul verifica automat daca ofertele sunt valide (daca suma este mai mare decat oferta precedenta si daca persoana are banii necesari).
Detalii tehnice:
Proiectul este scris in C++ si respecta cerintele de a nu folosi biblioteci STL.
Am utilizat char* pentru nume si am gestionat manual memoria prin alocare dinamica.
Fiecare clasa are implementat constructorul de copiere, operatorul egal si destructorul pentru a nu avea pierderi de memorie.
Tabloul de oferte din clasa Licitatie este realocat manual la fiecare intrare noua.
Clase folosite:
Candidat: Retine numele si bugetul.
Oferta: Retine cine a licitat si ce suma.
Licitatie: Clasa principala care coordoneaza procesul si gaseste castigatorul.
Scenariul din main:
Am creat o licitatie de test si doi candidati. Am simulat mai multe oferte, unele acceptate si altele respinse, pentru a demonstra logica de functionare si afisarea rezultatului final.