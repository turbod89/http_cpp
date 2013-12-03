#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <curl/curl.h>

#include "classes/chatConnection.h"

using namespace std;

bool configureRead(chatConnection& CH) {

  ifstream fin;
  fin.open("config.dat");
  if (fin.is_open())
    while( !fin.eof() ) {
	  string s;
      fin >> s;
      if (s == "[SERVER]") {
        fin >> s;
        CH.setServer(s);
      } else if (s == "[LOGIN]") {
        fin >> s;
        CH.setUser(s);
        fin >> s;
        CH.setPassword(s);
      }
    }
  else 
	return false;

 fin.close();

 return true;

}

bool configureWrite(const chatConnection& CH) {

  ofstream fout;
  fout.open("config.dat");
  if (fout.is_open()) {
	  
	if (CH.getServer()!="")
	  fout << "[SERVER]" << endl << CH.getServer() << endl;
	if (CH.getUser() != "" and CH.getPassword() != "")
	    fout << "[LOGIN]" << endl << CH.getUser() << endl << CH.getPassword() << endl;
	    
  } else 
	return false;

 fout.close();

 return true;

}

//
//  Forms
//

void askUserAndPassword(istream& in, ostream& out, chatConnection& CH) {
 
  string user, pass;
  out << endl;
  out << "  User: ";
  getline(in,user);
  out << "  Password: ";
  getline(in,pass);
  out << endl;
  CH.setUser(user);
  CH.setPassword(pass);
  
}

void printStatus(ostream& out, chatConnection& CH) {

  out << endl;
  out << "  Status" << endl;
  out << "  ======" << endl;
  out << endl;
 
  if (CH.getServer() != "")
	out << "  Server: " << CH.getServer() << endl;
  else
	out << "  Server: NOT ESTABLISHED"<< endl;
  
  if (CH.getUser() != "")
	out << "  User: " << CH.getUser() << endl;
  else
	out << "  User: NOT LOGGED"<< endl;

  out << endl;
 
}

void displayArguments(ostream& out) {
  out << endl;
  out << endl;
  out << "  Argument tree" << endl;
  out << "  =============" << endl;
  out << endl;
  out << "  + " << "configure" << endl;
  out << "  |-> " << "server <servername>" << endl;
  out << "  + " << "login" << endl;
  out << "  + " << "logout" << endl;
  out << "  + " << "new" << endl;
  out << "  |-> " << "chat <chatname>" << endl;
  out << "  - " << "status" << endl;
  out << endl;
  out << endl;
}


void printMsg(ostream& out, const string s){
  out << "  * " << s << endl;
}

void printError(ostream& out, const string s){
  out << "  /!\\ " << s << endl;
}

void errorExpectedArgument(ostream& out) {printError(out,"Expected argument.");}
void errorSaving(ostream& out) {printError(out,"Error saving.");}
void errorBadArgument(ostream& out) {printError(out,"Unespected argument.");}

void succesfullyAction(ostream& out) {printMsg(out,"Done succesfully!");}


//
//  configure
//

bool configureOptions(int start,int argc, char* argv[], chatConnection& CH) {
  
    string s;
  
    if (argc < start + 1) {
		
      errorExpectedArgument(cout);
      return 1;
      
    } else if (string(argv[start]) == "server") {
    
      if (argc < start + 2) {
		  
        errorExpectedArgument(cout);
        return 1;
        
      } else {
	    
	    CH.setServer(string(argv[start +1]));
	    
        if (configureWrite(CH))
          succesfullyAction(cout);
        else
          errorSaving(cout);
	  }
	
	} else {
	  errorBadArgument(cout);
    }
  
}

//
//  new
//

bool newOptions(int start,int argc, char* argv[], chatConnection& CH) {
    
    string s;
    
    if (argc < start +1) {
		
      errorExpectedArgument(cout);
      return false;
      
    } else if (string(argv[start]) == "chat") {
    
      if (argc < start+2) {
		  
        errorExpectedArgument(cout);
        return false;
        
      } else {
		  
        if (CH.newChat(string(argv[start+1])))
		  succesfullyAction(cout);
		else
		  printError(cout,"Chat not created");
		
	  }
	
	} else {
	  errorBadArgument(cout);
	  return false;
    }
	  
  return true;
}
 
int main(int argc, char* argv[]) {

  if (argc == 1) {
    displayArguments(cout);
    return 0;
  }
  
  chatConnection CH;
  
  if (!configureRead(CH)) {
    printError(cout,"Cannot read config.dat");
    return 1;
  }
  
  // do stuff
  
  string s;
  
  if (string(argv[1]) == "configure") {
	  
    if (!configureOptions(2,argc,argv,CH))
      return 0;
    
  } else if (string(argv[1]) == "login") {
	
	askUserAndPassword(cin,cout,CH);
	
	if (CH.checkLogin()) {
		
	  succesfullyAction(cout);
	  
	  if (!configureWrite(CH))
	    errorSaving(cout);
	    
	} else {
		
	  printError(cout,"Wrong login.");
	  return 1;
	  
	}
	
  } else if (string(argv[1]) == "logout") {
      
      CH.setUser("");
      CH.setPassword("");
	  
	  if (configureWrite(CH))
	    succesfullyAction(cout);
	  else
	    errorSaving(cout);
	  
  } else if (string(argv[1]) == "new") {
	
	if (!newOptions(2,argc,argv,CH))
      return 0;

  } else if (string(argv[1]) == "signin") {
	
    askUserAndPassword(cin,cout,CH);	
    
    if (CH.signIn()) {
	  succesfullyAction(cout);
	  
	  if (configureWrite(CH))
	    printMsg(cout,"Login as " + CH.getUser());
	  else
	    errorSaving(cout);
	    
	} else {
	  printError(cout,"Not signed in. Error: " + CH.error());
	  return 1;
	}

  } else if (string(argv[1]) == "status") {

    printStatus(cout,CH);	 

  } else {
    errorBadArgument(cout);
  }
	
  return 0;
}
