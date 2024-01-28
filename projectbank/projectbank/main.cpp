//
//  main.cpp
//  projectbank
//
//  Created by TOWHIDUL HASSAN on 25/1/2024.
//

#include <iostream>
using namespace std;
#include<map>

class Account{
    
    int accountnumber;
    string fname;
    string lname;
    float balance;
    
    
public:
    
    Account(string fname, string lname, float balance)
    {
        this -> fname = fname;
        this -> lname = lname;
        this -> balance = balance;
                
    }
    
    
    
    float deposit(float depositamount)
    {
        balance = balance + depositamount;
        return balance;
    }
    
    float withdrawal(float withdrawalamount)
    {
        balance = balance - withdrawalamount;
        return balance;
    }
    
    ~Account()
    {
        cout<<"destructor called";
    }
    
    
    
    class bank{
        
        map<int, Account> account;
        
        
        bank()
        
        
        
        
        
        
        
        
        
    
    
    
    
    
    
    
};

int main() {
    
    ;

    }

}
