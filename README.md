Proiect POO - Tema Licitatii

Student: Dumitrascu Ioana Alexandra

Grupa: 132

Descrierea proiectului:
Programul gestioneaza procesul de licitare pentru diverse obiecte. Acesta permite adaugarea de candidati cu un anumit buget si depunerea de oferte. Sistemul verifica automat daca ofertele sunt valide (daca suma este mai mare decat oferta precedenta si daca persoana are banii necesari).


Funcționalități Principale
*   Gestiune Participanți: Înregistrarea candidaților cu nume și buget maxim disponibil.
  
*   Validare Automată: Sistemul verifică dacă o ofertă respectă prețul minim, dacă ofertantul are fonduri suficiente și dacă oferta este superioară celei precedente.
  
*   Istoric Dinamic: Toate ofertele acceptate sunt stocate într-un vector alocat dinamic care se redimensionează la fiecare pas (Realocare Dinamică).
  
*   Statistici Globale: Monitorizarea numărului total de oferte acceptate la nivelul întregului sistem folosind membri statici.



Detalii tehnice:
Proiectul este scris in C++ si respecta cerintele de a nu folosi biblioteci STL.

Am utilizat char* pentru nume si am gestionat manual memoria prin alocare dinamica.

Fiecare clasa are implementat constructorul de copiere, operatorul egal si destructorul pentru a nu avea pierderi de memorie.

Tabloul de oferte din clasa Licitatie este realocat manual la fiecare intrare noua.

Supraîncărcarea Operatorilor:
    *   operator>>: Permite citirea directă și intuitivă a obiectelor de tip `Candidat` de la tastatură, incluzând gestionarea buffer-ului pentru nume.
    *   operator<<: Facilitează afișarea rapidă a detaliilor despre participanți într-un format lizibil.

Încapsulare: Toate atributele critice sunt private, accesul la ele fiind realizat exclusiv prin metode de tip *getter* sau prin logica internă de validare.



Clase folosite:

Candidat: Retine numele si bugetul.

Oferta: Retine cine a licitat si ce suma.

Licitatie: Clasa principala care coordoneaza procesul si gaseste castigatorul.

Scenariul din main:
Am creat o licitatie de test si doi candidati. Am simulat mai multe oferte, unele acceptate si altele respinse, pentru a demonstra logica de functionare si afisarea rezultatului final.

Exemplu de Rulare
1. Se configurează obiectul licitat și prețul de pornire.
2. Se introduc datele candidaților (Nume, Buget).
3. Se introduc succesiv ofertele (Bids).
4. Programul afișează în timp real dacă oferta a fost acceptată sau respinsă.
5. La final, se generează raportul cu câștigătorul și prețul final de adjudecare.
