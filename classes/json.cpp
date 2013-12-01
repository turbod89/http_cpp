#include "json.h"

/////////////////////////////////
//
// Private
//
////////////////////////////////


int json::getEndOfString(const string& s, int& i) const {

  int n = s.size();

  while (i<n && (s[i]!='"') )
    i++;
    
  i++;
  
  while (i<n && (s[i]!='"')) {
    if (s[i]=='\\')
      i++;
    i++;
  }
  
  return i;
}


vector<int> json::make_tree(const string& s, int& i) const {

  int n = s.size();
  vector<int> tree;

  while (i<n && (s[i]!='{'|| s[i]!='[' || s[i]!='"') )
    i++;
    
  tree.push_back(i);

  if (s[i]=='"') {
    tree.push_back(0);
    getEndOfString(s,i);
  } else if (s[i]=='[') {
    
    tree.push_back(0);
    i++;
    
    while (i<n && s[i]!=']') {
    
      while (i<n && (s[i]!='{'|| s[i]!='[' || s[i]!='"' || s[i]!=']') )
        i++;
        
      if (s[i]!='{'|| s[i]!='[' || s[i]!='"') {
	    vector<int> subtree = this->make_tree(s,i);
	    for (int j = 0; j < subtree.size(); j++)
	      tree.push_back(subtree[i]);
	    tree[1]++;
	    i++;
	  }
	  
    }
  }

  return tree;

}

json::json(){
  
  this->value ="";
  
}

json::json(const string& s) {
  this->value = s;
}

void json::set(const string& s) {
  this->value = s;
}

string json::print() const {
 return this->value;
}

int json::length() const {
	return 0;

}

int json::size() const{
  return this->value.size();
}


