//
//  main.cpp
//  projectbank
//
//  Created by TOWHIDUL HASSAN on 25/1/2024.
//

#include <iostream>
#include<fstream>
using namespace std;
#include<map>

class Account{
    
    static int nextaccountnumber;
    
    int accountnumber;
    string fname;
    string lname;
    float balance;
    
    
public:
    
    Account(string fname, string lname, float balance);

    
    
    
    void deposit(float depositamount);

    
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
        
        bank();
        Account create_account(string first_name, string last_name, float balance);
        Account Withdrawal(int accountnumber, float withdrawal_ammount);
        Account deposit(int accountnumber, float deposit_ammount);
        void showallaccount();
        void closeaccount(int accountnumber);
        

        
        
        
        
        
        
        
        
        
        
    
    
    
    
    
    
    
};

int main() {
    
    ;

    }





Account:: Account(string fname, string lname, float balance)
{
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


Account bank::  create_account(string first_name, string last_name, float balance)
{
    Account account(first_name, last_name, balance);
    ofstream outfile("my.text", ios::app);
    accounts.insert(pair<int,Account >(account.getAccNo(), account));
    outfile << account;
    
    outfile.close();
    
    return account;
    
    

}
