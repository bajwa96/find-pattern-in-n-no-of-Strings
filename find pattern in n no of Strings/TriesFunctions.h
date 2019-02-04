//
//  TriesFunctions.h
//  find pattern in n no of Strings
//
//  Created by Navroop Singh Bajwa on 29/01/19.
//  Copyright © 2019 Navroop Singh Bajwa. All rights reserved.
//

#ifndef TriesFunctions_h
#define TriesFunctions_h

#include<iostream>
using namespace std;

#define ENTRY_LOG(name) std::cout << "Entrying -->" << name<<endl;
#define EXIT_LOG(name) std::cout << "Exiting-->" << name<<endl;
#define INFO(name) std::cout << "INFO-->" << name<<endl;

struct ids{
    int current_id;
    struct ids *next,*prev;
    ids(int idd){
        this->current_id=idd;
        this->next=NULL;
        this->prev=NULL;
    }
};
struct trie{
    //int idforsong; //to be used for song searching instead use head for ids as ids can be multiple
    int count;
    char data;
    struct trie *next[26];
    struct trie *number[10];
    struct ids *head;
    trie(char t){
        for(int i=0;i<=26;i++)this->next[i]=NULL;
        for(int i=0;i<=10;i++)this->number[i]=NULL;
        this->data=t;
        count=1;
        this->head=NULL;
    }
};

class make_search_easy{
    private :
    struct trie *headnumber[10]={NULL};//total=10 heads for numerics
    struct trie *head[26]={NULL};//total 26 heads for alphabets
    
    
    /**
     Checks if given alphabet is b/w 'a' and 'z'

     @param alpha given alpha
     @return value true/false
     */
    bool is_alpha(char alpha){
        if(alpha>='a' && alpha<='z')
            return true;
        return false;
    }
    
    /**
     Checks if given alphabet is b/w '0' and '9'
     
     @param alpha given number
     @return value true/false
     */
    bool is_number(char alpha){
        if(alpha>='0' && alpha<='9')
            return true;
        return false;
    }
    
    struct ids *add_id_for_song(int no,struct ids *head){
        if(head==NULL){
            return new ids (no);
        }else{
            struct ids *rethead=head;
            // insertion in second pos in order to match with exsisting code
            struct ids *posNextToFirst = head->next;
            head->next =add_id_for_song(no,NULL);
            if(head->next){
                head->next->next=posNextToFirst;
            }
//
//            int flag=0;
//            struct ids* last=head;
//            while(head){
//                last=head;
//                if(head->current_id==no){
//                    flag=1;
//                    break;
//                }
//                head=head->next;
//            }
//            if(flag==0){
//                last->next=add_id_for_song(no, NULL);
//            }
            return rethead;
        }
    }
    
    /**
     MAIN Fucntion that handles TRIES inserts given String into trie using recurssion

     @param t given String
     @param head head of t[0] of trie
     @param song_id key associated with
     @return returns tries head address for a-z or 0-9
     */
    trie *perform_insertion(string t,trie *head,int song_id){ //perform from start to advance
        if(head==NULL){
            struct trie *rethead=NULL,*agla=head; // agla -> here means will keep copy of previous pointer
            for(int i=0;i<t.length();i++){
                if(rethead==NULL){
                    rethead=new trie (t[i]);
                    agla=rethead;
                    agla->head=add_id_for_song(song_id, agla->head);// addition for song id
                }else{
                    if(is_alpha(t[i])){
                        agla->next[t[i]-'a']=new trie(t[i]);
                        agla=agla->next[t[i]-'a'];
                    }else{
                        agla->number[t[i]-'0']=new trie(t[i]);
                        agla=agla->number[t[i]-'0'];
                    }
                    agla->head=add_id_for_song(song_id, agla->head);// addition for song id
                }
            }
            return rethead;
        }else{
            //match for same string till we get desired pos to insert and simply increase counter by one when we pass one
            trie *last=head;
            int index=0;
            // iterating given trie to the point where insertion is required and adding ids to exsisting trie nodes
            while(index<t.length() && head!=NULL && head->data==t[index]){
                last=head;
                head->head=add_id_for_song(song_id, head->head);// addition for song id
                last->count=last->count+1;
                if(index+1<t.length()){
                    if(is_alpha(t[index+1]))
                        head=head->next[t[index+1]-'a'];
                    else
                        head=head->number[t[index+1]-'0'];
                }//else break;
                index++;
            }

            string remainingsub=t.substr(index,t.length()); // remaining string not present in trie
            
            if(remainingsub.length()>0){
                if(is_alpha(remainingsub[0])){
                    if(head)
                        head->next[remainingsub[0]-'a']=perform_insertion(remainingsub, NULL,song_id);
                    else
                        last->next[remainingsub[0]-'a']=perform_insertion(remainingsub, NULL,song_id);
                    
                }
                else{
                    if(head)
                        head->number[remainingsub[0]-'0']=perform_insertion(remainingsub, NULL,song_id);
                    else
                        last->number[remainingsub[0]-'0']=perform_insertion(remainingsub, NULL,song_id);
                }
            }
        }
        return head;
    }
    
    
    /**
     inserts given string into trie and updates the respective head node for tries
     rest insertion into trie is handleled by next function perform_insertion
     @param name given string
     @param key key associated with that string
     */
    void insertt(string name,int key){
        
        
        if(is_alpha(name[0])){ // for english a-z
            if(head[name[0]-'a']==NULL){
                // initializes the head
                head[name[0]-'a']=perform_insertion(name, head[name[0]-'a'],key);
            }else{
                // perform insertion is already present node
                perform_insertion(name, head[name[0]-'a'],key);
            }
        }else { // for number 0-9
            if(headnumber[name[0]-'0']==NULL){
                // initializes the head
                headnumber[name[0]-'0']=perform_insertion(name, headnumber[name[0]-'0'],key);
            }else{
                // perform insertion is already present node
                perform_insertion(name, headnumber[name[0]-'0'],key);
            }
        }
    }

