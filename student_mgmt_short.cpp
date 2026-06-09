#include<iostream>
#include<fstream>
#include<string>
using namespace std;

struct Student {
    int id;
    string name;
    int age;
    float marks;
};

// Save one student to file
void addStudent() {
    Student s;
    ofstream f("students.txt", ios::app);
    cout << "\nEnter ID     : "; cin >> s.id;
    cout << "Enter Name   : "; cin.ignore(); getline(cin, s.name);
    cout << "Enter Age    : "; cin >> s.age;
    cout << "Enter Marks  : "; cin >> s.marks;
    f << s.id << "," << s.name << "," << s.age << "," << s.marks << "\n";
    f.close();
    cout << "\n✓ Student added!\n";
}

// Show all students
void showAll() {
    Student s;
    ifstream f("students.txt");
    char comma;
    cout << "\n--- All Students ---\n";
    cout << "ID  Name             Age  Marks\n";
    cout << "--------------------------------\n";
    while(f >> s.id >> comma) {
        getline(f, s.name, ',');
        f >> s.age >> comma >> s.marks;
        cout << s.id << "   " << s.name << "   " << s.age << "   " << s.marks << "\n";
    }
    f.close();
}

// Delete by ID (rewrite file without that record)
void deleteStudent() {
    int delId;
    cout << "\nEnter ID to delete: "; cin >> delId;
    ifstream fin("students.txt");
    ofstream fout("temp.txt");
    Student s;
    char comma;
    bool found = false;
    while(fin >> s.id >> comma) {
        getline(fin, s.name, ',');
        fin >> s.age >> comma >> s.marks;
        if(s.id == delId) { found = true; continue; }
        fout << s.id << "," << s.name << "," << s.age << "," << s.marks << "\n";
    }
    fin.close(); fout.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");
    cout << (found ? "\n✓ Deleted!\n" : "\n✗ ID not found.\n");
}

int main() {
    int ch;
    do {
        cout << "\n=== Student Management ===\n";
        cout << "1. Add Student\n";
        cout << "2. Show All\n";
        cout << "3. Delete Student\n";
        cout << "0. Exit\n";
        cout << "Choice: "; cin >> ch;
        if(ch==1) addStudent();
        else if(ch==2) showAll();
        else if(ch==3) deleteStudent();
    } while(ch != 0);
    return 0;
}
