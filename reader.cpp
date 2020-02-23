#include<bits/stdc++.h>
using namespace std;

// MIPS INSTRUCTIONS

class Instructions{
public:
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
fstream out_file;

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
void lui(string str1,string str2) {
int ind=((int)str1[2]-48);
stringstream ss;
int n;
ss << hex << str2;
ss >> n;
n=n<<16;
assign_pointer(str1[1])[ind]=n;
}

void load_word(string str1,string str2) {
int ind1=(int)str1[2]-48;
int x=0,imm=0;
while(str2[x]!='(') {
imm=imm*10+((int)str2[x]-48);
imm=imm/4;
x++;
    }
int mem,ind2=((int)str2[x+3]-48);
mem=assign_pointer(str2[x+2])[ind2];
mem=(mem+imm*4-address)/4;
assign_pointer(str1[1])[ind1]=memory[mem];
}

void store_word(string str1,string str2) {
int ind1=((int)str1[2]-48);
int x=0,imm=0;
while(str2[x]!='(') {
imm=imm*10+((int)str2[x]-48);
imm=imm/4;
x++;
   }
int mem,ind2=((int)str2[x+3]-48);
mem=assign_pointer(str2[x+2])[ind2];
mem=(mem+imm*4-address)/4;
memory[mem]=assign_pointer(str1[1])[ind1];
}

void add(string str1,string str2,string str3) {
int ind1=((int)str1[2]-48);
assign_pointer(str1[1])[ind1]=zero(str2)+zero(str3);
}

void sub(string str1,string str2,string str3) {
int ind1=((int)str1[2]-48);
assign_pointer(str1[1])[ind1]=zero(str2)-zero(str3);
}

void load_immediate(string str1,string str2) {
int ind=((int)str1[2]-48);
int n;
stringstream ss;
ss << str2;
ss >> n;
assign_pointer(str1[1])[ind]=n;
}

void add_immediate(string str1,string str2,string str3) {
int ind1=((int)str1[2]-48);
int n;
stringstream ss;
ss << str3;
ss >> n;
assign_pointer(str1[1])[ind1]=zero(str2)+n;
}

void set_on_less_than(string str1,string str2,string str3) {
int n;
int ind1=((int)str1[2]-48);
if(zero(str2) < zero(str3))
n=1;
else
n=0;
assign_pointer(str1[1])[ind1]=n;
}

void jump(string str1) {
pc=labels[str1];
}

void branch_equal(string str1,string str2,string str3) {
if(zero(str1) == zero(str2))
jump(str3);
}

void branch_not_equal(string str1,string str2,string str3) {
if(zero(str1) != zero(str2))
jump(str3);
}

void load_address(string str1, string str2) {
    int ind1=((int)str1[2]-48);
    assign_pointer(str1[1])[ind1]=labels[str2]*4+address;
}

void shift_left_logical(string str1,string str2,string str3) {
    int ind1=((int)str1[2]-48);
    int n;
    stringstream ss;
    ss << str3;
    ss >> n;
    assign_pointer(str1[1])[ind1]=zero(str2) << n;
}

void syscall() {
    if(v[0]==1) 
        out_file << a[0] << endl;
}

void word(string str1) {
int n;
stringstream ss;
ss << str1;
ss >> n;
memory[index] = n;
index++;
}
};

// DRIVER FUNCTION

