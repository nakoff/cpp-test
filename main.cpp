#pragma once
#include <iostream>
#include <cstdio>
#include <string>

using namespace std;
const char* MESSAGES[3] = {"SUCCESS!", "FAIL!", "BAD ARGUMENTS!"};
enum {SUCCESS = 0, FAIL, BAD_ARG} results;
//int result

bool checkParameter(string parameter, string invalidChars = ""){
    cout<<parameter.length()<<"\n";
    for (int i; i < parameter.length(); i++){
        cout<<i;
        printf("CHECK!");
        //cout<<parameters.at(i)<<"\n";
        char symbol = parameter.at(i);
        printf((char*)symbol);
        for (int j; j < invalidChars.length(); j++){
            if (symbol == invalidChars.at(j)){
                printf("BAD!!!\n");
                return false;
            }
        }
        if (symbol == '\\'){
            symbol = '/';
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

    for (int i; i < fileName.length(); i++){
        printf("!!!");
        string invalidChars = "*?";
        char symbol = fileName.at(i);
        printf((char*)symbol);
//        for (int j; j < invalidChars.length(); j++){
//            if (symbol == invalidChars.at(j)){
//                printf("BAD!!!\n");
//                return false;
//            }
//        }
        if (symbol == '\\'){
            symbol = '/';
        }
    }
    /*if (!checkParameter(fileName, "*?") || !checkParameter(templ)){
        cout<<MESSAGES[BAD_ARG]<<"\n";
        return BAD_ARG;
    }*/

    cout<<argv[1]<<"\n"<<argv[2]<<"\n";
    cout<<MESSAGES[SUCCESS]<<"\n";
    return SUCCESS;
}
