#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Person {
public:
    Person() : name(nullptr), age(0), zodie(nullptr) {}
    Person(const string& n, int a, const string& z) : age(a) {
        name = new char[n.size() + 1];
        strcpy_s(name, n.size() + 1, n.c_str());

        zodie= new char[z.size() + 1];
        strcpy_s(zodie, z.size() + 1, z.c_str());
    }

    // Destructor pentru a elibera memoria alocata dinamic
    ~Person() {
        delete[] name;
        delete[] zodie;
    }

    // Funcție de serializare
    void Serialize(ofstream& ofs) const {
        size_t nameLength = strlen(name) + 1;
        ofs.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength)); // Scriem lungimea numelui
        ofs.write(name, nameLength);

        ofs.write(reinterpret_cast<const char*>(&age), sizeof(age));

        size_t zodieLength = strlen(zodie) + 1;
        ofs.write(reinterpret_cast<const char*>(&zodieLength), sizeof(zodieLength));
        ofs.write(zodie, zodieLength);

        //in cazul sirurilor de caractere citim intai lungimea sirului si apoi sirul
    }

    // Funcție de deserializare
    void Deserialize(ifstream& ifs) {
        size_t nameLength;
        ifs.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength)); // Citim lungimea numelui
        delete[] name; //vreau sa aloc peste o zona deja scrisa - trebuie dezalocata
        name = new char[nameLength];
        ifs.read(name, nameLength);

        ifs.read(reinterpret_cast<char*>(&age), sizeof(age));

        size_t zodieLength;
        ifs.read(reinterpret_cast<char*>(&zodieLength), sizeof(zodieLength));
        delete[] zodie;
        zodie = new char[zodieLength];
        ifs.read(zodie, zodieLength);
    }

    void DisplayInfo() const {
        cout << "Name: " << name << ", Age: " << age << ", Zodie: "<< zodie<< endl;
    }

private:
    char* name;
    int age;
    char* zodie;
};

int mainSD() {
    // Salvare obiect într-un fișier binar
    {
        ofstream outputFile("person.dat", ios::binary);
        if (!outputFile) {
            cerr << "Error opening file for writing." << endl;
            return 1;
        }

        Person personToSave("John Doe", 25, "leo");
        personToSave.Serialize(outputFile);

        cout << "Object saved successfully." << endl;
    }

    // Restaurare obiect din fișier binar
    {
        ifstream inputFile("person.dat", ios::binary);
        if (!inputFile) {
            cerr << "Error opening file for reading." << endl;
            return 1;
        }

        Person restoredPerson;
        restoredPerson.Deserialize(inputFile);

        cout << "Object restored successfully." << endl;
        restoredPerson.DisplayInfo();
    }

    return 0;
}