int main(int argc, char const *argv[]) {

Instructions i;
int j;
fstream new_file;
new_file.open("text.txt",ios::in);
string str;
vector <string> instr;
vector <string> line;
int line_num=0;

while(getline(new_file,str)) {
line.push_back(str);
stringstream ss(str);
string w;
while(getline(ss,w,' ')) {
if(w=="")
continue;
else if(w[w.length()-1]==':') {
i.labels[w.substr(0,w.length()-1)]=line_num;
}
}
++line_num;
}
int m = i.labels["main"];
for (auto ad = i.labels.begin(); ad != i.labels.end(); ad++) {
if(ad->second>=m)
ad->second=ad->second-m;
}

for(int line_num=0; line_num<line.size();line_num++) {
if(line[line_num]=="")
continue;
else if(line[line_num].find(".data")!=string::npos) {
++line_num;
while(1) {
if(line[line_num].find(".text")!=string::npos) {
line_num--;
break;
}

stringstream s(line[line_num]);
string word;
vector<string> tokens1;

while(getline(s,word,' ')) {
if(word=="")
continue;
else if(word[word.length()-1]==':') {
i.labels[word.substr(0,word.length()-1)]=i.index;
}
else
tokens1.push_back(word);
}

if(tokens1.size()!=0 && tokens1[0].compare(".word") == 0) {
for(int j =1; j<tokens1.size();j++){
i.word(tokens1[j]);
               } 
       }
line_num++;
}
}

else if(line[line_num].find(".text")!=string::npos) {
for(int line_num2=m; line_num2<line.size(); line_num2++) {
instr.push_back(line[line_num2]);
++i.pc;
}
}
else if(line[line_num].find(".globl main")!=string::npos) {
break; }
}

for(int j=0;j<9;j++)
cout << "s" << j << " " << i.s[j] << endl;
for(int j=0;j<9;j++)
cout << "t" << j << " " << i.t[j] << endl;
for(int j=0;j<2;j++)
cout << "v" << j << " " << i.v[j] << endl;
for(int j=0;j<4;j++)
cout << "a" << j << " " << i.a[j] << endl;
for(int j=0;j<2;j++)
cout << "k" << j << " " << i.k[j] << endl;
for(int j=0;j<i.index;j++)
cout << "memory" << j << " " << i.memory[j] << endl;
cout << "\n";

i.pc=0;
i.out_file.open("console.txt",ios::out);

while(i.pc<instr.size()) {

vector <string> tokens;
stringstream s(instr[i.pc]);
string word;

while(getline(s,word,' ')) {
if(word=="" || word[word.length()-1]==':')
continue;
else
tokens.push_back(word);
}

++i.pc;

if(tokens.size()!=0) {
if(tokens[0].compare("lui")==0)
i.lui(tokens[1],tokens[2]);
if(tokens[0].compare("lw")==0)
i.load_word(tokens[1],tokens[2]);
if(tokens[0].compare("add")==0)
i.add(tokens[1],tokens[2],tokens[3]);
if(tokens[0].compare("sub")==0)
i.sub(tokens[1],tokens[2],tokens[3]);
if(tokens[0].compare("sw")==0)
i.store_word(tokens[1],tokens[2]);
if(tokens[0].compare("addi")==0)
i.add_immediate(tokens[1],tokens[2],tokens[3]);
if(tokens[0].compare("li")==0)
i.load_immediate(tokens[1],tokens[2]);
if(tokens[0].compare("slt")==0)
i.set_on_less_than(tokens[1],tokens[2],tokens[3]);
if(tokens[0].compare("j")==0)
i.jump(tokens[1]);
if(tokens[0].compare("beq")==0)
i.branch_equal(tokens[1],tokens[2],tokens[3]);
if(tokens[0].compare("bne")==0)
i.branch_not_equal(tokens[1],tokens[2],tokens[3]);
if(tokens[0].compare("la")==0)
i.load_address(tokens[1],tokens[2]);
if(tokens[0].compare("sll")==0)
i.shift_left_logical(tokens[1],tokens[2],tokens[3]);
if(tokens[0].compare("syscall")==0)
i.syscall();
}
}
for(int j=0;j<9;j++)
cout << "s" << j << " " << i.s[j] << endl;
for(int j=0;j<9;j++)
cout << "t" << j << " " << i.t[j] << endl;
for(int j=0;j<2;j++)
cout << "v" << j << " " << i.v[j] << endl;
for(int j=0;j<4;j++)
cout << "a" << j << " " << i.a[j] << endl;
for(int j=0;j<2;j++)
cout << "k" << j << " " << i.k[j] << endl;
for(int j=0;j<i.index;j++)
cout << "memory" << j << " " << i.memory[j] << endl;

i.out_file.close();
return 0;
}
