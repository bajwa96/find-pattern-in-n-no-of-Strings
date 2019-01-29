//
//  main.cpp
//  find pattern in n no of Strings
//
//  Created by Navroop Singh Bajwa on 28/01/19.
//  Copyright © 2019 Navroop Singh Bajwa. All rights reserved.
//
#include <iostream>
#include <string>
#include<vector>
#include "TriesFunctions.h"
using namespace std;
int main() {
    
    make_search_easy mytrie;
    
    vector<string> words;
    vector<ids*> wordsID;
    int noOfWords;
    
    cout<<"Enter no of words : ";
    cin>>noOfWords;
    
    for(int i=0;i<noOfWords;i++){
        string word;
        cin>>word;
        words.push_back(word);
        DEBUG_METHOD("Now inserting into TRIES = " + word);
        mytrie.insert(word,i);
    }

    string pattern;
    cout<<"Enter pattern you want to search for : ";
    cin>>pattern;
    
    for(int i=0;i<pattern.length();i++){
        DEBUG_METHOD("Now searching given String in Tries " + pattern.substr(0,i));
        string charStr = pattern.at(i);
        wordsID.push_back(mytrie.search_for_this_string(charStr));
    }
    for(int i=0;i<wordsID.size();i++){
        struct ids *head=wordsID.at(i);
        while(head){
            cout<<words.at(head->current_id)<<" ";
            head=head->next;
        }
        cout<<endl;
    }
    
    return 0;
}
