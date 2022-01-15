#include<bits/stdc++.h>

using namespace std;


vector<string>Keywords{"int","float","for","while","if","else","else if","do","char"};
vector<string>Functions{"main","scanf","printf","getch","putch"};
set<string>keyword;
set<string>terminal;
set<pair<string,string>>identifier;
set<pair<string,string>>literal;
vector<pair<string,pair<string,int>>>ust;
int main(){

    string line1;
    fstream file1;
    int j=0,size=0,i;
    file1.open("input2.txt");
    if(file1.fail())
    {
        cout<<"Error!";
    }else{
	cout<<"\nInput file-\n";
        while(getline(file1,line1)) //print contents of input file and table
        {
            cout<<line1<<"\n";
        }
    }
    file1.close();

    file1.open("input2.txt");
    if(file1.fail())
    {
        cout<<"Error!";
    }else{

        while(getline(file1,line1))  //readong input file to generate intermediate code
    	{	
            if(line1.empty()||line1[0]=='#'||line1[0]=='/*') continue;
            // char* data=new char(line1.length()+1);
            int it=0;
            char* data=(char*)malloc(line1.length()+1);
            strcpy(data,line1.c_str());
            
            char* s=strtok_r(data," ",&data);
            while(s!=NULL){
                string ty;int i;
                string check=s;
                // ty=string(s);
                if(isdigit(*(s))){
                    literal.insert(make_pair(s,"numeric constant"));
                    ty="LT";
                    i=literal.size()-1;
                }else if(find(Keywords.begin(),Keywords.end(),s)!=Keywords.end()){
                    
                    keyword.insert(s);
                    ty="KEY";
                    i=keyword.size()-1;
                
                }else if(find(Functions.begin(),Functions.end(),s)!=Functions.end()){
                   
                    identifier.insert(make_pair(s,"function name"));
                    ty="IDN";
                    i=identifier.size()-1;
                    
                }else if(isalpha(*(s))){
                    
                    identifier.insert(make_pair(s,"varibale"));
                    ty="IDN";
                    i=identifier.size()-1;
                   
                    
                }else if(*s=='"'){
                    literal.insert(make_pair(s,"sting constant"));
                    ty="LT";
                    i=literal.size()-1;
                }else{
                    terminal.insert(s);
                    ty="TRM";
                    i=terminal.size()-1;
                }
                
                if(find_if(ust.begin(),ust.end(),[&check](pair<string,pair<string,int>>&el){return el.first==check;})==ust.end()) ust.push_back(make_pair(check,make_pair(ty,i)));
                
                s=strtok_r(NULL," ",&data);
            }
            
        
        }


    }

    cout<<"\n----Terminals----\n";
    for(auto it:terminal){
        cout<<it<<"\n";
    }
    cout<<"\n----Keywords----\n";
    for(auto it:keyword){
        cout<<it<<"\n";
    }
    cout<<"\n----Literals----\nIdentifier\tAttribute\n";
    for(auto it:literal){
        cout<<it.first<<"\t\t"<<it.second<<"\n";
    }
    cout<<"\n----Identifiers----\nIdentifier\tAttribute\n";
    for(auto it:identifier){
        cout<<it.first<<"\t\t"<<it.second<<"\n";
    }
    cout<<"\n----UST----\nSymbol\ttype\tid\n";
    for(auto it:ust){
        cout<<it.first<<"\t"<<it.second.first<<"\t"<<it.second.second<<"\n";
    }

    return 0;

}


/**
 * 
 * Input file-
#include<stdio.h>


main ( )
{
    int   i , no , sum , max ;
    sum = 0 ; max = 32767 ;
    for ( i = 0 ; i < 10 ; i ++ )
    {       
        scanf ( “%d” , & no ) ; 
        sum = sum + no ;
        if ( max > no ) max = no ;
    }
    printf ( “sum = % d  max = % d” , sum , max ) ;
    getch ( ) ;
} 

----Terminals----
%
&
(
)
+
++
,
;
<
=
>
{
}

----Keywords----
for
if
int

----Literals----
Identifier      Attribute
0               numeric constant
10              numeric constant
32767           numeric constant
"%d”            string  constant
“sum            string constant
----Identifiers----
Identifier      Attribute
getch           function name
i               varibale
main            function name
max             varibale
no              varibale
printf          function name
scanf           function name
sum             varibale

----UST----
Symbol  type    id
main    IDN     0
(       TRM     0
)       TRM     1
{       TRM     2
int     KEY     0
i       IDN     1
,       TRM     3
no      IDN     2
sum     IDN     3
max     IDN     4
;       TRM     4
=       TRM     5
0       LT      0
32767   LT      1
for     KEY     1
<       TRM     6
10      LT      2
++      TRM     7
scanf   IDN     5
“%d”    LT      4
&       TRM     9
+       TRM     10
if      KEY     2
>       TRM     11
}       TRM     12
printf  IDN     6
“sum    LT      5
%       TRM     14
getch   IDN     8
 * 
 * 
 * 
 * **/