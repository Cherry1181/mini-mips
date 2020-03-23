#include <bits/stdc++.h>
using namespace std;

int clock_cycle = 0;

Instructions i;
int j;
fstream new_file;
string str;
vector<string> instr;
string word;
vector<string> tokens1;

stringstream *if_id;
int id_ex[3];
string reg_id_ex[3];

map<string, int> labels;
int pc = 0;
int memory[1024];
int s[9] = {0};
int t[9] = {0};
int v[2] = {0};
int a[4] = {0};
int k[2] = {0};
int address = 268500992;
int index = 0;

// MIPS INSTRUCTIONS

class Instructions
{
public:
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

    void add()
    {
        id_ex[1] = id_ex[2] + id_ex[3];
        cout << id_ex[1] << endl;
    }

    void sub()
    {
        id_ex[1] = id_ex[2] + id_ex[3];
        cout << id_ex[1] << endl;
    }

    void set_on_less_than(string str1, string str2, string str3)
    {
        int n;
        int ind1 = ((int)str1[2] - 48);
        if (zero(str2) < zero(str3))
            n = 1;
        else
            n = 0;
        assign_pointer(str1[1])[ind1] = n;
        cout << assign_pointer(str1[1])[ind1] << endl;
    }
};

int *assign_pointer(char c)
{
    switch (c)
    {
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

int zero(string str)
{
    if ((str.compare("$zero") == 0) || (str.compare("$0") == 0))
        return 0;
    int ind = ((int)str[2] - 48);
    return assign_pointer(str[1])[ind];
}

void write_back()
{
    int ind = ((int)reg_id_ex[1][2] - 48);
    assign_pointer(reg_id_ex[1][1])[ind] = id_ex[0];
}

void mem()
{
}

void execute()
{
    if (reg_id_ex[0].compare("add") == 0)
        i.add();
    if (reg_id_ex[0].compare("sub") == 0)
        i.sub();
}

void decode()
{
    vector<string> tokens;
    string word;
    while (getline(*if_id, word, ' '))
    {
        if (word == "" || word[word.length() - 1] == ':')
            continue;
        else
            tokens.push_back(word);
    }
    if (tokens.size() != 0)
    {
        reg_id_ex[0] = tokens[0];
        for (int i = 1; i < tokens.size(); i++)
        {
            reg_id_ex[i - 1] = tokens[i];
            id_ex[i - 1] = zero(tokens[i]);
        }
        //if(tokens[0].compare("lui")==0)
        // i.lui(tokens[1],tokens[2]);
        // if(tokens[0].compare("lw")==0)
        // i.load_word(tokens[1],tokens[2]);
        //if(tokens[0].compare("sw")==0)
        // i.store_word(tokens[1],tokens[2]);
        // if(tokens[0].compare("addi")==0)
    }
}

void fetch()
{
    stringstream s(instr[i.pc]);
    if_id = &s;
    ++i.pc;
}

// DRIVER FUNCTION

int main(int argc, char const *argv[])
{
    s[1] = 2;
    s[3] = 1;
    new_file.open("text.asm", ios::in);
    i.pc = 0;
    while (getline(new_file, str))
        instr.push_back(str);
    while (clock_cycle >= 0)
    {
        write_back();
        mem();
        execute();
        decode();
        fetch();
        clock_cycle++;
    }

    return 0;
}