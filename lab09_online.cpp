/*
Sa se implementeze o clasa Spital, conform urm cerinte:
Clasa are cel putin urm atribute:
	- cif (cod de identificare fiscala - valoare de tip sir de caractere - 
	se atribuie valoare la crearea obiectului si apoi nu mai poate fi modificata) 
	- nume (sir de caractere)
	- adresa --
	- medici (vectori de valori string, alocat dinamic)
	- nrMedici
	- nrSpitale (va retine nr de spitale - obiecte de tip Spital instantiate vreodata)
				- static int

Se vor implementa:
- constructor fara parametri
- constructor cu toti parametrii necesari instantierii unui obiect complet
- constructor de copiere
- destructor

- supraincarcare operator =
- supraincarcare operatori de citire si scriere din/in consola (>> si <<)
- supraincarcare op [] - returneaza medicul de pe o pozitie data -- atat in mod scriere
						cat si in mod citire
- supraincarcare op !
- cast explicit int - returneaza nr de spitale instantiate

- metode de get si set
- cel putin unul dintre atributele de tip sir de caractere trb sa fie tip char*
- toate atributele sa fie private
*/

#include <iostream>
#include <string>
using namespace std;

class Spital
{
private:
	const string cif;
	char* nume;
	string adresa;
	string* medici;
	int nrMedici;
	static int nrSpitale;


public:

	//constructor fara param

	Spital() :cif("")
	{
		this->nume = nullptr;
		this->adresa = "";
		this->medici = nullptr;
		this->nrMedici = 0;
		Spital::nrSpitale++;//operatorul de scop
	}

	//constructor cu param

	Spital(string cif, const char* nume, string adresa, const string* medici, int nrMedici):
		cif(cif), adresa(adresa), nrMedici(nrMedici)
	{
		if (nume != nullptr)
		{
			this->nume = new char[strlen(nume) + 1]; //1=terminatorul de sir
			strcpy_s(this->nume, strlen(nume) + 1, nume);
		}
		else
			this->nume = nullptr;

		this->medici = new string[nrMedici];
		for (int i = 0; i < nrMedici; i++)
		{
			this->medici[i] = medici[i];
		}
		Spital::nrSpitale++;
	}

	//constructor de copiere

	Spital(Spital& s) : cif(s.cif)
	{
		if (s.nume != nullptr)
		{
			this->nume = new char[strlen(s.nume) + 1];
			strcpy_s(this->nume, strlen(s.nume) + 1, s.nume);
		}
		else
		{
			this->nume = nullptr;
		}

		this->adresa = s.adresa;

		if (s.medici != nullptr && s.nrMedici > 0)
		{
			this->nrMedici = s.nrMedici;
			this->medici = new string[s.nrMedici];
			for (int i = 0; i < s.nrMedici; i++)
			{
				this->medici[i] = s.medici[i];
			}
		}
		else
		{
			this->medici = nullptr;
			this->nrMedici = 0;
		}
	}

	//set

	void setNume(const char* nume)
	{
		if (nume != nullptr)
		{
			delete[] this->nume;
			this->nume = new char[strlen(nume) + 1]; 
			strcpy_s(this->nume, strlen(nume) + 1, nume);
		}
		else this->nume = nullptr;
	}

	void setAdresa(string adresa) { this->adresa = adresa; }
	void setMedici(const string* medici, int nrMedici)
	{
		if (medici != nullptr && nrMedici>0)
		{
			delete[] this->medici;
			this->nrMedici = nrMedici;
			this->medici = new string[nrMedici];
			for (int i = 0; i < nrMedici; i++)
			{
				this->medici[i] = medici[i];
			}
		}
		else
		{
			this->medici = nullptr;
			this->nrMedici = 0;
		}
	}


	//get

	char* getNume()
	{
		char* copy = new char[strlen(this->nume) + 1];
		strcpy_s(copy, strlen(this->nume) + 1, this->nume);
		return copy;
	}


	//suprainc =
	
	Spital& operator = (Spital& s)
	{ 
		if (this == &s)
			return *this;

		delete[] this->nume;
		this->nume = new char[strlen(s.nume) + 1];
		strcpy_s(this->nume, strlen(s.nume) + 1, s.nume);

		delete[] this->medici;
		this->nrMedici = nrMedici;
		this->medici = new string[s.nrMedici];
		for (int i = 0; i < s.nrMedici; i++)
		{
			this->medici[i] = s.medici[i];
		}
		this->adresa = s.adresa;
		return *this;
	}
	
	//suprainc op afisare

	friend ostream& operator << (ostream& os, Spital s);

	//suprainc op citire

	friend istream& operator >> (istream& is, Spital& s)
	{
		char* tmp = new char[256];
		cout <<endl<< endl<<  "Nume: ";
		is.getline(tmp, 256);
		s.setNume(tmp);

		cout << "Adresa: ";
		is.getline(tmp, 256);
		s.setAdresa(tmp);

		cout << "Numar de medici:";
		int tmpNr;
		is >> tmpNr;
		is.getline(tmp, 256);
		cout << "Numele pentru " << tmpNr << " medici: ";
		string* medici = new string[tmpNr];
		for (int i = 0; i < tmpNr; i++)
		{
			is.getline(tmp, 256);
			medici[i] = (string)tmp;
		}
		s.setMedici(medici, tmpNr);
		return is;
	}

	//destructor

	~Spital()
	{
		delete[]this->nume;
		delete[]this->medici;
		Spital::nrSpitale--;
	}
};

ostream& operator << (ostream& os, Spital s)
{
	os << "CIF: " << s.cif << endl;
	os << "Nume: " << s.nume << endl;
	os << "Adresa: " << s.adresa << endl;
	os << "Numar medici: " << s.nrMedici << endl;
	for (int i = 0; i < s.nrMedici; i++)
	{
		os << s.medici[i] << "   ";
	}
	return os;
};


int Spital::nrSpitale = 0; //initializam variabila de tip static int

int main()
{
	string med[] = { "Med1", "Med2", "Med3" };
	Spital s1, s2("RO123", "Floreasca", "Bucuresti", med, 3);
	
	s1 = s2;
	s1.setNume("Alt nume");

	cout << s2;
	Spital s3;

	cin >> s3;
	return 0;
};