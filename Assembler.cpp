#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<fstream>
#include<vector>
#include<unordered_map>
#include<sstream>
#include<bitset>
using namespace std;

//definations
string typeA(vector<string> word, int start, int end, string opcode, int line);
string typeC(vector<string> word, int start, int end, string opcode, int line);
string typeD(vector<string> word, int start, int end, string opcode, int line);
string register_to_string(string r, int line);
string register_to_string_including_flags(string r, int line);
bool syntaxoflable(string s, int line);
string typeA_opcode_finder(string opcode);
string typeB_opcode_finder(string opcode);
string typeC_opcode_finder(string opcode);
string typeD_opcode_finder(string opcode);
string typeE_opcode_finder(string opcode);

//main
int main()
{
    ifstream read;
    ofstream write;

    // reading file first time to store all labels
    write.open("C:\\Users\\yanuj\\Desktop\\test.txt",ios::out);
    string file = "", temp;
    while(!std::getline(std::cin, file).eof())
    {
        write << file << endl;
    }
    write << file << endl;

    write.close();
    read.open("C:\\Users\\yanuj\\Desktop\\test.txt",ios::in);
    if (!read.is_open())
        cout<<"read can't open";

    // hashmap for label
    unordered_map<string, int> lab;
    unordered_map<string, int> var;
    int line = 1; //file line and will include blank lines too
    int ins_number = 0; //instruction number
    int blank_line = 0;
    int line_label = 0;
    int var_line = 0;
    int number_label = 0;
    while(!read.eof())
    {
        string whole_line;
        getline(read, whole_line); //taking whole line from file
        vector<string> word;
        string w;
        stringstream iss(whole_line);
        while (iss >> w)
            word.push_back(w);

        if(word.size() == 0) //condtion for blank lines
        {
            blank_line++;
            continue;
        }
        if(word[0] == "var")
        {
            var_line++;
            line = line + blank_line;
            blank_line = 0;
            line++; //blue line
            line_label++;
            continue;
        }
        line = line + blank_line;
        blank_line = 0;
        string s = word[0];
        if(s[s.length() - 1] == ':')
        {
            if(syntaxoflable(s, line) == false)
            {
                cout<<"Error at line "<<line<<" it is not a valid lable."<<endl;
                exit(0);
            }
            if (lab.find(word[0]) != lab.end())
            {
                cout<<"Error at line "<<line<<" redeclaration of label."<<endl;
                exit(0);
            }
            lab.insert({s,number_label});
        }
        line++; //blue line
        line_label++;
        number_label++;
        ins_number++; //pink line
    }
    
    read.close();
    if(line_label > 256)
    {
        cout<<"Error at line "<<"256"<<" ,total number of instructions exceeded the limit."<<endl;
        exit(0);
    }
    line_label = line_label - var_line;
    line = 1;
    int flag = 0; // it showing no var is encourtered
    // reading file first time to store all variables.
    read.open("C:\\Users\\yanuj\\Desktop\\test.txt",ios::in); //2nd time reopen
    if (!read.is_open())
        cout<<"read can't open";
    while(!read.eof())
    {
        string whole_line;
        getline(read, whole_line); //taking whole line from file
        vector<string> word;
        string w;
        stringstream iss(whole_line);
        while (iss >> w)
            word.push_back(w);

        if(word.size() == 0) //condtion for blank lines
        {
            line++;
            continue;
        }
        if(word[0] == "var")
        {
            if(flag == 1)
            {
                cout<<"Error at line "<<line<<" invalid declaration of variable in between instructions."<<endl;
                exit(0);
            }
            if(word.size() == 2)
            {
                if (var.find(word[1]) != lab.end())
                {
                    cout<<"Error at line "<<line<<" redeclaration of variable."<<endl;
                    exit(0);
                }
                else
                {
                    var.insert({word[1],line_label});
                }
            }
            else
            {
                cout<<"Error at line "<<line<<" invalid synatx of variable."<<endl;
                exit(0);
            }
        }
        else
        {
            flag = 1;
        }
        line_label++;
        line++;
        ins_number++;
    }
    read.close();


    // File in and out
    read.open("C:\\Users\\yanuj\\Desktop\\test.txt",ios::in); //final reopen
    write.open("C:\\Users\\yanuj\\Desktop\\out.txt",ios::out);
    if (!read.is_open())
        cout<<"read can't open";
    if (!write.is_open())
        cout<<"Write can't open"; 

    
    line = 1;
    flag = 0; // halt condition
    //
    while(!read.eof())
    {
        //all registers and flags
        string whole_line;
        string opcode, rs0, rs1, rs2, rs3, rs4, rs5, rs6, sflag, extra;
        getline(read, whole_line); //taking whole line from file

        //vector to store all words extracted from getline string.
        vector<string> word;
        string w;
        stringstream iss(whole_line);
        while (iss >> w)
            word.push_back(w);

        if(word.size() == 0) //condtion for blank lines
        {    
            line++;
            continue;
        }
        if(flag == 1)
        {
            cout<<"Error at line "<<line<<" hlt is not last instruction."<<endl;
            exit(0);
        }
        if(word[0] == "var")
        {
            line++; //blue line
            continue;
        }
        //label check
        int start = 1;
        opcode = word[0];
        if(opcode[opcode.length()-1] == ':')
        {
            //lab.insert(opcode,line);
            opcode = word[start++];
        }

        
        //opcode checking
        if(opcode == "add" || opcode == "sub" || opcode == "mul" || opcode == "xor" || opcode == "or" || opcode == "and") //type A instruction
        {
            //this is a type A instruction so i will check the number of arguments and nature of those arguments
            if(word.size() == (4 + start - 1))
            {
                //correct no. of parameters
                string s = typeA(word, start, (4 + start - 1), opcode, line) + "\n";
                if(s == "-1")
                {
                    cout<<"Error at line "<<line<<" invalid TYPE A instruction."<<endl;
                    exit(0);
                }
                //write in file
                cout<<s;
                write << s;
            }
            else
            {
                cout<<"Error at line "<<line<<" invalid TYPE A instruction."<<endl;
                exit(0);
            }
        }
        else if(opcode == "ls" || opcode == "rs") //type B instruction
        {
            //this is a type B instruction so i will check the number of arguments and nature of those arguments
            if(word.size() == (3 + start - 1))
            {
                //correct no. of parameters
                //checking for numeric characters
                int counter = 0, length = 0;
                if(word[start+1].length() < 2)
                {
                    //throw error
                }
                if(word[start+1][0] != '$')
                {
                    cout<<"Error at line "<<line<<" invalid immediate starting symbol."<<endl;
                    exit(0);
                }
                for(int i=0; word[start+1][i]!='\0' ;i++)
                    length++;
                for(int i=1; i<length; i++)
                {
                        if(word[start+1][i] >= '0' && word[start+1][i] <= '9')
                        {
                            counter++;
                        }
                }
                if(counter!=length - 1)
                {
                    cout<<"Error at line "<<line<<" invalid immediate value."<<endl;
                    exit(0);
                }
                stringstream stringtonumber(word[start+1].substr(1, length));
                int i = 10;
                stringtonumber >> i;
                if(i > 255)
                {
                    cout<<"Error at line "<<line<<" invalid immediate value."<<endl;
                    exit(0);
                }
                std::string ans = std::bitset<8>(i).to_string();
                for(int i = 0; ans.length() < 8; i++)
                {
                    ans = "0" + ans;
                }
                string s = typeB_opcode_finder(opcode);
                string ans2 = register_to_string(word[start], line);
                if(s=="-1")
                {
                    cout<<"Error at line "<<line<<" invalid register value."<<endl;
                    exit(0);
                }
                s = s + ans2 + ans + "\n";
                cout<<s;
                write << s;
            }
            else
            {
                cout<<"Error at line "<<line<<" invalid TYPE B instruction."<<endl;
                exit(0);
            }
        }
        else if(opcode == "mov")
        {
            if(word.size() == (3 + start - 1))
            {
                string s = "00011";
                string reg = register_to_string(word[start], line);
                if(reg == "-1")
                {
                    cout<<"Error at line "<<line<<" invalid register value."<<endl;
                    exit(0);
                }
                string ans = register_to_string_including_flags(word[start+1], line);
                if(ans == "-1")
                {
                    s = "00010";
                    int counter = 0, length = 0;
                    if(word[start+1].length() < 2)
                    {
                        //throw error
                    }
                    if(word[start+1][0] != '$')
                    {
                        cout<<"Error at line "<<line<<" invalid immediate starting symbol."<<endl;
                        exit(0);
                    }
                    for(int i=0; word[start+1][i]!='\0' ;i++)
                        length++;
                    for(int i=1; i<length; i++)
                    {
                            if(word[start+1][i] >= '0' && word[start+1][i] <= '9')
                            {
                                counter++;
                            }
                    }
                    if(counter!=length - 1)
                    {
                        cout<<"Error at line "<<line<<" invalid immediate value."<<endl;
                        exit(0);
                    }
                    stringstream stringtonumber(word[start+1].substr(1, length));
                    int i = 10;
                    stringtonumber >> i;
                    if(i > 255)
                    {
                        cout<<"Error at line "<<line<<" invalid immediate value."<<endl;
                        exit(0);
                    }
                    std::string ans2 = std::bitset<8>(i).to_string();
                    for(int i = 0; ans2.length() < 8; i++)
                    {
                        ans2 = "0" + ans2;
                    }
                    s = s + reg + ans2 + "\n";
                    cout<<s;
                    write << s;
                    line++;
                    continue;
                }
                s = s + "00000" + reg + ans + "\n";
                cout<<s;
                write << s;
            }
            else
            {
                cout<<"Error at line "<<line<<" invalid mov instruction."<<endl;
                exit(0);
            }
        }
        else if(opcode == "div" || opcode == "not" || opcode == "cmp") //type C instruction
        {
            if(word.size() == (3 + start - 1))
            {
                //correct no. of parameters
                string s = typeC(word, start, (3 + start - 1), opcode, line) + "\n";
                if(s == "-1")
                {
                    cout<<"Error at line "<<line<<" invalid TYPE C instruction."<<endl;
                    exit(0);
                }
                //write in file
                cout<<s;
                write << s;
            }
            else
            {
                cout<<"Error at line "<<line<<" invalid TYPE C instruction."<<endl;
                exit(0);
            }
        }

        
        else if(opcode == "ld" || opcode == "st") //type D instruction
        {
            if(word.size() == (3 + start - 1))
            {
                //correct no. of parameters
                string s = typeD(word, start, (3 + start - 1), opcode, line);
                if(s == "-1")
                {
                    cout<<"Error at line "<<line<<" invalid TYPE C instruction."<<endl;
                    exit(0);
                }
                //write in file
                
                //variable ckecking if present or not
                std::unordered_map<std::string,int>::const_iterator got = var.find (word[start+1]);
                if (var.find(word[start+1]) == var.end())
                {
                    cout<<"Error at line "<<line<<" variable not declared."<<endl;
                    exit(0);
                }
                int i = got->second;
                std::string ans = std::bitset<8>(i).to_string();
                for(int i = 0; ans.length() < 8; i++)
                {
                    ans = "0" + ans;
                }
                s = s + ans + "\n";
                cout<<s;
                write << s;
            }
            else
            {
                cout<<"Error at line "<<line<<" invalid TYPE D instruction."<<endl;
                exit(0);
            }
        }
        else if(opcode == "jmp" || opcode == "jlt" || opcode == "jgt" || opcode == "je") //type E instruction
        {
            if(word.size() == (2 + start - 1))
            {    //correct no. of parameters
                
                string s = typeE_opcode_finder(opcode);
                if(s == "-1")
                {
                    cout<<"Error at line "<<line<<" invalid TYPE E instruction."<<endl;
                    exit(0);
                }

                s = s + "000";
                //write in file
                word[start] = word[start] + ":";
                //label ckecking if present or not
                std::unordered_map<std::string,int>::const_iterator got = lab.find(word[start]);
                if (lab.find(word[start]) == lab.end())
                {
                    cout<<"Error at line "<<line<<" label not declared."<<endl;
                    exit(0);
                }
                int i = got->second;
                std::string ans = std::bitset<8>(i).to_string();
                for(int i = 0; ans.length() < 8; i++)
                {
                    ans = "0" + ans;
                }
                cout<<s + ans + "\n";
                write << s + ans + "\n";
            }
            else
            {
                cout<<"Error at line "<<line<<" invalid TYPE E instruction."<<endl;
                exit(0);
            }
        }
        else if(opcode == "hlt") //type E instruction
        {
            if(word.size() == start)
            {    flag = 1;
                string s = "1001100000000000";
                cout<<s;
                write << s;
            }
            else
            {
                cout<<"Error at line "<<line<<" invalid TYPE F instruction."<<endl;
                exit(0);
            }
        }
        else
        {
            cout<<"Error at line "<<line<<" invalid instruction."<<endl;
            exit(0);
        }
        line++;
    }
    if(flag == 0)
    {
        line--;
        cout<<"Error at line "<<line<<" halt is missing."<<endl;
        exit(0);
    }

}

