/*
   DESCRIERE: Programul simuleaza un sistem de licitatii.
   Date intrare: Obiectul licitat, pretul de pornire, candidatii si ofertele lor.
   Operatii: Verificare bugete, realocare dinamica pentru istoricul ofertelor,
             determinare castigator final.
*/

#include <iostream>
#include <cstring>

class Candidat
{
private:
    char* nume;     /// numele candidatului alocat dinamic
    double buget;   /// suma maxima de care dispune candidatul

public:
    /// Constructor implicit
    Candidat()
    {
        this->nume = NULL;
        this->buget = 0;
    }

    /// Constructor de initializare
    Candidat(const char* n, double b)
    {
        if (n)
        {
            this->nume = new char[strlen(n) + 1];
            strcpy(this->nume, n);
        }
        else this->nume = NULL;
        this->buget = b;
    }

    /// Constructor de copiere
    Candidat(const Candidat& sursa)
    {
        if (sursa.nume)
        {
            this->nume = new char[strlen(sursa.nume) + 1];
            strcpy(this->nume, sursa.nume);
        }
        else this->nume = NULL;
        this->buget = sursa.buget;
    }

    /// Operator de atribuire
    Candidat& operator=(const Candidat& sursa)
    {
        if (this != &sursa)
        {
            if (this->nume) delete[] this->nume; /// eliberare memorie veche
            if (sursa.nume)
            {
                this->nume = new char[strlen(sursa.nume) + 1];
                strcpy(this->nume, sursa.nume);
            }
            else this->nume = NULL;
            this->buget = sursa.buget;
        }
        return *this;
    }

    /// Destructor - elibereaza memoria ocupata de nume
    ~Candidat()
    {
        if (this->nume) delete[] this->nume;
    }

    /// Getteri
    const char* getNume() const { return this->nume; }
    double getBuget() const { return this->buget; }

    /// Operator>> pentru citirea de la tastatura fara std::string
    friend std::istream& operator>>(std::istream& in, Candidat& c)
    {
        char buffer[100]; /// buffer temporar pentru citirea numelui
        std::cout << "Introduceti numele candidatului: ";
        in >> buffer;

        if (c.nume) delete[] c.nume; /// curatam memoria inainte de o noua citire
        c.nume = new char[strlen(buffer) + 1];
        strcpy(c.nume, buffer);

        std::cout << "Introduceti bugetul pentru " << c.nume << ": ";
        in >> c.buget;
        return in;
    }

    /// Operator<< pentru afisarea detaliilor candidatului
    friend std::ostream& operator<<(std::ostream& out, const Candidat& c)
    {
        out << "Candidat: " << (c.nume ? c.nume : "Anonim") << " | Buget: " << c.buget;
        return out;
    }
};


class Oferta
{
private:
    char* numeOfertant; /// numele celui care a facut oferta
    double suma;        /// valoarea oferita

public:
    /// Constructor implicit
    Oferta() : numeOfertant(NULL), suma(0) {}

    /// Constructor de initializare
    Oferta(const char* n, double s)
    {
        if (n)
        {
            this->numeOfertant = new char[strlen(n) + 1];
            strcpy(this->numeOfertant, n);
        }
        else this->numeOfertant = NULL;
        this->suma = s;
    }

    /// Destructor
    ~Oferta() { if (this->numeOfertant) delete[] this->numeOfertant; }

    /// Constructor de copiere
    Oferta(const Oferta& o)
    {
        if (o.numeOfertant)
        {
            this->numeOfertant = new char[strlen(o.numeOfertant) + 1];
            strcpy(this->numeOfertant, o.numeOfertant);
        }
        else this->numeOfertant = NULL;
        this->suma = o.suma;
    }

    /// Operator de atribuire
    Oferta& operator=(const Oferta& o)
    {
        if (this != &o)
        {
            if (this->numeOfertant) delete[] this->numeOfertant;
            if (o.numeOfertant)
            {
                this->numeOfertant = new char[strlen(o.numeOfertant) + 1];
                strcpy(this->numeOfertant, o.numeOfertant);
            }
            else this->numeOfertant = NULL;
            this->suma = o.suma;
        }
        return *this;
    }

