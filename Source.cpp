//Employee Data Base
// Finished on 5/10 
#pragma warning(disable :4716)
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
    float salary;           //Doesn't allow for commas to be entered when giving salary for example
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
            cin >> socialSecurityNumber; // Enter in format xxx-xxx-xxxx
        } while (strchr(socialSecurityNumber, '-') == NULL);

        cout << "Salary (no comma needed): ";
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
    //fstream fio("employeeInfo.dat", ios::in | ios::out | ios::app);
    fstream fio;
    fio.open("employeeInfo.dat", ios::out); //this is only to create a new file, if you want append operation remove this
    fio.close();// this is for same reason as above
    char ans = 'y';
    int ch;
    bool flag = false;
    int id;
    char ssn[11];
    while (!flag)
    {

        cout << "Select  1. Add record\n\t2. Delete Record\n\t3. Search Record by ID\n\t4. Display records\n\t5. Exit\n\t6. Search Record by SSN (Enter in this format xxx-xxx-xxxx)" << endl;

        cout << "\nEnter choice: ";
        cin >> ch;//read choice
        switch (ch)
        {
        case 1:
            fio.open("employeeInfo.dat", ios::in | ios::out | ios::app);//add record into file
            addRecord(fio, count);
            count++;//adding index
            fio.close();
            break;
        case 2:
            fio.open("employeeInfo.dat", ios::in | ios::out | ios::app);
            cout << "Enter a social security number for delete record (Enter in this format xxx-xxx-xxxx): ";
            cin >> ssn;   //read sn for delete record
            deleteRecord(fio, ssn);
            //if (deleteRecord(fio, ssn) == false)
            //{
               // cout << "\nRecord not found in the file..!!\n";
              //  cout << "Press any key to exit...\n";
             //   exit(2);
            //}
            //fio.close();
            break;
        case 3:
            fio.open("employeeInfo.dat", ios::in | ios::out | ios::app);
            cout << "Enter a employee ID for searching: ";
            cin >> id;//read employee id for search   record in file
            if (searchbyID(fio, id) == false)
            {
                cout << "\nRecord not found in the file..!!\n";
                cout << "Press any key to exit...\n";
                exit(2);
            }
            fio.close();
            break;
        case 6:
            fio.open("employeeInfo.dat", ios::in | ios::out | ios::app);
            cout << "Enter a social security number (Enter in this format xxx-xxx-xxxx): ";
            cin >> ssn;//read social security number for search   record in file
            if (searchbySSN(fio, ssn) == false)
            {
                cout << "\nRecord not found in the file..!!\n";
                cout << "Press any key to exit...\n";
                exit(2);
            }
            fio.close();
            break;
        case 4:
            fio.open("employeeInfo.dat", ios::in | ios::out | ios::app);
            display(fio);//display emlpoyees information        //this section is not working at all
            fio.close();
            break;
        case 5:
            flag = true;//set flag to true to exit
            break;
        default:
            cout << "Enter valid choice only." << endl;

        }
    }
    //fio.close();
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
    

    int pos, flag = 0;

    ofstream ofs;
    ofs.open("temp.dat", ios::out | ios::binary);

    while (!fio.eof()) {

        fio.read((char*)&emp1, sizeof(emp1));

        // if(ifs)checks the buffer record in the file
        if (fio) {

            // comparing the roll no with
            // roll no of record to be deleted
            if (strncmp(emp1.getSSN(), ssn, 2) == 0) {
                flag = 1;
                emp1.printData();//print founded record
                cout << "Employee record found" << endl;
            }
            else {
                ofs.write((char*)&emp1, sizeof(emp1));
            }
        }
    }

    ofs.close();
    fio.close();

    // delete the old file
    remove("employeeInfo.dat");

    // rename new file to the older file
    rename("temp.dat", "employeeInfo.dat");

    if (flag == 1)
        cout << "\nrecord successfully deleted \n";
    else
        cout << "\nrecord not found \n";

}


void display(fstream& fio)
{
    fio.seekg(0);
    cout << "Now the file contains:\n";
    fio.read((char*)&emp, sizeof(emp));
    while (!fio.eof())
    {
        //fio.read((char*)&emp, sizeof(emp));//read record from file to emp
        //if (fio.eof())
            //break;
        emp.printData();//print data of each employee
        fio.read((char*)&emp, sizeof(emp));
    }
}