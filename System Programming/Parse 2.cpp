#include<bits/stdc++.h>

#include<fstream>
using namespace std;
struct Icval{

    int lc=0;
    string opcode="";
    string opr2="";
    int opr1=0;
};

Icval ic_lines[50];
unordered_map<string,string>mp1;
vector<pair<string,int>>symtable;
vector<pair<string,int>>ltable;
vector<int>ptable;
vector<string>operator1={"AREG","BREG","CREG","DREG","LT","GT"}; 


void locationCounter(int j,int size){
    ic_lines[j].lc=ic_lines[j-1].lc+size;
}
int Index(string value,vector<pair<string,int>>table){
    for(int i=0;i<table.size();i++)
    {
        if(table[i].first==value)
            return i+1;
    }

    return 0;
}
int Opcode(string s2,int j){
    int pos1=s2.find(" ");
    if(s2.substr(0,pos1)=="LTORG"){
        ptable.push_back(1);
        for(auto it1=ltable.begin();it1!=ltable.end();it1++)
            {
                it1->second=distance(ltable.begin(),it1)+ic_lines[j].lc;
            }
        ic_lines[j].opcode=s2.substr(pos1+6,3)+','+s2.substr(pos1,3);
        return ltable.size();
    }else if(s2.substr(0,pos1)=="EQU"){

        if(Index("EQU",symtable)){
                                
            symtable[Index("EQU",symtable)-1].second=symtable[Index(ic_lines[j].opr2,symtable)-1].second;
        }else{
            symtable.push_back(make_pair("EQU",ic_lines[j].lc));
        }

    }
    ic_lines[j].opcode=s2.substr(pos1+6,3)+','+s2.substr(pos1,3);

    return stoi(s2.substr(pos1+3,3));
}

void Operator2(char* s,int j){
    string s3(s);
    if(isdigit(*s)){        //check if constant
        ic_lines[j].opr2="C,"+s3;
                    
        }else if(isupper(*s)){      //check if Capital
                    
            if(!Index(s3,symtable)){
                symtable.push_back(make_pair(s3,-1));
                }
                ic_lines[j].opr2="S,"+to_string(Index(s3,symtable));
                
            }else{      //else it is literal
                    
                        if(!Index(s3,ltable)){
                            ltable.push_back(make_pair(s3,-1));
                        }
                        ic_lines[j].opr2="L,"+to_string(Index(s3,ltable));
                        
                    
                }
    if(j==0)
    {
        ic_lines[j].lc=stoi(s);
    }
}

void printIc(int j){
    cout<<"\n-------------------------------------------";
    cout<<"\nLC\tType-Code\tOp1\tOp2\n";
    for(int i=0;i<j;i++)
 
    {
       cout<<ic_lines[i].lc<<"\t"<<ic_lines[i].opcode<<"\t\t"<<ic_lines[i].opr1 <<"\t"<<ic_lines[i].opr2<<"\n";
    }
    cout<<"\n--------------------------------------------";
}

void printSym(){
    cout<<"\n---SYMBOL TABLE---\n";
    cout<<"Symbol\t\tAddress\n";
    for(auto it=symtable.begin();it!=symtable.end();it++)
    {   
        cout<<it->first<<"\t\t"<<it->second<<"\n";
    }
}

void printLt(int j){
    int i=0;
    cout<<"\n---LITERAL TABLE---\n";
    cout<<"Literal\t\tAddress\n";
    for(auto it=ltable.begin();it!=ltable.end();it++)
    {   if(it->second==-1)
        {   it->second=ic_lines[j-1].lc+i; 
            if(i==0)
                ptable.push_back(Index(it->first,ltable)); 
            i++;
            
        }   //if literal address unassigned  
        cout<<it->first<<"\t\t"<<it->second<<"\n";
    }
}


int Parse2(string s){
    if(s[0] == 'L'){
        // cout<<s<<"\n";
        return ltable[stoi(s.substr(2))-1].second;
    }else if(s[0] == 'S'){
        return symtable[stoi(s.substr(2))-1].second;
    }
    
    return 0;
}
void printP2(int j){
    cout<<"\n-------------------------------------------";
    cout<<"\nLC\tOpcode\tOp1\tMemoryAddress\n";
    for(int i=0;i<j;i++)
    {
        cout<<ic_lines[i].lc<<"\t";

        if(ic_lines[i].opcode.substr(0,2)==" A"){
           
            if(ic_lines[i].opcode.substr(4,5)==" 03"){
                cout<<"00\t00\t"<<ltable[0].first[1]<<"\n";
                for(int k=1;k<ic_lines[i+1].lc-ic_lines[i].lc;k++){
                    cout<<ic_lines[i].lc+k<<"\t00\t00\t"<<ltable[k].first[1]<<"\n";
                }
                
            }else{
                cout<<"00\t00\t00\n";
            }
            
        }else{
            cout<<ic_lines[i].opcode.substr(4)<<"\t"<<ic_lines[i].opr1<<"\t"<<Parse2(ic_lines[i].opr2)<<"\n";
        }
        
    }

}

