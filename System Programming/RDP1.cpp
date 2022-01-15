#include<bits/stdc++.h>

using namespace std;

/*
Grammar: E --> i Et
Et --> + i Et | e
(e is epsilon)
*/


void Et();
void E();
void match(char i);
char* l;
int main()
{
	char s[100];
	cout<<"\nEnter input ";
    scanf("%s",s);
	l=&s[0];
    // E is a start symbol.
    E();
  
    // if lookahead = $, it represents the end of the string
    
    if (*l == '$')
        printf("Parsing Successful");
    else
        printf("Parsing unsuccessful");
}
  
// Definition of E, as per the given production
void E()
{
    if (*l == 'i') {
        match('i');
        Et();
    }
}
  
// Definition of Et as per the given production
void Et()   
{
    if (*l == '+') {
		
        match('+');

        match('i');

        Et();
    }
    else
    { 
		return;
	
	}
}
  
// Match function
void match(char t)
{
    if (*l == t) {
        *l++;
    }
    else
    { 
		printf("Error");
		exit(0);
	
	}
}

