/*
 *  Class: json
 *  Author: Daniel Torres
 *  Filename: json.h
 * 
 * 
 * 
 *  Notes: 
 * 
 *
 */

#ifndef H_JSON
#define H_JSON

#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include <vector>
#include <map>

using namespace std;

class json {

  private:
    
    string value;
    vector<int> tree;
    
    int getEndOfString(const string& s,int& i) const;
    vector<int> make_tree(const string& s, int& i) const;
  
  public:
  
    json();
    json(const string& s);
    
    void set(const string& s);
    
    string print() const;
    int length() const;
    int size() const;

};


#endif
