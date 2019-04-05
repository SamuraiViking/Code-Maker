#include<iostream>
#include<fstream>
#include<map>
#include <map>
#include<vector>
#include <unistd.h>
#include<bitset>

using namespace std;

void split(string str,vector<string>&c){
    string word = "";
    for(auto letter: str){
        if(letter == ' '){
            c.push_back(word);
            word = "";
        } else {
            word += letter;
        }
    }
    c.push_back(word);
}

void new_screen(){
    for(int i = 0; i < 50; i++){
        cout << "\n";
    }
}

int main(){

for(int i = 0; i < 10; i++){
    i++;
}


class Converter{
    string filename;
    string message;
public:

    Converter(){};

    void read(string filename){
        this->message = "";
        this->filename = filename;
        string line;
        ifstream myfile(filename);
        if(myfile.is_open()){
            while(getline(myfile,line)){
                this->message += line + "\n";
            }
            myfile.close();
        } else {
            cout << "Unable to open file: " << filename;
        }
    }
    void msg_to_dec(int shift){
        std::vector<int>str_int;

        for(int i = 0; i < message.size(); i++){
            str_int.push_back((int)message[i]);
        }

        message = "";

        for(auto elem: str_int){
            if(elem <= 32){
                elem -= shift;
                message += (char)elem;
            }
            else{
            message.append(to_string(elem));
            message.append(" ");
            }
        }
    }

    void msg_to_hex(){

        std::string temp = message;
        std::string hex_symbol = "";
        message = "";

        std::vector<int>msg_int;
        for(char c: temp){
            msg_int.push_back((int)c);
        }
        for(int num: msg_int){
            int mod = (num % 16);
            int minus_mod = num - mod;
            int divided = minus_mod /= 16;

            divided += 1;

            if(divided > 0)
                divided -= 1;

            if(divided > 0){
                hex_symbol += to_string(divided);
            }
            if(mod < 10){
                hex_symbol += to_string(mod);
            }
            else{
                hex_symbol += (char)(mod+55);
            }
            message += hex_symbol + " ";
            hex_symbol = "";
        }
    }

    void get_msg(){
        cout << message;
    }

    void write(string filename){
        ofstream myfile(filename);
        if(myfile.is_open()){
            myfile << message;
            myfile.close();
        } else {
            message = "Couldn't open file: "+filename;
        }
    }

    void commands(){
        vector<string>history;
        std::string input;
        std::string invalid; 
        std::string back;
        vector<string>command;
        int cmd_size;
        while(1){

            input = "";
            command.clear();
            new_screen();
            cout << message << "\n\n\n";
            cout << "Encript: ";
            getline(std::cin,input); 
            history.push_back(input);

            string word = "";
            for(auto letter: input){
                if(letter == ' '){
                    command.push_back(word);
                    word = "";
                } else {
                    word += letter;
                }
            }
            command.push_back(word);

            cmd_size = command.size();

            if(command[0] == "get"){
                read("input.txt");
            }
            else if(command[0] == "write"){
                cout << "Writing ... ";
                write("input.txt");
                system("killall TextEdit");
                sleep(1);
                system("open input.txt");
            }
            else if(command[0] == "dec"){
                std::vector<int>str_int;
                for(int i = 0; i < message.size(); i++){
                    str_int.push_back((int)message[i]);
                }
                back = message;
                message = "";
                if(command[1] == "whitespace" && cmd_size > 1){
                    for(auto elem: str_int){
                        if(elem <= 32){
                            message.append(to_string(elem));
                        }
                        else{
                            message += (char)elem;
                        }
                    }
                }
                else if(command[1] == "letters" && cmd_size > 1){
                    for(auto elem: str_int){
                        if(elem >= 65 && elem <= 90){
                            message.append(to_string(elem));
                            message.append(" ");
                        }
                        else if(elem >= 97 && elem <= 122){
                            message.append(to_string(elem));
                            message.append(" ");
                        }
                        else{
                            message += (char)elem;
                        }
                    }
                }
                else{
                    for(auto elem: str_int){
                        message.append(to_string(elem));
                        message.append(" ");
                    }
                }
            }
            else if(command[0] == "ascii"){
                vector<string>ascii;
                split(message,ascii);
                back = message;
                message = "";
                for(int i = 0; i < ascii.size()-1; i++){
                    message += (char)stoi(ascii[i]);
                }
            }
            else if(command[0] == "cipher" && cmd_size > 1){
                std::vector<int>str_int;

                for(int i = 0; i < message.size(); i++){
                    str_int.push_back((int)message[i]);
                }
                back = message;
                message = "";
                if(command[1] == "letters" && command.size() > 2){
                    for(auto elem: str_int){
                        if(elem >= 65 && elem <= 90){
                            elem += stoi(command[2]);
                            if(elem < 65)
                                elem = 90 - (64-elem);
                            else if(elem > 90)
                                elem = 65 + (elem - 91);
                            message += (char)elem;
                        }
                        else if(elem >= 97 && elem <= 122){
                            elem += stoi(command[2]);
                            if(elem < 97)
                                elem = 122 - (96-elem);
                            else if(elem > 122)
                                elem = 97 + (elem - 123);
                            message += (char)elem;
                        }
                        else
                            message += (char)elem;
                    }
                }
                if(command[1] == "whitespace" && command.size() > 2){
                    for(auto elem: str_int){
                        if(elem <= 32){
                            elem -= stoi(command[2]);
                            if(elem < 32)
                                elem = 90 - (31-elem);
                            else if(elem > 32)
                                elem = 0 + (elem - 31);
                            message += (char)elem;
                        }
                    }
                }
            }
            else if(command[0] == "hex"){
                std::string temp = message;
                std::string hex_symbol = "";
                back = message;
                message = "";

                std::vector<int>msg_int;
                for(char c: temp){
                    msg_int.push_back((int)c);
                }
                for(int num: msg_int){
                    int mod = (num % 16);
                    int minus_mod = num - mod;
                    int divided = minus_mod /= 16;

                    divided += 1;

                    if(divided > 0)
                        divided -= 1;

                    if(divided > 0){
                        hex_symbol += to_string(divided);
                    }
                    if(mod < 10){
                        hex_symbol += to_string(mod);
                    }
                    else{
                        hex_symbol += (char)(mod+55);
                    }
                    message += hex_symbol + " ";
                    hex_symbol = "";
                }
            }
            else if(command[0] == "history"){
                back = message;
                message = "";
                for(auto elem: history)
                    message +=  elem + "\n";
            }
            else if(command[0] == "quit"){
                string y_or_n = "";
                cout <<"\nAre you sure you want to quit? (Y)es (N)o: ";
                getline(std::cin,y_or_n);
                if((y_or_n == "Y") || (y_or_n == "y")){
                    cout << "\nSelf Destruct\n\n";
                    break;
                }
            }
            else if(command[0] == "binary"){
                vector<string>dec_str;
                split(message,dec_str);
                back = message;
                message = "";
                int x;
                for(auto elem: dec_str){
                    try{
                        x = stoi(elem);
                        message += std::bitset<7>(stoi(elem)).to_string();
                        message += " ";
                    }
                    catch(invalid_argument& e){
                        continue;
                    }
                }
            }
            else if(command[0] == "back"){
                message = back;
            }
            else if(command[0] == "clear"){
                if(command[1] == "history" && command.size() > 1)
                    history.clear();
            }
            else if(command[0] == "length"){
                back = message;
                message = "The displayed message was ";
                message += to_string(back.size());
                message += " characters long";
            }
            else if(command[0] == "freq"){
                back = message;
                if(command[1] == "words" && command.size() > 1){
                    vector<string>str;
                    split(message,str);
                    back = message;
                    message = "";
                    map<string,int>str_freq;
                    for(auto elem: str){
                        if(str_freq.find(elem) == str_freq.end()){
                            str_freq.insert(pair<string,int>(elem,1));
                        } else {
                            str_freq[elem] += 1;
                        }
                    }
                    for(auto elem: str_freq){
                        message += elem.first + ": " + to_string(elem.second) + "\n";
                    }
                }
                else if(command[1] == "char" && command.size() > 1){
                    map<char,int>char_freq;
                    for(auto elem: message){
                        if(char_freq.find(elem) == char_freq.end()){
                            char_freq.insert(pair<char,int>(elem,1));
                        }
                        else {
                            char_freq[elem] += 1;
                        }
                    }
                    message = "";
                    for(auto elem: char_freq){
                        message += (char)elem.first;
                        message += ": " + to_string(elem.second) + "\n";
                    }
                }
                else if(command[1] == "letters" && command.size() > 1){
                    if(command[2] == "case" && command.size() > 2){
                        map<char,int>char_freq;
                        for(auto elem: message){
                                if(char_freq.find(elem) == char_freq.end()){
                                    char_freq.insert(pair<char,int>(elem,1));
                                }
                                else {
                                    char_freq[elem] += 1;
                                }
                        }
                        message = "";
                        for(auto elem: char_freq){
                            if((elem.first >= 65 && elem.first <= 90) || (elem.first >= 97 && elem.first <= 122)){
                                message += (char)elem.first;
                                message += ": " + to_string(elem.second) + "\n";
                            }
                            if(elem.first == 'Z')
                                message += "\n";
                        }
                    }
                    else{
                        map<char,int>char_freq;
                        for(auto elem: message){
                            if(elem >= 65 && elem <= 90){
                                elem += 32;
                            }
                            if(char_freq.find(elem) == char_freq.end()){
                                char_freq.insert(pair<char,int>(elem,1));
                            }
                            else {
                                char_freq[elem] += 1;
                            }
                        }
                        message = "";
                        for(auto elem: char_freq){
                            if(elem.first >= 97 && elem.first <= 122){
                                message += (char)elem.first;
                                message += ": " + to_string(elem.second) + "\n";
                            }
                        }
                    }
                }
            }
            else {
                back = message;
                message = "Invalid Encription Method";
            }
        }
    }
};

Converter msg;

msg.commands();

    return 0;
}