//--------------------------------------------------------------------------------------------------------------------------------
//**
//--------------------------------------------------------------------------------------------------------------------------------

//main functions

//function appends bits to generate the add instruction
string typeA(vector<string> word, int start, int end, string opcode, int line) //start means from which index our reading will be done
{
    string ans = typeA_opcode_finder(opcode); //start with opcode
    ans = ans + "00"; //unused bits
    while(start < end)
    {
        string s = register_to_string(word[start++], line);
        if(s=="-1")
        {
            cout<<"Error at line "<<line<<" invalid TYPE A instruction."<<endl;
            exit(0);
        }
        ans = ans + s;
    }
    return ans;
}

string typeC(vector<string> word, int start, int end, string opcode, int line)
{
    string ans = typeC_opcode_finder(opcode); //start with opcode
    ans = ans + "00000"; //unused bits
    while(start < end)
    {
        string s = register_to_string(word[start++], line);
        if(s=="-1")
        {
            cout<<"Error at line "<<line<<" invalid TYPE C instruction."<<endl;
            exit(0);
        }
        ans = ans + s;
    }
    return ans;
}


string typeD(vector<string> word, int start, int end, string opcode, int line) //start means from which index our reading will be done
{
    string ans = typeD_opcode_finder(opcode); //start with opcode
    //while(start < end)
    {
        string s = register_to_string(word[start++], line);
        if(s=="-1")
        {
            cout<<"Error at line "<<line<<" invalid TYPE D instruction."<<endl;
            exit(0);
        }
        ans = ans + s;
    }
    return ans;
}



