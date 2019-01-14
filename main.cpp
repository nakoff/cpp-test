
#include <iostream>
#include <cstdio>
#include <string>

const char* MESSAGES[3] = {"SUCCESS!", "FAIL!", "BAD ARGUMENTS!"};
enum {SUCCESS = 0, FAIL, BAD_ARG};

using namespace std;

bool checkParameter(string parameter, string invalidChars = ""){
    for (int i=0; i < parameter.length(); i++){
        //cout<<parameters.at(i)<<"\n";
        char symbol = parameter.at(i);
        for (int j=0; j < invalidChars.length(); j++){
            if (symbol == invalidChars.at(j)){
                return false;
            }
        }
    }
    return true;
}

int main(int argc, char *argv[]){
    if (argc < 3){
        cout<<MESSAGES[BAD_ARG]<<"\n";
        return BAD_ARG;
    }

    string fileName = argv[1];
    string templ = argv[2];

    if (!checkParameter(fileName, "*?") || !checkParameter(templ)){
        cout<<MESSAGES[BAD_ARG]<<"\n";
        return BAD_ARG;
    }

    int tmPos = -1;
    int fnPos = 0;


    for (int i=0; i<templ.length(); i++){
        //cout<<fnPos<<" FNPOS\n";
        char tmSymbol = templ.at(i);
        char fnSymbol = fileName.at(fnPos);

 
        cout<<"----------->> "<<tmSymbol<<" "<<fnSymbol<<" <<-----------\n";

        if (tmSymbol == '*'){
            for (int pos=fnPos; pos<fileName.length(); pos++){
                //если символ = следующий оператор
                if (i<templ.length()-1 && fileName.at(pos) == templ.at(i+1)){
                    tmPos = pos+1; //TODO
                    break;
                }
                if (fileName.at(pos) == '/'){
                    tmPos = pos;
                    break;
                }
                if (fnPos<fileName.length()-1){
                    fnPos++;
                    continue;
                }
            }
        }
        // TODO
        else if (tmSymbol == '?'){
            if (tmPos > -1 && tmPos-1 < fileName.length()){
                cout<<fileName.at(tmPos-1)<<" ////\n";
                if (fileName.at(tmPos-1) != '/'){
                    tmPos--;
                    cout<<"cntn\n";
                    continue;
                }
            }
            fnPos++;
        }
        else if (fnSymbol == tmSymbol){
            fnPos ++;
        }
        else{
            cout<<MESSAGES[FAIL]<<" "<<tmSymbol<<"\n";
            exit(FAIL);
        }

    }

    cout<<MESSAGES[SUCCESS]<<"\n";
    return SUCCESS;
}
