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

}emp1, emp; //Employee Management system using C++ program uses EmpID 
            //as unique identifier (i.e. primary key) to recognize employee.


void addRecord(fstream& file, int count);
bool searchbyID(fstream& file, int id);
bool searchbySSN(fstream& file, char ssn[]);
bool deleteRecord(fstream& file, char ssn[]);
void display(fstream& file);
int main()
{

    int count = 0;
   
    fstream file;
    file.open("employeeInfo.dat", ios::out); 
    file.close();
    char ans = 'y';
    int ch;
    bool flag = false;
    int ID;
    char ssn[11];
    while (!flag)
    {

        cout << "Select  \n\t1. Add record\n\t2. Delete Record\n\t3. Search Record by ID\n\t4. Display records\n\t5. Search Record by SSN (Enter in this format xxx-xxx-xxxx)\n\t6. Exit" << endl;

        cout << "\nEnter choice: ";
        cin >> ch;//read choice
        switch (ch)
        {
        case 1:
            file.open("employeeInfo.dat", ios::in | ios::out | ios::app);//add record into file
            addRecord(file, count);
            count++;//adding index
            file.close();
            break;
        case 2:
            file.open("employeeInfo.dat", ios::in | ios::out | ios::app);
            cout << "Enter a social security number for delete record (Enter in this format xxx-xxx-xxxx): ";
            cin >> ssn;   //read sn for delete record
            deleteRecord(file, ssn);
           
            break;
        case 3:
            file.open("employeeInfo.dat", ios::in | ios::out | ios::app);
            cout << "Enter a employee ID for searching: ";
            cin >> ID;//read employee id for search   record in file
            if (searchbyID(file, ID) == false)
            {
                cout << "\nRecord not found in the file..!!\n";
                cout << "Press any key to exit...\n";
                exit(2);
            }
            file.close();
            break;
        case 5:
            file.open("employeeInfo.dat", ios::in | ios::out | ios::app);
            cout << "Enter a social security number (Enter in this format xxx-xxx-xxxx): ";
            cin >> ssn;//read social security number for search   record in file
            if (searchbySSN(file, ssn) == false)
            {
                cout << "\nRecord not found in the file..!!\n";
                cout << "Press any key to exit...\n";
                exit(2);
            }
            file.close();
            break;
        case 4:
            file.open("employeeInfo.dat", ios::in | ios::out | ios::app);
            display(file);//display emlpoyees information      
            file.close();
            break;
        case 6:
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
        pos = fio.tellg();//get positon of cursor
        fio.read((char*)&emp1, sizeof(emp1));//read record from file
        if (strncmp(emp1.getSSN(), ssn, 3) == 0)//compare ssn with emp1 ssn
        {
            emp1.printData();//print data
            fio.seekg(pos);
            fio.write((char*)&emp1, sizeof(emp1));
            return true;//and return true is found
        }
    }
    return false;//return false if not found in the list
}
bool searchbyID(fstream& file, int id)//search by Employee id
{
    //search record in file
    int pos;
    file.seekg(0);
    while (!file.eof())
    {
        pos = file.tellg();//get positon of cursur
        file.read((char*)&emp1, sizeof(emp1));//read record from file
        if (emp1.getID() == id)//campare id with emp1 id
        {
            emp1.printData();//print founded record
            file.seekg(pos);
            file.write((char*)&emp1, sizeof(emp1));
            return true;//and return true is found
        }
    }
    return false;
}
bool deleteRecord(fstream& file, char ssn[])                
{
    

    int pos, flag = 0;

    ofstream ofs;
    ofs.open("temp.dat", ios::out | ios::binary);

    while (!file.eof()) {

        file.read((char*)&emp1, sizeof(emp1));

        // if(ifs)checks the buffer record in the file
        if (file) {

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
    file.close();

    // delete the old file
    remove("employeeInfo.dat");

    // rename new file to the older file
    rename("temp.dat", "employeeInfo.dat");

    if (flag == 1)
        cout << "\nrecord successfully deleted \n";
    else
        cout << "\nrecord not found \n";

}


void display(fstream& file)
{
    file.seekg(0);
    cout << "Now the file contains:\n";
    file.read((char*)&emp, sizeof(emp));
    while (!file.eof())
    {


        emp.printData();//print data of each employee
        file.read((char*)&emp, sizeof(emp));
    }
}