#include<iostream>
using namespace std;
#include<fstream>
#include<vector>

class product
{
private:
    string name;
    float price;
    int quantity;
    
public:
    product(){}
    
    product(string name, float price, int quantity)
    {
        this -> name = name;
        this -> price = price;
        this -> quantity =  quantity;
    }
    
    
    friend ofstream & operator<<(ofstream &ofs, product &s);
    friend ifstream & operator >>(ifstream &ifs, product &s);
    friend ostream & operator <<(ostream &os, product &s);
    
    

    

};
    ofstream & operator<<(ofstream &ofs, product &s)
    {
        ofs<<s.name<<" "<<s.price<<" "<<s.quantity<<endl;

        return ofs;
    }
    
    ifstream & operator >>(ifstream &ifs, product &s)
    {
        ifs>>s.name>>s.price>>s.quantity;

        
        return ifs;
    }

    ostream & operator <<(ostream &os, product &s)
    {
        os<<"Name "<<s.name<<endl;
        os<<"Roll "<<s.price<<endl;
        os<<"quantity "<<s.quantity<<endl;
        return os;
    }







int main()
{
    int i, pro_quantity;
    float pro_price;
    string pro_name;
    
    cout<<" how many product would you like to enter?";
    int pro_number;
    cin>> pro_number;

    
    vector<product *> prod;// use of *
//    product *list[pro_number];
    
    for(i=0; i<pro_number; i++)
    {
        cout<<"please enter the product"<<i+1<< "name";
        cin>> pro_name;
        cout<<"please enter the product"<<i+1<< "price";
        cin>> pro_price;
        cout<<"please enter the product"<<i+1<< "quantity";
        cin>> pro_quantity;
        
        prod.push_back(new product(pro_name, pro_price, pro_quantity));//use of new
        

        
        

    }
    for(auto itr = prod.begin(); itr != prod.end(); itr++)
    {

        ofstream file("input.txt", ios::app);
        file<< *itr;
    }

    
    for(i=0; i<pro_number; i++)
    {
        product pro;

        ifstream file("input.txt");
        file>> pro;
        cout<<pro;
    }


}
