#include<bits/stdc++.h>
using namespace std;

// MIPS INSTRUCTIONS

class Instructions{
public:
	int memory[1024];
	int s[9]; 
	int t[9];
	int v[2];
	int a[4];
	int k[2];
	int address=268500992;

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

	void lui(string str1,string str2) {
		int ind=((int)str1[2]-48);
	    stringstream ss;
	    int n;
	    ss << hex << str2;
	    ss >> n;
	    n=n<<16;
	    assign_pointer(str1[1])[ind]=n;
	    cout << assign_pointer(str1[1])[1] << endl;
	}

	void load_word(string str1,string str2) {
	    int ind1=(int)str1[2]-48;
	    int x=0,imm=0;
	    while(str2[x]!='(') { 
	    imm=imm*10+((int)str2[x]-48);
	    x++;
	    } 
	    int mem,ind2=((int)str2[x+3]-48);
	    mem=assign_pointer(str2[x+2])[ind2];
	    mem=(mem+imm*4-address)/4;
		assign_pointer(str1[1])[ind1]=memory[mem];
		cout << assign_pointer(str1[1])[ind1] << endl; 
	}

	void store_word(string str1,string str2) {
	    int ind1=(int)str1[2]-48;
	    int x=0,imm=0;
	    while(str2[x]!='(') { 
	    imm=imm*10+((int)str2[x]-48);
	    x++;
	    } 
	    int mem,ind2=((int)str2[x+3]-48);
	    mem=assign_pointer(str2[x+2])[ind2];
	    mem=(mem+imm*4-address)/4;
	    memory[mem]=assign_pointer(str1[1])[ind1];
	    cout << memory[mem] << endl;
	}

	void add(string str1,string str2,string str3) {
	    int ind1=(int)str1[2];
	    int ind2=(int)str2[2];
	    int ind3=(int)str3[2];
	    ind1-=48;
	    ind2-=48;
	    ind3-=48;
	    assign_pointer(str1[1])[ind1]=assign_pointer(str2[1])[ind2]+assign_pointer(str3[1])[ind3];
	    cout << s[ind1] << endl;
	}

	void sub(string str1,string str2,string str3) {
	    int ind1=(int)str1[2];
	    int ind2=(int)str2[2];
	    int ind3=(int)str3[2];
	    ind1-=48;
	    ind2-=48;
	    ind3-=48;
	    assign_pointer(str1[1])[ind1]=assign_pointer(str2[1])[ind2]-assign_pointer(str3[1])[ind3];
	    cout << s[ind1] << endl;
	}

	void load_immediate(string str1,string str2) {
	    int ind=((int)str1[2]-48);
	    int n;
	    stringstream ss;
	    ss << str2;
	    ss >> n;
	    assign_pointer(str1[1])[ind]=n;
	   	cout << assign_pointer(str1[1])[ind] << endl;
	}

	void add_immediate(string str1,string str2,string str3) {
	    int ind1=((int)str1[2]-48),ind2=((int)str2[2]-48);
	    int n;
	    stringstream ss;
	    ss << str3;
	    ss >> n;
	    assign_pointer(str1[1])[ind1]=assign_pointer(str2[1])[ind2]+n;
	    cout << assign_pointer(str1[1])[ind1] << endl;
	}

};

// DRIVER FUNCTION

int main(int argc, char const *argv[]){

    Instructions i;
    i.memory[0]=10;
	i.memory[1]=4;
	fstream new_file;
	new_file.open("text.txt",ios::in);
	string str;

	while(getline(new_file,str)){

		vector <string> tokens;
	    stringstream s(str);
	    string word;

	    while(getline(s,word,' '))
	    tokens.push_back(word);

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
	}

	return 0;
}
