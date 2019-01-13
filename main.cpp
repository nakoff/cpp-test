
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

 
        cout<<"----------->> "<<tmSymbol<<" <<-----------\n";

        if (tmSymbol == '*'){
            tmPos = i;
            for (int pos=fnPos; pos<fileName.length(); pos++){
                //если символ = следующий оператор
                if (i<templ.length()-1 && fileName.at(pos) == templ.at(i+1)){
                    break;
                }
                if (fnPos<fileName.length()-1){
                    if (fileName.at(fnPos) != '/'){
                        fnPos ++;
                        continue;
                    }
                    else{
                        fnPos ++;
                        break;
                    }
                }
            }
        }
        else if (fnSymbol == tmSymbol || tmSymbol == '?'){
            fnPos ++;
            tmPos ++;
            continue;
        }
        else{
            cout<<MESSAGES[FAIL]<<"\n";
            exit(FAIL);
        }

    }

    cout<<MESSAGES[SUCCESS]<<"\n";
    return SUCCESS;
}