    /// Getteri
    double getSuma() const { return this->suma; }
    const char* getAutor() const { return this->numeOfertant; }
};

class Licitatie
{
private:
    char* titlu;            /// titlul obiectului licitat
    Oferta* istoricOferte;  /// vector de oferte alocat dinamic
    int nrOferte;           /// numarul curent de oferte inregistrate
    double pretMinim;       /// pretul de la care porneste licitatia

    static int nrTotalOfertanti; /// atribut static: numara ofertele acceptate global

    /// Metoda privata pentru validarea regulilor licitatiei
    bool validare(const Candidat& c, double s) const
    {
        if (s <= this->pretMinim) return false; /// sub pretul de pornire
        if (s > c.getBuget()) return false;     /// depaseste bugetul candidatului
        if (this->nrOferte > 0 && s <= this->istoricOferte[this->nrOferte - 1].getSuma()) return false; /// mai mica decat oferta precedenta
        return true;
    }

public:
    /// Constructor de initializare
    Licitatie(const char* t, double p)
    {
        this->titlu = new char[strlen(t) + 1];
        strcpy(this->titlu, t);
        this->pretMinim = p;
        this->istoricOferte = NULL;
        this->nrOferte = 0;
    }

    /// Destructor
    ~Licitatie()
    {
        if (this->titlu) delete[] this->titlu;
        if (this->istoricOferte) delete[] this->istoricOferte;
    }

    /// fct- adaugarea unei oferte prin realocare dinamica
    void adaugaBid(const Candidat& c, double s)
    {
        if (!validare(c, s))
        {
            std::cout << "[REJECT] Oferta lui " << c.getNume() << " de " << s << " nu e buna.\n";
            return;
        }

        Licitatie::nrTotalOfertanti++; /// incrementare membru static

        /// Incepe procesul de realocare dinamica
        Oferta* temp = new Oferta[this->nrOferte + 1]; /// alocam spatiu nou (n+1)

        for (int i = 0; i < this->nrOferte; i++)
        {
            temp[i] = this->istoricOferte[i]; /// copiem ofertele vechi
        }

        temp[this->nrOferte] = Oferta(c.getNume(), s); /// adaugam noua oferta

        if (this->istoricOferte) delete[] this->istoricOferte; /// eliberam vectorul vechi

        this->istoricOferte = temp; /// mutam pointerul la noul vector
        this->nrOferte++;

        std::cout << "[SUCCESS] Oferta de " << s << " de la " << c.getNume() << " a fost inregistrata.\n";
    }

    /// Functie statica pentru accesarea contorului global
    static int getNrTotalOfertanti()
    {
        return nrTotalOfertanti;
    }

    /// Afisarea rezultatului final al licitatiei
    void afisareFinala() const
    {
        std::cout << "\n----------------------------------\n";
        std::cout << "LICITATIE: " << this->titlu << "\n";
        if (this->nrOferte == 0)
            std::cout << "Rezultat: Nicio oferta acceptata.\n";
        else
        {
            const Oferta& finala = this->istoricOferte[this->nrOferte - 1];
            std::cout << "CASTIGATOR: " << finala.getAutor() << "\n";
            std::cout << "PRET FINAL: " << finala.getSuma() << " EUR\n";
        }
        std::cout << "Statistica: " << Licitatie::nrTotalOfertanti << " oferte reusite pana acum.\n";
        std::cout << "----------------------------------\n";
    }
};

/// Initializarea membrului static
int Licitatie::nrTotalOfertanti = 0;

int main()
{
    Licitatie lic("Geanta vintage", 5000.0);
    Candidat c1, c2;

    /// Folosim operatorul overloadat >> pentru citire
    std::cout << "Configurare Candidati:\n";
    std::cin >> c1;
    std::cin >> c2;

    std::cout << "\nIncepem licitatia pentru: Geanta vintage\n\n";

    lic.adaugaBid(c1, 5500.0);
    lic.adaugaBid(c2, 6000.0);
    lic.adaugaBid(c1, 7500.0);
    lic.adaugaBid(c2, 9000.0);
    lic.adaugaBid(c1, 7000.0); /// oferta respinsa

    lic.afisareFinala();

    return 0;
}