void printPool(){
    cout<<"\n---POOL TABLE---\n";
    cout<<"Index\t\tLtable start\n";
    for(int i=0;i<ptable.size();i++)
        cout<<i<<"\t\t"<<ptable[i]<<"\n";
}

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


    file1.open("HashTable.txt");
    if(file1.fail())
    {
        cout<<"Error!";
    }else{
	    cout<<"\nTable file-\n";
    

        while(getline(file1,line1)) 
        {
            cout<<line1<<"\n";
            int pos1=line1.find(" ");
        

            mp1.insert(make_pair(line1.substr(0,pos1),line1));      //mapping to respective information values in mp1 map.
            
        }

        file1.close();
        cout<<"\nHashed values-\n";
        for(auto it=mp1.begin();it!=mp1.end();it++)
        {   
            cout<<it->first<<"-"<<it->second<<"\n";
        }
    }

    file1.open("input2.txt");
    if(file1.fail())
    {
        cout<<"Error!";
    }else{
    
    string s2;

        while(getline(file1,line1))  //readong input file to generate intermediate code
    	{	char* data=new char(line1.length());
            // int i=0;
            strcpy(data,line1.c_str());
            for(int i=0;i<4;i++){
                char* s=strtok_r(data," ",&data);
                if(i==0){
                    if(j==0){
                        continue;
                    }else{
                        locationCounter(j,size);
                    }
                    if(isupper(*s)){
                            if(Index(s,symtable)){
                                
                                symtable[Index(s,symtable)-1].second=ic_lines[j].lc;
                            }else{
                                symtable.push_back(make_pair(s,ic_lines[j].lc));
                            }
                        }
                }else if(i==1){
                    auto it=mp1.find(s);

                    if(it!=mp1.end()){
                        size=Opcode(it->second,j);

                    }else{
                        cout<<"\nInvalid opcode";
                    }
                }else if(i==2){
                    if(*s!='-')
                    {
                        ic_lines[j].opr1=(find(operator1.begin(),operator1.end(),s)-operator1.begin())+1;   //finding registers or conditional code index value from vector
                    }
                }else{
                    if(*s!='-'){
                    Operator2(s,j);
                    }
                }

            }
            j++;
    }
    }

    printIc(j);
    printSym();
    printLt(j);
    printPool();
    printP2(j);
    
}


/**
 * 
 * Input file-
- START - 2000       
- MOVER AREG '2'   
- MOVER BREG '5'  
- LTORG - -
- MOVER AREG A    
- ADD AREG X  
- DIV BREG A 
- SUB DREG A
- STOP - -
A DC - ‘10’
X DS - 100
- END - -

Table file-
ADD 01 02 IS 2 
SUB 02 02 IS 2
MULT 03 02 IS 2 
DIV 08 02 IS 2 
BC 07 02 IS 2 
READ 09 01 IS 1 
PRINT 10 01 IS 1 
START 01 00 AD 0
ORIGIN 02 00 AD 1 
LTORG 03 00 AD 0 
END 04 00 AD 0
EQU 05 00 AD 1 
STOP 00 01 IS 0 
MOVER 04 03 IS 2 
MOVEM 05 04 IS 2 
DC 01 01 DL 1 
DS 02 01 DL 1 

Hashed values-
DS-DS 02 01 DL 1 
DC-DC 01 01 DL 1 
MOVEM-MOVEM 05 04 IS 2 
MOVER-MOVER 04 03 IS 2 
ADD-ADD 01 02 IS 2 
MULT-MULT 03 02 IS 2 
END-END 04 00 AD 0
DIV-DIV 08 02 IS 2 
BC-BC 07 02 IS 2 
STOP-STOP 00 01 IS 0 
READ-READ 09 01 IS 1 
PRINT-PRINT 10 01 IS 1 
SUB-SUB 02 02 IS 2
START-START 01 00 AD 0
ORIGIN-ORIGIN 02 00 AD 1 
EQU-EQU 05 00 AD 1 
LTORG-LTORG 03 00 AD 0 

-------------------------------------------
LC      Type-Code       Op1     Op2
2000     AD, 01         0       C,2000
2000     IS, 04         1       L,1
2003     IS, 04         2       L,2
2006     AD, 03         0
2008     IS, 04         1       S,1
2011     IS, 01         1       S,2
2013     IS, 08         2       S,1
2015     IS, 02         4       S,1
2017     IS, 00         0
2018     DL, 01         0       L,3
2019     DL, 02         0       C,100
2020     AD, 04         0

--------------------------------------------
---SYMBOL TABLE---
Symbol          Address
A               2018
X               2019

---LITERAL TABLE---
Literal         Address
'2'             2006
'5'             2007
‘10’            2020

---POOL TABLE---
Index           Ltable start
0               1
1               3

-------------------------------------------
LC      Opcode  Op1     MemoryAddress
2000    00      00      00
2000     04     1       2006
2003     04     2       2007
2006    00      00      2
2007    00      00      5
2008     04     1       2018
2011     01     1       2019
2013     08     2       2018
2015     02     4       2018
2017     00     0       0
2018     01     0       2020
2019     02     0       0
2020    00      00      00
 * **/