/*
   DESCRIERE: Programul simuleaza un sistem de licitatii.
   Date intrare: Obiectul licitat, pretul de pornire, candidatii si ofertele lor.
   Operatii: Verificare bugete, realocare dinamica pentru istoricul ofertelor,
             determinare castigator final.
*/


#include <iostream>
#include <cstring>

class Candidat {
private:
    char* nume;
    double buget;

public:
    Candidat() {
        this->nume = NULL;
        this->buget = 0;
    }

    Candidat(const char* n, double b) {
        if (n) {
            this->nume = new char[strlen(n) + 1];
            strcpy(this->nume, n);
        } else this->nume = NULL;
        this->buget = b;
    }

    Candidat(const Candidat& sursa) {
        if (sursa.nume) {
            this->nume = new char[strlen(sursa.nume) + 1];
            strcpy(this->nume, sursa.nume);
        } else this->nume = NULL;
        this->buget = sursa.buget;
    }

    Candidat& operator=(const Candidat& sursa) {
        if (this != &sursa) {
            if (this->nume) delete[] this->nume;
            if (sursa.nume) {
                this->nume = new char[strlen(sursa.nume) + 1];
                strcpy(this->nume, sursa.nume);
            } else this->nume = NULL;
            this->buget = sursa.buget;
        }
        return *this;
    }

    ~Candidat() {
        if (this->nume) delete[] this->nume;
    }

    const char* getNume() const { return this->nume; }
    double getBuget() const { return this->buget; }

    friend std::ostream& operator<<(std::ostream& out, const Candidat& c) {
        out << "Candidat: " << (c.nume ? c.nume : "Anonim") << " | Buget: " << c.buget;
        return out;
    }
};


class Oferta {
private:
    char* numeOfertant;
    double suma;

public:
    Oferta() : numeOfertant(NULL), suma(0) {}

    Oferta(const char* n, double s) {
        if (n) {
            this->numeOfertant = new char[strlen(n) + 1];
            strcpy(this->numeOfertant, n);
        } else this->numeOfertant = NULL;
        this->suma = s;
    }


    ~Oferta() { if (this->numeOfertant) delete[] this->numeOfertant; }

    Oferta(const Oferta& o) {
        if (o.numeOfertant) {
            this->numeOfertant = new char[strlen(o.numeOfertant) + 1];
            strcpy(this->numeOfertant, o.numeOfertant);
        } else this->numeOfertant = NULL;
        this->suma = o.suma;
    }

    Oferta& operator=(const Oferta& o) {
        if (this != &o) {
            if (this->numeOfertant) delete[] this->numeOfertant;
            if (o.numeOfertant) {
                this->numeOfertant = new char[strlen(o.numeOfertant) + 1];
                strcpy(this->numeOfertant, o.numeOfertant);
            } else this->numeOfertant = NULL;
            this->suma = o.suma;
        }
        return *this;
    }

    double getSuma() const { return this->suma; }
    const char* getAutor() const { return this->numeOfertant; }
};

class Licitatie {
private:
    char* titlu;
    Oferta* istoricOferte;
    int nrOferte;
    double pretMinim;

    bool validare(const Candidat& c, double s) const {
        if (s <= this->pretMinim) return false;
        if (s > c.getBuget()) return false;
        if (this->nrOferte > 0 && s <= this->istoricOferte[this->nrOferte - 1].getSuma()) return false;
        return true;
    }

public:
    Licitatie(const char* t, double p) {
        this->titlu = new char[strlen(t) + 1];
        strcpy(this->titlu, t);
        this->pretMinim = p;
        this->istoricOferte = NULL;
        this->nrOferte = 0;
    }

    ~Licitatie() {
        if (this->titlu) delete[] this->titlu;
        if (this->istoricOferte) delete[] this->istoricOferte;
    }
    void adaugaBid(const Candidat& c, double s) {
        if (!validare(c, s)) {
            std::cout << "[REJECT] Oferta lui " << c.getNume() << " de " << s << " nu e buna.\n";
            return;
        }

        Oferta* temp = new Oferta[this->nrOferte + 1];

        for (int i = 0; i < this->nrOferte; i++) {
            temp[i] = this->istoricOferte[i];
        }

        temp[this->nrOferte] = Oferta(c.getNume(), s);

        if (this->istoricOferte) delete[] this->istoricOferte;


        this->istoricOferte = temp;
        this->nrOferte++;

        std::cout << "[SUCCESS] Oferta de " << s << " de la " << c.getNume() << " a fost inregistrata.\n";
    }

    void afisareFinala() const {
        std::cout << "\n----------------------------------\n";
        std::cout << "LICITATIE: " << this->titlu << "\n";
        if (this->nrOferte == 0) {
            std::cout << "Rezultat: Nicio oferta acceptata.\n";
        } else {
            const Oferta& finala = this->istoricOferte[this->nrOferte - 1];
            std::cout << "CASTIGATOR: " << finala.getAutor() << "\n";
            std::cout << "PRET FINAL: " << finala.getSuma() << " EUR\n";
        }
        std::cout << "----------------------------------\n";
    }
};

int main() {

    Licitatie lic("Geanta vintage", 5000.0);

    Candidat c1("Andrei", 15000.0);
    Candidat c2("Vasile", 8000.0);

    std::cout << "Obiect licitat: Geanta vintage (Start: 5000 EUR)\n\n";

    lic.adaugaBid(c1, 5500.0);
    lic.adaugaBid(c2, 6000.0);
    lic.adaugaBid(c1, 7500.0);
    lic.adaugaBid(c2, 9000.0);
    lic.adaugaBid(c1, 7000.0);

    lic.afisareFinala();

    return 0;
}
