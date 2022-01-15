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
unordered_map<string,int>symtable;
unordered_map<string,int>ltable;
vector<string>operator1={"AREG","BREG","CREG","DREG","LT","GT"}; 


void locationCounter(int j,int size){
    ic_lines[j].lc=ic_lines[j-1].lc+size;
}

int Opcode(string s2,int j){
    int pos1=s2.find(" ");
    if(s2.substr(0,pos1)=="LTORG"){
        for(auto it1=ltable.begin();it1!=ltable.end();it1++)
            {
                it1->second=distance(ltable.begin(),it1)+ic_lines[j].lc;
            }
        ic_lines[j].opcode=s2.substr(pos1+6,3)+','+s2.substr(pos1,3);
        return ltable.size();
    }
    ic_lines[j].opcode=s2.substr(pos1+6,3)+','+s2.substr(pos1,3);

    return stoi(s2.substr(pos1+3,3));
}

void Operator2(char* s,int j){
    string s3(s);
    if(isdigit(*s)){        //check if constant
        ic_lines[j].opr2="C,"+s3;
                    
        }else if(isupper(*s)){      //check if Capital
                    
            if(symtable.find(s3)==symtable.end()){
                symtable.insert(make_pair(s3,-1));
                }
                ic_lines[j].opr2="S,"+to_string(distance(symtable.begin(),symtable.find(s3)));
                
            }else{      //else it is literal
                    if(*s!='-'){
                        if(ltable.find(s3)==ltable.end()){
                            ltable.insert(make_pair(s3,-1));
                        }
                        ic_lines[j].opr2="L,"+to_string(distance(ltable.begin(),ltable.find(s3)));
                        
                    }
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

void printSym(int j){
    cout<<"\n---SYMBOL TABLE---\n";
    cout<<"Symbol\t\tAddress\n";
    for(auto it=symtable.begin();it!=symtable.end();it++)
    {   
        cout<<it->first<<"\t\t"<<it->second<<"\n";
    }
}

void printLt(int j){
    cout<<"\n---LITERAL TABLE---\n";
    cout<<"Literal\t\tAddress\n";
    for(auto it=ltable.begin();it!=ltable.end();it++)
    {   if(it->second==-1)
            it->second=ic_lines[j-1].lc+(distance(ltable.begin(),it));     //if literal address unassigned  
        cout<<it->first<<"\t\t"<<it->second<<"\n";
    }
}


int Parse2(string s){
    if(s[0] == 'L'){
        for(auto it:ltable){

           
        }
        
    }else if(s[0] == 'S'){
        for(auto it:symtable){

            if(s.substr(3)== it.first){
                return it.second;
            }
        }
    }

    return 0;    
}
void printP2(int j){
    cout<<"\n-------------------------------------------";
    cout<<"\nLC\tType-Code\tOp1\tOp2\n";
    for(int i=0;i<j;i++)
    {
        cout<<ic_lines[i].lc<<"\t\t+"<<ic_lines[i].opcode.substr(4)<<"\t"<<ic_lines[i].opr1<<"\t"<<Parse2(ic_lines[i].opr2)<<"\n";
    }

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
                            if(symtable.find(s)!=symtable.end()){
                                symtable.find(s)->second=ic_lines[j].lc;
                            }else{
                                symtable.insert(make_pair(s,ic_lines[j].lc));
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
                    
                    Operator2(s,j);
                }

            }
            j++;
    }
    }

    printIc(j);
    printSym(j);
    printLt(j);
    printP2(j);
}