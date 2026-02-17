#include<iostream>
#include<fstream>
#include "user.h"
using namespace std;
void User::registerUser() {
    ofstream fout("users.txt", ios::app);

    //From now we are taking user input for registration 
  cout<<"If you are a new user ,please register yourself by providing the following details\n";
    cout<<"-------------"<<"Enter User Details"<<"-------------"<<endl;
    cin.ignore(); 
    cout<<"Enter user name:";
    cin>>name;
    cout<<"Enter user ID :";
    cin>>id;
    cout<<"Enter user password :";
    cin>>password;
    cout<<"Enter user phone number :";
    cin>>phone;
    cout<<"Enter user email :";
    cin>>email;
    //Now I'm storing user details in a text file named users.txt
 fout<<name<<" "<<id<<" "<<password<<" "<<phone<<" "<<email<<endl;
 fout.close();
 }
 void User::searchUser(){

int choice,searchID;
string searchName;
ifstream fin("users.txt");
cout<<"-------Select any one of the options below------";
cout<<"1.Search by Name \n";
cout<<"2.Search by ID \n";
cout<<"Enter your choice :\n";
cin>>choice;
   switch(choice)
   {
    case 1:
      cout<<"Enter the name to be searched :\n";
      cin>>searchName;
      bool foundinfo=false;
      while(fin>>name>>id>>password>>phone>>email)
      { if (name==searchName)
        {
            cout<<"User is found.The information of this user is provided below:\n";
            cout<<"Name :"<<name<<endl;
            cout<<"ID :"<<id<<endl;
            cout<<"E-mail :"<<email<<endl;
            cout<<"Phone :"<<phone<<endl;
            foundinfo=true;
        } 
     }
    if(!foundinfo) {
            cout<<"Sorry! The user doesn't exist in this database \n";
        }
    fin.close();
    break;

    case 2:
    cout<<"Enter the id to be searched :\n";
    cin>>searchID;
     bool foundinfo=false;
      while(fin>>name>>id>>password>>phone>>email)
      { if (id==searchID)
        {
            cout<<"User is found.The information of this user is provided below:\n";
            cout<<"Name :"<<name<<endl;
            cout<<"ID :"<<id<<endl;
            cout<<"E-mail :"<<email<<endl;
            cout<<"Phone :"<<phone<<endl;
            foundinfo=true;
        } 
     }
    if(!foundinfo) {
            cout<<"Sorry! The user doesn't exist in this database \n";
        }
    fin.close();

    break;
   }
}
  
void User::AdminMenu()
    { int choice;
        cout<<"---------------------"<<"Welcome Admin"<<"---------------------";
 cout<<"Do you want to:\n";
 cout<<"1. View all users \n";
 cout<<"2. Search user \n";
 cout<<"3. View Drivers \n";
 cout<<"4. Manage Vehicles \n";
 cout<<"5. Logout \n";
cout<<"Enter your choice :";
cin>>choice;

    }