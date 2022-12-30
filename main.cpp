#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>

#include "calculator.h"

using namespace std;

int main()
{
    for( int c = 0; c < 13; c++ )
    {
        string eps;
        
        string inp;
        
        getline(cin, inp);
        
        for ( int i = 0; i < inp.size(); i++ ) //通过for循环来规范输入
        {
            if( inp[i] == ' ' )
                ;
            
            else if( inp[i] == '(' && ( inp[i-1] == ')' || type(inp[i-1]) == 0 ) )
            {
                eps.push_back('*');
                eps.push_back(inp[i]);
                i++;
                eps.push_back(inp[i]);
            }
            
            else
                eps.push_back(inp[i]);
        }
        
        if( calculate(eps) != " " && is_valid(eps) )
        {
            cout << inp << " = " << fixed << setprecision(2) << sTOd( calculate(eps) ) << endl;
        }
    }
    return 0;
}