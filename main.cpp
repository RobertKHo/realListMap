// $Id: main.cpp,v 1.2 2015-02-12 11:24:26-08 - - $
//Robert Ho rokho@ucsc.edu
//Daniel Urrutia deurruti@ucsc.edu
#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream>

using namespace std;

#include "listmap.h"
#include "xpair.h"
#include "util.h"

using str_str_pair = xpair<const string,string>;
using str_str_map = listmap<string,string>;

void scan_options (int argc, char** argv) {
   opterr = 0;
   for (;;) {
      int option = getopt (argc, argv, "@:");
      if (option == EOF) break;
      switch (option) {
         case '@':
            traceflags::setflags (optarg);
            break;
         default:
            complain() << "-" << (char) optopt << ": invalid option"
                       << endl;
            break;
      }
   }
}

string trim (const string &str){
   size_t first = str.find_first_not_of(" \t");
   if(first == string::npos) return "";
   size_t last = str.find_last_not_of(" \t");
   return str.substr(first, last - first +1);
}

int main (int argc, char** argv) {
   sys_info::set_execname (argv[0]);
   scan_options (argc, argv);
   string file; 
   ifstream inFile;
   str_str_map test;
   int count = 0; 
   string fname;
   bool check = false;

   for(int i = 1; i < argc; ++i){
      file = argv[i];
      fname = file;
      check = true;
      inFile.open(file.c_str());
    
      if(!inFile){ 
         cout << "keyvalue: "<<fname <<": No such file or directory"
              << endl;
         return -1; 
      } 

      //reading contents
      for(;;){ 
         getline(inFile,file);
         if(inFile.eof()) break;
         file = trim(file);
         if(file.size() == 0 or file[0] == '#'){
            ++count;
            cout <<fname<<": "<<count<<": " << file << endl;
            continue;
         }
         size_t pos = file.find_first_of("=");
         if(pos == string::npos){
            ++count;
            string key = trim(file.substr(0, pos == 0 ? 0 : pos));
            cout <<fname<<": "<<count<<": " << file << endl;
            test.find(key);
         }else{
            string key = trim(file.substr(0, pos == 0 ? 0 : pos));
            string value = trim(file.substr(pos + 1));
            if(key != "" and value != ""){
               ++count;
               str_str_pair pair (key,value);
               cout <<fname<<": "<<count<<": " << file << endl;
               cout << pair.first<< " = "<<pair.second << endl;
               test.insert(pair); 
            }else if(key == "" and value == ""){
               ++count;
               cout <<fname<<": "<<count<<": " << file << endl;
               //print all instances in the map
               test.print_pairs();
            }else if(key == "" and value != ""){
               //print all instances that have this value
               ++count;
               cout <<fname<<": "<<count<<": " << file << endl;
               test.find_value(value);
            }else if(key != "" and value == ""){
               ++count;
               cout <<fname<<": "<<count<<": " << file << endl;
               //delete instance
               //check if key is there
               str_str_map::iterator del = test.find(key);
               if(del != test.end()){
                  test.erase(del);
               }
            }
         }
      }
      count = 0;
      inFile.close();
   } 
       
      if(not check){ 
         for(;;){ 
            getline(cin,file);
            if(cin.eof()) break;
            file = trim(file);
            if(file.size() == 0 or file[0] == '#'){
               ++count;
               cout << "-: "<<count<<": "<< file << endl;
               continue;
            }
            size_t pos = file.find_first_of("=");
            if(pos == string::npos){
               ++count;
               string key = trim(file.substr(0, pos == 0 ? 0 : pos));
             cout <<"-: "<<count<<": " << file << endl;
             test.find(key);
          }else{
             string key = trim(file.substr(0, pos == 0 ? 0 : pos));
             string value = trim(file.substr(pos + 1));
             if(key != "" and value != ""){
                ++count;
                str_str_pair pair (key,value);
                cout <<"-: "<<count<<": " << file << endl;
                cout << pair.first<< " = "<<pair.second << endl;
                test.insert(pair); 
             }else if(key == "" and value == ""){
                ++count;
                cout <<"-: "<<count<<": " << file << endl;
                //print all instances in the map
                test.print_pairs();
             }else if(key == "" and value != ""){
                //print all instances that have this value
                ++count;
                cout <<"-: "<<count<<": " << file << endl;
                test.find_value(value);
             }else if(key != "" and value == ""){
                ++count;
                cout <<"-: "<<count<<": " << file << endl;
                //delete instance
                //check if key is there
                str_str_map::iterator del = test.find(key);
                if(del != test.end()){
                   test.erase(del);
                }
             }
          }
       }
    }

   test.~listmap();
   delete sys_info::execname;
   return EXIT_SUCCESS;
}