//--------------------------------------------------------------------------------------------------------------------------------
//**
//--------------------------------------------------------------------------------------------------------------------------------

// Helper functions
string register_to_string(string r, int line)
{
    if(r=="R0")
        return "000";
    if(r=="R1")
        return "001";
    if(r=="R2")
        return "010";
    if(r=="R3")
        return "011";
    if(r=="R4")
        return "100";
    if(r=="R5")
        return "101";
    if(r=="R6")
        return "110";
    cout<<"Error at line "<<line<<" invalid Register."<<endl;
    exit(0);
}

string register_to_string_including_flags(string r, int line)
{
    if(r=="R0")
        return "000";
    if(r=="R1")
        return "001";
    if(r=="R2")
        return "010";
    if(r=="R3")
        return "011";
    if(r=="R4")
        return "100";
    if(r=="R5")
        return "101";
    if(r=="R6")
        return "110";
    if(r=="FLAGS")
        return "111";
    return "-1";
}

//function to fetch opcode for type A instructions
string typeA_opcode_finder(string opcode)
{
    if(opcode == "add")
        return "00000";
    if(opcode == "sub")
        return "00001";
    if(opcode == "mul")
        return "00110";
    if(opcode == "xor")
        return "01010";
    if(opcode == "or")
        return "01011";
    if(opcode == "and")
        return "01100";
    return "-1";
}

