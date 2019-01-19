#include <iostream>
#include <string>

const char* MESSAGES[3] = {"SUCCESS!", "FAIL!", "BAD ARGUMENTS!"};
enum {SUCCESS = 0, FAIL, BAD_ARG};

using namespace std;

string checkParameter(string parameter, string invalidChars = ""){
    for (int i=0; i < parameter.length(); i++){
        char symbol = parameter[i];
        
        for (int j=0; j < invalidChars.length(); j++){
            if (symbol == invalidChars[j]){
                return "";
            }
        }
        if (symbol == '\\'){
            parameter[i] = '/';
        }
    }
    return parameter;
}

int main(int argc, char *argv[]){
    if (argc < 3){
        cout<<MESSAGES[BAD_ARG]<<" 0\n";
        return BAD_ARG;
    }
    
    string fileName = checkParameter((string)argv[1], "*?");
    string templ = checkParameter((string)argv[2]);
    
    if (fileName == "" || templ == ""){
        cout<<MESSAGES[BAD_ARG]<<" 1\n";
        return BAD_ARG;
    }
    
    int starPos = -1;
    int templPos = 0;
    bool doubleStar = false;
    int doubleStarPos = -1;
    int nameCount = -1;

    for (int namePos=0; namePos<fileName.length(); namePos++){
        if (templPos > templ.length() - 1){
            if (nameCount > -1){
                namePos = nameCount;
                templPos = doubleStarPos + 1;
                starPos = doubleStarPos;
                doubleStar = true;
                continue;
            }

            if (starPos > - 1){
                if (fileName.at(namePos) != '/'){
                    continue;
                }
            }
            cout<<MESSAGES[FAIL]<<" 0\n";
            exit (FAIL);
        }

        if (templ.at(templPos) == '*'){
            if (starPos > -1){
                doubleStar = true;
                doubleStarPos = templPos;
                nameCount = namePos;
            }
            starPos = namePos;
            templPos ++;
            namePos --;
            continue;
        }
        
        if (starPos < 0){
            if (fileName.at(namePos) == templ.at(templPos) || (fileName.at(namePos) != '/' && templ.at(templPos) == '?') ){
                templPos ++;
                continue;
            }
            cout<<MESSAGES[FAIL]<<" 1\n";
            exit (FAIL);
        }
        
        int newTemplPos = templPos;
        int counter = starPos;
        for (int newNamePos=starPos; newNamePos<fileName.length(); newNamePos++){
            char fnSymbol = fileName.at(newNamePos);

            if ( newTemplPos >= templ.length() || (fnSymbol != templ.at(newTemplPos) && templ.at(newTemplPos) != '?') ){
                if (newTemplPos < templ.length() && templ.at(newTemplPos) == '*'){
                    templPos = newTemplPos;
                    namePos = newNamePos - 1;
                    starPos = templPos;
                    doubleStar = false;
                    break;
                }
                
                if ( (newNamePos > fileName.length()-1) || (fnSymbol == '/' && !doubleStar) ){
                    cout<<MESSAGES[FAIL]<<" 2\n";
                    exit (FAIL);
                }
                newTemplPos = templPos;
                newNamePos = counter;
                counter ++;
                continue;
            }
            
            newTemplPos ++;
            
            if ( (fnSymbol == '/' && !doubleStar) || newNamePos >= fileName.length()-1){
                if (newTemplPos < templ.length() && templ.at(newTemplPos) == '*'){
                    doubleStar = false;
                }
                templPos = newTemplPos;
                namePos = newNamePos;
                starPos = -1;
                break;
            }
        }
    }
    
    if (templPos < templ.length()){
        if (templ.at(templPos) != '*'){
            cout<<MESSAGES[FAIL]<<" 3\n";
            exit (FAIL);
        }
    }

    cout<<MESSAGES[SUCCESS]<<endl;
    return SUCCESS;
}