    string getparsed(string t){
        string ret="";
        for(int i=0;i<t.length();i++){
            if((t[i]>='a'&&t[i]<='z')||(t[i]>='0'&&t[i]<='9'))ret+=t[i];
        }
        return ret;
    }
    
    void display_unique_ids(struct ids *head){
        if(head){
            while(head){
                cout<<head->current_id<<" ";
                head=head->next;
            }cout<<endl;
        }else cout<<"Empty";
        
    }
    
    void display_thishead(trie *head){
        if(head!=NULL){
            cout<<head->data<<" "<<head->count<<" | ";
            display_unique_ids(head->head);
            for(int i=0;i<26;i++)
                if(head->next[i]!=NULL){
                    display_thishead(head->next[i]);
                    cout<<endl;
                }
            for(int i=0;i<10;i++)
                if(head->number[i]!=NULL){
                    display_thishead(head->number[i]);
                    cout<<endl;
                }
        }
    }
    
    public :
    
    /**
     Insert String associated with specific key for future identification

     @param str string to be inserted
     @param key associated key with string
     
     EX -> insert "new file"
     newfile
     ewfile
     wfile
     file
     ile
     le
     e
     
     */
    void insert(string str,int key){
        string name = "insert";
        ENTRY_LOG(name);
        
        if(str.length()>0){
            string nonspaced="";
            for(int i=0;i<str.length();i++){
                if(is_alpha(str[i])||is_number(str[i]))
                    nonspaced=nonspaced+str[i];
            }
            for(int i=0;i<nonspaced.length();i++){
                if(nonspaced.substr(i,nonspaced.length()).length()>0)
                    insertt(nonspaced.substr(i,nonspaced.length()), key);
            }
        }
        
        EXIT_LOG(name);
    }
    
    struct ids* search_for_this_char(char ch){ // only made for is_alpha condition
        if(is_alpha(ch)){
            return head[ch-'a']?head[ch-'a']->head:NULL;
        }else
            return NULL;
    }
    
    struct ids* search_for_this_string(string t){
        if(t.length()>0){
            
            t=getparsed(t);
            
            int index=0;
            // struct ids *rethead=NULL;
            char start=t[0];
            if(is_alpha(start) && head[start-'a']!=NULL){
                struct trie *temp=head[start-'a'],*last;
                last=temp;
                while( index<=t.length() && temp!=NULL && temp->data==t[index] ){
                    last=temp;
                    if(t[index+1]>='a'&&t[index+1]<='z')
                        temp=temp->next[t[index+1]-'a'];
                    else if(t[index+1]>='0'&&t[index+1]<='1')
                        temp=temp->number[t[index+1]-'0'];
                    index++;
                }
                
                if(t.substr(0,index).length()>0){
                    cout<<"Showing results for : \""<<t.substr(0,index)<<"\""<<endl;
                    if(temp)return temp->head;
                    return last->head;
                }
            }else{
                if(headnumber[start-'0']!=NULL){
                    struct trie *temp=headnumber[start-'0'],*last;
                    last=temp;
                    while(index<t.length()&&temp!=NULL && temp->data==t[index] ){
                        last=temp;
                        
                        if(t[index+1]>='a'&&t[index+1]<='z'){
                            temp=temp->next[t[index+1]-'a'];
                            
                        }
                        else if(t[index+1]>='0'&&t[index+1]<='9'){
                            temp=temp->number[t[index+1]-'0'];
                            //index++;
                        }
                        index++;
                        
                    }
                    if(t.substr(0,index).length()>0){
                        cout<<"Showing results for : \""<<t.substr(0,index)<<"\""<<endl;
                        if(temp)return temp->head;
                        return last->head;
                    }
                }
            }
        }
        return NULL;
    }
    void display(){
        for (int i=0;i<26;i++)display_thishead(head[i]);
        for(int i=0;i<10;i++)display_thishead(headnumber[i]);
    }
};
/*
 for creating object of trie just write
 make_search_easy mytrie;
 mytrie.insert(string , key associated with the string);
 for search purpose
 struct ids *head=mytrie.search_for_this_string(string to be searched);
 for deleting in tries : mytrie.deletion_process( name to be deleted ,  uni_id associated with that string )
 for changing the id of song : mytrie.changing__id_process(name,oldid,newid to be assigned);
 */




#endif /* TriesFunctions_h */
