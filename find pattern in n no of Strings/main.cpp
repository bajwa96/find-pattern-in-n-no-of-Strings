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
#include <map>
#include "TriesFunctions.h"
using namespace std;

map<int,int> incrementOrInsertIntoMap(map<int,int> mapDaso, int id){
    map<int,int>::iterator it;
    it = mapDaso.find(id);
    if(it != mapDaso.end()){
        it->second = it->second+1;
    }else{
        mapDaso.insert(pair<int, int>(id,1));
    }
    return mapDaso;
}

map<int,int> *incrementOrInsertIntoMap(map<int,int> *mapDaso, int id){
    map<int,int>::iterator it;
    it = mapDaso->find(id);
    if(it != mapDaso->end()){
        it->second = it->second+1;
    }else{
        mapDaso->insert(pair<int, int>(id,1));
    }
    return mapDaso;
}

map<int, int> getCharCount(struct ids *head,map<int,int> *overAllMap){
    
    map<int, int> charCount;
    
    while(head){
       charCount= incrementOrInsertIntoMap(charCount,head->current_id);
        incrementOrInsertIntoMap(overAllMap,head->current_id);
        head=head->next;
    }
    return charCount;
}

struct allDataForPair{
    public :
    map<int, int> charCount;
    char alpha;
    int count;
    allDataForPair(struct ids *head,char alpha,map<int,int> *overAllMap){
        charCount = getCharCount(head, overAllMap);
        this->alpha=alpha;
        this->count = 1;
    }
};

int main() {
    
    make_search_easy mytrie;
    
    vector<string> words;
    vector<allDataForPair*> wordsID;
    map<char,allDataForPair*> wordsIDmap;
    int noOfWords;
    
    cout<<"Enter no of words : ";
    cin>>noOfWords;
    
    for(int i=0;i<noOfWords;i++){
        string word;
        cout<<"Enter "<<i+1<<" word :";
        cin>>word;
        words.push_back(word);
        INFO("Now inserting into TRIES = " + word +"\n");
        mytrie.insert(word,i);
    }

    string pattern;
    cout<<"Enter pattern you want to search for : ";
    cin>>pattern;
    map<int,int> maxCount ;
    for(int i=0;i<pattern.length();i++){
        wordsID.push_back(new allDataForPair(mytrie.search_for_this_char(pattern[i]),pattern[i],&maxCount));
    }
    
    const int ansIndex = pattern.length()-1;
    int longestLen=-1,index=-1;
    map<int,int>::iterator it;
    for (it=maxCount.begin(); it!=maxCount.end(); ++it){
        cout << it->first << " => " << it->second << '\n';
        if(it->second>=ansIndex){
            cout<<"Found Word Fulfilling your given Cond :"<<words[it->first]<<endl;
            if(words[it->first].length()>longestLen){
                longestLen=words[it->first].length();
                index=it->first;
            }
        }
    }
    cout<<"Final Ans = "<<words[it->first]<<endl;
    
    
    
    
    return 0;
}