string typeB_opcode_finder(string opcode)
{
    if(opcode == "ls")
        return "01001";
    if(opcode == "rs")
        return "01000";
    return "-1";
}

//function to fetch opcode for type C instructions
string typeC_opcode_finder(string opcode)
{
    if(opcode == "mov")
        return "00011";
    if(opcode == "div")
        return "00111";
    if(opcode == "not")
        return "01101";
    if(opcode == "cmp")
        return "01110";
    return "-1";
}

//function to fetch opcode for type D instructions
string typeD_opcode_finder(string opcode)
{
    if(opcode == "ld")
        return "00100";
    if(opcode == "st")
        return "00101";
    return "-1";
}

//function to fetch opcode for type E instructions
string typeE_opcode_finder(string opcode)
{
    if(opcode == "jmp")
        return "01111";
    if(opcode == "jlt")
        return "10000";
    if(opcode == "jgt")
        return "10001";
    if(opcode == "je")
        return "10010";
    return "-1";
}

bool syntaxoflable(string s, int line)
{
    int n = s.length() - 1;
    for(int i = 0; i<n; i++)
    {
        if((s[i]>='0' && s[i] <= '9') || (s[i]>='a' && s[i] <= 'z') || (s[i]>='A' && s[i] <= 'Z') || s[i]=='_')
            continue;
        cout<<"Error at line "<<line<<" invalid label syntax."<<endl;
        exit(0);
    }
    return true;
}