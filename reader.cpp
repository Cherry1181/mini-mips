#include<bits/stdc++.h>
using namespace std;

int clock_cycle=0;

Instructions i;
int j;
fstream new_file;
string str;
vector <string> instr;
string word;
vector<string> tokens1;

map<string,list<int>> imap;

stringstream* if_id;
int id_ex[3];
string ex_cat, mem_cat, wb_cat;
string reg_id_ex[3];
int alu_flag=0;
int ex_mem;
int mem_read_flag=0;
int mem_write_flag=0;
int mem_wb;
int write_back_flag=0;
int id_ex_arr[5],ex_mem_arr[5],mem_wb_arr[5]; 

map<string,int> labels;

int pc=0;
int memory[1024];
int s[9]={0};
int t[9]={0};
int v[2]={0};
int a[4]={0};
int k[2]={0};
int address=268500992;
int index=0;

// MIPS INSTRUCTIONS

class Instructions{
public:

    Instructions(){
        imap.insert({"c1",list<int>{1,0,1}});
        imap.insert({"c2",list<int>{1,0,1}});
        imap.insert({"c3",list<int>{0,0,0}});
        imap.insert({"c4",list<int>{1,1,1}});
        imap.insert({"c5",list<int>{0,0,1}});
        imap.insert({"c6",list<int>{0,0,0}});

    }

// void lui(string str1,string str2) {
// int ind=((int)str1[2]-48);
// stringstream ss;
// int n;
// ss << hex << str2;
// ss >> n;
// n=n<<16;
// assign_pointer(str1[1])[ind]=n;
// }

// void load_word(string str1,string str2) {
// int ind1=(int)str1[2]-48;
// int x=0,imm=0;
// while(str2[x]!='(') {
// imm=imm*10+((int)str2[x]-48);
// imm=imm/4;
// x++;
//     }
// int mem,ind2=((int)str2[x+3]-48);
// mem=assign_pointer(str2[x+2])[ind2];
// mem=(mem+imm*4-address)/4;
// assign_pointer(str1[1])[ind1]=memory[mem];
// }

// void store_word(string str1,string str2) {
// int ind1=((int)str1[2]-48);
// int x=0,imm=0;
// while(str2[x]!='(') {
// imm=imm*10+((int)str2[x]-48);
// imm=imm/4;
// x++;
//    }
// int mem,ind2=((int)str2[x+3]-48);
// mem=assign_pointer(str2[x+2])[ind2];
// mem=(mem+imm*4-address)/4;
// memory[mem]=assign_pointer(str1[1])[ind1];
// }

};

int* assign_pointer(char c) {
switch(c) {
case 's':
return s;
case 't':
return t;
case 'v':
return v;
case 'a':
return a;
case 'k':
return k;
}
return NULL;
}

int zero(string str) {
    if((str.compare("$zero")==0) || (str.compare("$0")==0))
        return 0;
    int ind=((int)str[2]-48);
        return assign_pointer(str[1])[ind];
}

void write_back() {
    if(write_back_flag==1) {
        int ind=((int)reg_id_ex[0][2]-48);
        assign_pointer(reg_id_ex[0][1])[ind]=mem_wb;
    }
}

void mem() {
    if(mem_read_flag==1) {
        mem_wb=memory[ex_mem];
        mem_read_flag=0;
    }
    if(mem_write_flag==1) {
        memory[ex_mem]=id_ex[0];
        mem_write_flag=0;
    }
    else 
        mem_wb=ex_mem;
}

void execute() {
    if(alu_flag==0)
        ex_mem=id_ex[1]+id_ex[2];
    if(alu_flag==1)
        ex_mem=id_ex[1]-id_ex[2];
    if(alu_flag==2)
        ex_mem=id_ex[1]<<id_ex[2];
    if(alu_flag==3) {
        if(id_ex[1]<id_ex[2])
            ex_mem=1;
        else 
            ex_mem=0;
    }
    if(alu_flag==4) {
        ex_mem=(id_ex[1]+id_ex[2]*4-address)/4;
    }
}

void decode() {
    vector <string> tokens;
    string word;
    while(getline(*if_id,word,' ')) {
        if(word=="" || word[word.length()-1]==':')
            continue;
        else 
            tokens.push_back(word);
    }
    if(tokens.size()!=0) {
        for(int i=1;i<tokens.size();i++) 
            reg_id_ex[i-1]=tokens[i];
        if(tokens[0].compare["j"]==0)
            pc=labels[reg_id_ex[0]];
        else {
            id_ex[0]=zero(reg_id_ex[0]);
            if(tokens[0].compare("add")==0 || tokens[0].compare("sub")==0 || tokens[0].compare("slt")==0) {
                id_ex[1]=zero(reg_id_ex[1]);
                id_ex[2]=zero(reg_id_ex[2]); 
            }     
            if(tokens[0].compare("addi")==0 || tokens[0].compare("sll")==0) {
                id_ex[1]=zero(reg_id_ex[1]);
                stringstream ss;
                ss << reg_id_ex[2];
                ss >> id_ex[2]; 
            }
            if(tokens[0].compare("beq")==0 || tokens[0].compare("bne")==0) {
                id_ex[1]=zero(reg_id_ex[1]);
                if(tokens[0].compare("beq")==0 && id_ex[0]==id_ex[1])
                    pc=labels[reg_id_ex[2]];
                if(tokens[0].compare("bne")==0 && id_ex[0]!=id_ex[1])
                    pc=labels[reg_id_ex[2]];
            }
            if(tokens[0].compare("lw")==0 || tokens[0].compare("sw")==0) {
                alu_flag=4;
                int x=0;
                id_ex[2]=0;
                while(reg_id_ex[1][x]!='(') { 
                    id_ex[2]=id_ex[2]*10+((int)reg_id_ex[1][x]-48);
                    id_ex[2]=id_ex[2]/4;
                    x++;    }
                int ind2=((int)reg_id_ex[1][x+3]-48);
                id_ex[1]=assign_pointer(reg_id_ex[1][x+2])[ind2];
            }
            if(tokens[0].compare("li")==0) {
                stringstream ss;
                ss << reg_id_ex[1];
                ss >> id_ex[1];
            }
            if(tokens[0].compare("lui")==0) {
                stringstream ss;
                ss << hex << reg_id_ex[1];
                ss >> id_ex[1];
            }
            
            if(tokens[0].compare("la")==0) 
                id_ex[1]=labels[reg_id_ex[1]];
            if(tokens[0].compare("add")==0 || tokens[0].compare("addi")==0)
                alu_flag=0;
            if(tokens[0].compare("sub")==0)
                alu_flag=1;
            if(tokens[0].compare("sll")==0)
                alu_flag=2;
            if(tokens[0].compare("slt")==0)
                alu_flag=3;        
        }
    }
}

void fetch() {
    stringstream s(instr[i.pc]);
    if_id = &s;
    ++pc;
}

// DRIVER FUNCTION

int main(int argc, char const *argv[])  {
    s[1]=2;
    s[3]=1;
    new_file.open("text.asm",ios::in);
        pc=0;
    while(getline(new_file,str))
        instr.push_back(str);
    while(clock_cycle>=0) {
        write_back();
        mem();
        execute();
        decode();
        fetch();
        clock_cycle++;
    }
    return 0;
}