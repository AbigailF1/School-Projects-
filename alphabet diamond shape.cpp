#include <iostream>
#include<cmath>

using namespace std;
int main() {
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            int column =  7 - abs(7 - j);
            int row =  7 - abs(7 - i);
            if (column + row <= 7)
            {
                cout<<char(column+ 65)<<" ";
            }
            else
            {
                cout<<"  ";
            }
        }
        cout<<endl;
        
    }
    return 0;
}  
