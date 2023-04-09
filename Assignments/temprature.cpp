#include <iostream>
#include <string>
using namespace std;

// Function to refactor the given number from index i
void refac(string num, int i){
    string above=num;
    string below=num;
    above[i]=above[i] + 1; // Increment the digit at index i in above
    below[i]=below[i] - 1; // Decrement the digit at index i in below

    // Set all digits after i to '0' in above and '9' in below
    for(int j=i+1;j<num.size();j++){
        above[j]='0';
        below[j]='9';
    }
    // Print the refactored numbers
    cout<<above<<" : "<<below<<endl;
}

int main(){
    string def_program = "This program takes a degree from 0 - 999 and returns the largest and smallest closest degrees respectfully when the number contains 1, 4 & 7 in its digits and the number itself if it doesnt contain these three digits"; 
    cout << def_program << "\n\n"; 
    string temp;
    cout<<"Enter temprature: ";
    cin>>temp; 

    // Check if the number is between 0 and 999
    if(stoi(temp)>999||stoi(temp)<0){
        cout<<"Invalid!! Enter a number between 0 and 999";
        return 0;
    }

    // Iterate over each digit in the input number
    for (int i=0;i<temp.length();i++){
        
            

        // Check if the character is not a digit
        if(int(temp[i])<int('0') || int(temp[i])>int('9')){
            cout<<"Enter a valid number.";
            break;
        }

        // Check if the digit is 1, 4, or 7
        if(temp[i]=='7'||temp[i]=='1'||temp[i]=='4'){
            refac(temp,i); // Call the refac function
            break;
        }

        // If all digits have been checked and no refactoring was done, print the original number
        if(i+1==temp.length())cout<<temp;
    }
    return 0;
}
