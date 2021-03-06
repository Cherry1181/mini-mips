#include<bits/stdc++.h>
using namespace std;

// MIPS INSTRUCTIONS

class Instructions{
public:
    map<string,int> labels;
	int pc=0;
	int memory[1024];
	int s[9]; 
	int t[9];
	int v[2];
	int a[4];
	int k[2];
	int address=268500992;
	int index = 0;

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
	void word(string str1){
		int n;
		stringstream ss;
		ss << str1;
		ss >> n;
		memory[index] = n;
		index++;
	}
};

// DRIVER FUNCTION

int main(int argc, char const *argv[]){

    Instructions i;
	int j;
	fstream new_file;
	new_file.open("text.txt",ios::in);
	string str;
	vector <string> instr;
	vector <string> line;

	while(getline(new_file,str)) 
		line.push_back(str);

    int line_num;
    for(line_num=0; line_num<line.size(); line_num++) {
		stringstream ss1(line[line_num]);
		string w1;
		while(getline(ss1,w1,' ')) {
		if(w1=="")
		    continue;
		else if(w1.compare(".data") == 0){
			while(1) {
				stringstream s(line[line_num+1]);
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

				if(tokens1[0].compare(".word") == 0){
					for(int j =1; j<tokens1.size();j++){
						i.word(tokens1[j]);
					}
				}
				else if(tokens1[0].compare(".text") == 0) {
                    line_num++;
                    continue;
				}
                else if(tokens1[0].compare(".globl")==0 && tokens1[1].compare("main")==0) {
					break; 
                }
				line_num++;
			}
            for(int dummy=line_num+1; dummy<line.size(); dummy++) {
					stringstream ss2(line[dummy]);
					string w2;
					while(getline(ss2,w2,' ')) {
					if(w2=="")
						continue;
					else if(w2[w2.length()-1]==':') {
                        
						if(w2.substr(0,w2.length()-1).compare("main")==0) {
						for(int dummy1=dummy; dummy1<line.size();dummy1++) {
							instr.push_back(line[dummy1]);
							stringstream ss3(line[dummy1]);
							string w3;
							while(getline(ss3,w3,' ')) {
								if(w3=="")
									continue;
								else if(w3[w3.length()-1]==':') 
									i.labels[w3.substr(0,w3.length()-1)]=i.pc; }
								i.pc++; }
					  }  }  } 
                      line_num=line.size();
					  break; }
		}
	} }

    i.pc=0;
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
		}
	}
	for(j=0;j<11;j++) 
		cout << i.memory[j] << endl;
	return 0;
}
