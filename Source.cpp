//James Meeagn Employee Data Base


#include<fstream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;

class Employee
{
    int id;
    char firstName[20], lastName[20];
    char socialSecurityNumber[11];      //xxx-xxx-xxxx
    float salary;           //Don't think this allows for commas to be entered when giving salary for example
    int age;                //do 35000 instead of 35,000

public:
    void getdata(int i)
    {
        //read data from employee
        id = i + 1;
        cout << "First Name: ";
        cin >> firstName;
        cout << "Last Name: ";
        cin >> lastName;
        do {
            cout << "social Security Number (Enter in this format xxx-xxx-xxxx): ";
            cin >> socialSecurityNumber; //at the present moment its only accepting social security numbers that are 6 digits xxx-xxx would be an example
        } while (strchr(socialSecurityNumber, '-') == NULL);

        cout << "Salary: ";
        cin >> salary;
        cout << "Age: ";
        cin >> age;


    }

    void printData()
    {//print employee information
        cout << id << "\t" << firstName << "\t" << lastName << "\t" << socialSecurityNumber << "\t" << salary << "\t" << age << "\n";
    }

    int getID()
    {
        return id;
    }
    char* getSSN()
    {
        return socialSecurityNumber;
    }

}emp1, emp;


void addRecord(fstream& fio, int count);
bool searchbyID(fstream& fio, int id);
bool searchbySSN(fstream& fio, char ssn[]);
bool deleteRecord(fstream& fio, char ssn[]);
void display(fstream& fio);
int main()
{

    int count = 0;
    fstream fio("employeeInfo.dat", ios::in | ios::out);
    char ans = 'y';
    int ch;
    bool flag = false;
    int id;
    char ssn[11];
    while (!flag)
    {

        cout << "Select  1. Add record\n\t2. Delete Record\n\t3. Search Record by ID\n\t4. Display records\n\t5. Exit\n\t6. Search Record by SSN" << endl;
        
        cout << "\nEnter choice: ";
        cin >> ch;//read choice
        switch (ch)
        {
        case 1://add record into file
            addRecord(fio, count);
            count++;//adding index
            break;
        case 2:
            cout << "Enter a social security number for delete record: ";
            cin >> ssn;   //read sn for delete record          
            if (deleteRecord(fio, ssn) == false)
            {
                cout << "\nRecord not found in the file..!!\n";
                cout << "Press any key to exit...\n";
                exit(2);
            }
            break;
        case 3:
            cout << "Enter a employee ID for searching: ";
            cin >> id;//read employee id for search   record in file          
            if (searchbyID(fio, id) == false)
            {
                cout << "\nRecord not found in the file..!!\n";
                cout << "Press any key to exit...\n";
                exit(2);
            }
            break;
        case 6:

            cout << "Enter a social security number: ";
            cin >> ssn;//read social security number for search   record in file                      
            if (searchbySSN(fio, ssn) == false)
            {
                cout << "\nRecord not found in the file..!!\n";
                cout << "Press any key to exit...\n";
                exit(2);
            }
            break;
        case 4:
            display(fio);//display emlpoyees information
            break;
        case 5:
            flag = true;//set flag to true to exit
            break;
        default:
            cout << "Enter valid choice only." << endl;

        }
    }
    fio.close();
    return 0;
}
void addRecord(fstream& fio, int count)
{
    //add record into file
    emp1.getdata(count);
    fio.write((char*)&emp1, sizeof(emp1));//write record on file
}
bool searchbySSN(fstream& fio, char ssn[])//search by employee social Security Number
{
    //search record in file
    int pos;
    fio.seekg(0);
    while (!fio.eof())
    {
        pos = fio.tellg();//get positon of cursur
        fio.read((char*)&emp1, sizeof(emp1));//read record from file
        if (strncmp(emp1.getSSN(), ssn, 3) == 0)//campare ssn with emp1 ssn
        {
            emp1.printData();//print data
            fio.seekg(pos);
            fio.write((char*)&emp1, sizeof(emp1));
            return true;//and return true is found
        }
    }
    return false;//return false if not found in the list
}
bool searchbyID(fstream& fio, int id)//search by Employee id
{
    //search record in file
    int pos;
    fio.seekg(0);
    while (!fio.eof())
    {
        pos = fio.tellg();//get positon of cursur
        fio.read((char*)&emp1, sizeof(emp1));//read record from file
        if (emp1.getID() == id)//campare id with emp1 id
        {
            emp1.printData();//print founded record
            fio.seekg(pos);
            fio.write((char*)&emp1, sizeof(emp1));
            return true;//and return true is found
        }
    }
    return false;
}
bool deleteRecord(fstream& fio, char ssn[])
{
    //search record in file
    int pos;
    fio.seekg(0);
    while (!fio.eof())
    {
        pos = fio.tellg();
        fio.read((char*)&emp1, sizeof(emp1));//read record from file
        if (strncmp(emp1.getSSN(), ssn, 2) == 0)
        {
            emp1.printData();//print founded record          
            fio.seekg(pos);
            fio.write((char*)&emp1, sizeof(emp1)) << "";
            return true;//and return true is deleded
        }
    }
    return false;
}
void display(fstream& fio)
{
    fio.seekg(0);
    cout << "Now the file contains:\n";
    while (true)
    {
        fio.read((char*)&emp, sizeof(emp));//read record from file to emp
        if (fio.eof())
            break;
        emp.printData();//print data of each employee
    }
}