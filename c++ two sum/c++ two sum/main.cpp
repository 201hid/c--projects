//
//  main.cpp
//  c++ two sum
//
//  Created by TOWHIDUL HASSAN on 30/1/2024.
//
using namespace std;
#include <iostream>

int main(int argc, const char * argv[]) {
    
    
    int a[5] = {1,2,3,4,5};
    int size = sizeof(a)/ sizeof(a[0]);

    
    for (int y = 0; y < size; y++)
    {
        for (int i = y+1; i < size; i++)
        {
            cout<<a[y];

            cout<<a[i]<<endl;
            
        }
        
    }

    
    
    std::cout << "Hello, World!\n";
    return 0;
}
