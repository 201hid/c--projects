//
//  main.cpp
//  projectbank
//
//  Created by TOWHIDUL HASSAN on 25/1/2024.
//
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<map>
using namespace std;



class Account
{
    
private:
    static int nextaccountnumber ;
    
    int accountnumber ;
    string fname;
    string lname;
    float balance;
    
    
public:
    
    Account(string fname, string lname, float balance);

    
    
    
    void deposit(float depositamount);

    Account(){};
    void withdrawal(float withdrawalamount);
    string getfirstname(){return fname;}
    string getlastname(){return lname;}
    float getbalance(){return balance;}
    int getAccNo(){return accountnumber;}
    
    friend ofstream & operator<<(ofstream &ofs,Account &acc);
    friend ifstream & operator>>(ifstream &ifs,Account &acc);
    friend ostream & operator<<(ostream &os,Account &acc);

    
    ~Account()
    {
        cout<<"destructor called";
    }
    
    
};


    class bank{
        
    map<int,Account> accounts;
        
    public:
        
        bank();
        Account create_account(string first_name, string last_name, float balance);
        Account Withdrawal(int accountnumber, float withdrawal_ammount);
        Account deposit(int accountnumber, float deposit_ammount);
        Account balanceenquiry(int accountnumber);
        void updatememory();

        void showallaccount();
        void closeaccount(int accountnumber);

};


int Account::nextaccountnumber=0;

int main() {
    bank b;
    Account a;
    int choice;
    int accountnumber;



    do
    {
        
        cout<<"\n\tSelect one option below ";
        cout<<"\n\t1 Open an Account";
        cout<<"\n\t2 Balance Enquiry";
        cout<<"\n\t3 Deposit";
        cout<<"\n\t4 Withdrawal";
        cout<<"\n\t5 Close an Account";
        cout<<"\n\t6 Show All Accounts";
        cout<<"\n\t7 Quit";
        cout<<"\nEnter your choice: ";

        cin>> choice;
        switch(choice)
            
        {
                
            case 1:
            {
                string fname;
                string lname;
                float balance;
                cout<<"enter your first name";
                cin>>fname;
                cout<<"enter your last name";
                cin>> lname;
                cout<<"enter your intial balance ";
                cin>> balance;
                
                a = b.create_account(fname, lname, balance);
                cout<<a;
                break;
            }
                

            case 2:
            {
                
                cout<<"enter your account number";
                cin >> accountnumber;
                a = b.balanceenquiry(accountnumber);
                cout<<a.getbalance();
                
                
                
                break;
            }

            case 3:
            {
                
                cout<<"enter your account number";
                cin >> accountnumber;
                cout<<"enter your deposit amount in aud";
                float deposit_ammount;
                cin>>deposit_ammount;
                a = b.deposit(accountnumber,deposit_ammount);
                cout<< a;
                
                break;
            }

            case 4:
            {
                
                cout<<"enter your account number";
                cin >> accountnumber;
                cout<<"enter your deposit amount in aud";
                float withdrawal_ammount;
                cin>>withdrawal_ammount;
                a = b.Withdrawal(accountnumber,withdrawal_ammount);
                cout<< a;
                break;
            }
            case 5:
            {
                
                cout<<"enter the  account number you want to close";
                cin>>accountnumber;
                b.closeaccount(accountnumber);
                cout<<accountnumber<<" successfully closed from the bank";
                break;
            }

            case 6:

                b.showallaccount();
                break;

            case 7:
                break;
  
            default:
                cout<<"enter valid input";
                exit(0);

        }
    }while (choice !=7);
    
    return 0;
}





Account:: Account(string fname, string lname, float balance)
{
    nextaccountnumber++;
    
    accountnumber = nextaccountnumber;
    this -> fname = fname;
    this -> lname = lname;
    this -> balance = balance;
            
}



void Account::deposit(float depositamount)
{
    balance = balance + depositamount;
}

void Account:: withdrawal(float withdrawalamount)
{
    balance = balance - withdrawalamount;
}

ofstream & operator<<(ofstream &ofs,Account &acc)
{
 ofs<<acc.accountnumber<<endl;
 ofs<<acc.fname<<endl;
 ofs<<acc.lname<<endl;
 ofs<<acc.balance<<endl;
 return ofs;
}
ifstream & operator>>(ifstream &ifs,Account &acc)
{
 ifs>>acc.accountnumber;
 ifs>>acc.fname;
 ifs>>acc.lname;
 ifs>>acc.balance;
 return ifs;

}
ostream & operator<<(ostream &os,Account &acc)
{
 os<<"First Name:"<<acc.getfirstname()<<endl;
 os<<"Last Name:"<<acc.getlastname()<<endl;
 os<<"Account Number:"<<acc.getAccNo()<<endl;
 os<<"Balance:"<<acc.getbalance()<<endl;
 return os;
}

//Account
bank::bank()//reading from text to initialize bank
{
    Account account;
    ifstream ifs("accounts.txt");
    
    if(!ifs)
    {
        cout<<"not able to open file";
        
    }
    else
    {
        while (!ifs.eof())
        {
            ifs>>account;
            accounts.insert(pair<int, Account>(account.getAccNo(), account));
        }
    }
    
    
}
Account bank::  create_account(string first_name, string last_name, float balance)
{
    Account account(first_name, last_name, balance);
    ofstream outfile("accounts.txt", ios::app);
    accounts.insert(pair<int,Account >(account.getAccNo(), account));
    outfile << account;
    
    outfile.close();
    
    return account;
}

Account bank:: Withdrawal(int accountnumber, float withdrawal_ammount)
{
    
    map<int, Account> ::iterator itr=accounts.find(accountnumber);
    itr  -> second.withdrawal(withdrawal_ammount);
    updatememory();

    return itr -> second;

}
Account bank :: deposit(int accountnumber, float deposit_ammount)
{
    map<int, Account>:: iterator itr= accounts.find(accountnumber);
    itr -> second.deposit(deposit_ammount);
    updatememory();

    return itr -> second;
    
}

Account bank:: balanceenquiry(int accountnumber)
{
    map<int, Account>:: iterator itr= accounts.find(accountnumber);
    
    return itr -> second;
}

void bank::showallaccount()
{
    map< int , Account> :: iterator itr;
    for (itr =accounts.begin(); itr != accounts.end(); itr++)
    {
        cout<< itr -> first<< itr -> second;
    }
}

void bank::updatememory()
{
    map< int, Account>:: iterator itr;
    ofstream outfile("accounts.txt", ios::trunc);

    for(itr = accounts.begin(); itr != accounts.end(); itr++)
    {
        outfile << itr -> second;
        
    }
    outfile.close();

}

void bank::closeaccount(int accountnumber)
{
    map<int ,Account>::iterator itr=accounts.find(accountnumber);
    
    cout<< itr -> first<< itr -> second;

    accounts.erase(accountnumber);
    
    updatememory();
    
}
