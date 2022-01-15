#include<bits/stdc++.h>

#include<fstream>
using namespace std;


int main()
{
    string line1;
    fstream file1,file3;
    long fileSize;
    char* buffer;
    FILE* file2=fopen("Hasheda.txt","w+");
    unordered_map<string,string>mp1;
    unordered_map<int,string>mp2;
    file1.open("HashTable.txt");
    if(file1.fail())
    {
        cout<<"Error!";
    }else{
	    cout<<"\nTable file-\n";
    int index=1;
	while(getline(file1,line1)) //print contents of input file and table
	{
		cout<<line1<<"\n";
        int pos1=line1.find(" ");
        int pos2=line1.length()-pos1;
        // cout<<pos1<<"\n";
        mp1.insert(make_pair(line1.substr(0,pos1),line1.substr(pos1,pos2)));
        
	}

	file1.close();
    file3.open("HashTable.txt");
    cout<<"Mapped values:"<<"\n";
    for(auto it=mp1.begin();it!=mp1.end();it++)
    {   
        cout<<it->first<<"-"<<it->second<<"\n";
    }
    cout<<"Mne\t\topcode\t\tsize\t\ttype\t\toperands"<<"\n";
    while(getline(file3,line1))
    {
        int pos1=line1.find(" ");
        cout<<line1.substr(0,pos1)<<line1.substr(pos1,3)<<line1.substr(pos1+3,3)<<line1.substr(pos1+6,3)<<line1.substr(pos1+9,3)<<"\n";
        // auto it=mp1.find(line1.substr(0,pos1));
        // if(it!=mp1.end())
        // {
        //     cout<<line1<<"--"<<it->second<<"\n";
        // }
        
    }

    }

    file3.close();
    
  

    return 0;
}

/*

Table file-
ADD 01 02 IS 2 
SUB 02 02 IS 2
MULT 03 02 IS 2 
DIV 08 02 IS 2 
BC 07 02 IS 2 
READ 09 01 IS 1 
PRINT 10 01 IS 1 
START 01 0 AD 0
ORIGIN 02 0 AD 1 
LTORG 03 0 AD 0 
END 04 0 AD 0
EQU 05 0 AD 1 
STOP 00 01 IS 0 
MOVER 04 03 IS 2 
MOVEM 05 04 IS 2 
DC 01 1 DL 1 16
DS 02 - DL 1 -1
Mapped values:
DS- 02 - DL 1 -1
DC- 01 1 DL 1 16
MOVEM- 05 04 IS 2 
MOVER- 04 03 IS 2 
ADD- 01 02 IS 2 
MULT- 03 02 IS 2 
END- 04 0 AD 0
DIV- 08 02 IS 2 
BC- 07 02 IS 2 
STOP- 00 01 IS 0 
READ- 09 01 IS 1 
PRINT- 10 01 IS 1 
SUB- 02 02 IS 2
START- 01 0 AD 0
ORIGIN- 02 0 AD 1 
EQU- 05 0 AD 1 
LTORG- 03 0 AD 0 
MNE       OpcodeTable
START 2000     -- 01 0 AD 0
MOVER  AREG A    -- 04 03 IS 2 
ADD AREG X  -- 01 02 IS 2 
DIV BREG A -- 08 02 IS 2 
STOP-- 00 01 IS 0 
END-- 04 0 AD 0
*/