#include<bits/stdc++.h>

using namespace std;



void terminalB(char* c){            
    
    if(*c=='b'){
        *c++;
        terminalB(c);
        if(*c=='b') {
            *c++;
                
        }
        else{
            cout<<"\nIncorrect!";
            exit(0);
        }

    }
    
    
    else{
        cout<<"\nCorrect!";
        exit(0);
    }

}


void terminalA(char* c){
    
    if(*c=='a'){
        *c++;
        terminalA(c);
        if(*c=='a') {
            *c++;
    
        }

        else{
            cout<<"\nIncorrect!\n";
            exit(0);
        }
    }

    else if(*c=='b'){
        *c++;
        terminalB(c);
        if(*c=='b') {
            *c++;
            
        }
        else{
            cout<<"\nIncorrect!\n";
            exit(0);
        }
    }

    else{
        cout<<"\nIncorrect!\n";
        exit(0);
    }
    
}



int main(){

    char s[100];
    
    cout<<"\nEnter input ";
    scanf("%s",s);
    
    terminalA(s);
    cout<<"\nCorrect!\n";
   

    
    return 0;


}

/*

ellika@ellika-HP-Laptop-15s-du1xxx:~/sl5/sp$ g++ RDP.cpp
ellika@ellika-HP-Laptop-15s-du1xxx:~/sl5/sp$ ./a.out

Enter input aabbaa

Correct!ellika@ellika-HP-Laptop-15s-du1xxx:~/sl5/sp$ ./a.out

Enter input bb

Correct!ellika@ellika-HP-Laptop-15s-du1xxx:~/sl5/sp$ ./a.out

Enter input aa

Incorrect!
ellika@ellika-HP-Laptop-15s-du1xxx:~/sl5/sp$ ./a.out

Enter input aaabbaaa

Correct!ellika@ellika-HP-Laptop-15s-du1xxx:~/sl5/sp$ ^C


*/