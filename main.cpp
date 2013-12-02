#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <curl/curl.h>

#include "classes/chatConnection.h"

using namespace std;

void displayArguments() {
  cout << endl;
  cout << endl;
  cout << "Arguments: " << endl;
  cout << "  -> " << "configure" << endl;
  cout << "  -> " << "login" << endl;
  cout << "  -> " << "logout" << endl;
  cout << "  -> " << "status" << endl;
  cout << endl;
  cout << endl;
}

bool configureRead(string& server, string& user, string& password) {

  ifstream fin;
  fin.open("config.dat");
  if (fin.is_open())
    while( !fin.eof() ) {
	  string s;
      fin >> s;
      if (s == "[SERVER]")
        fin >> server;
      else if (s == "[LOGIN]")
        fin >> user >> password;
    }
  else 
	return false;

 fin.close();

 return true;

}

bool configureWrite(const string& server,const string& user,const string& password) {

  ofstream fout;
  fout.open("config.dat");
  if (fout.is_open()) {
	  
	if (server!="")
	  fout << "[SERVER]" << endl << server << endl;
	if (user != "" and password != "")
	    fout << "[LOGIN]" << endl << user << endl << password << endl;
	    
  } else 
	return false;

 fout.close();

 return true;

}

 
int main(int argc, char* argv[]) {

  if (argc == 1) {
    displayArguments();
    return 0;
  }
  
  // Configure
  
  string server   = "";
  string user     = "";
  string password = "";
  
  if (!configureRead(server,user,password)) {
    cout << "Cannot read config.dat" << endl;
    return 1;
  }
  
  // do stuff
  
  chatConnection CH(server,user,password);
  
  if (string(argv[1]) == "configure") { 
    
    if (argc < 3) {
      cout << "Expected argument" << endl;
      return 1;
    } else if (string(argv[2]) == "server") {
    
      if (argc < 4) {
        cout << "Expected server url" << endl;
        return 1;
      } else {
	    server = string(argv[3]);
        if (configureWrite(server,user,password)) {
          cout << "Server url set to: " << server << endl;
          CH.setServer(server);
        } else
          cout << "Error setting server url to: " << server << endl;
	  }
	
	} else {
	  cout << "Bad argument" << endl;
    }
  
  } else if (string(argv[1]) == "login") {
	
	cout << "User: ";
	getline(cin,user);
	cout << "Password: ";
	getline(cin,password);
	
	CH.setUser(user);
	CH.setPassword(password);
	
	if (CH.checkLogin()) {
	  cout << "Succeful login!" << endl;
	  if (configureWrite(server,user,password))
	    cout << "Login as " << user << endl;
	  else
	    cerr << "Error saving login on config.dat" << endl;
	} else {
	  cout << "Wrong login." << endl;
	  return 1;
	}
	
  } else if (string(argv[1]) == "logout") {
	  user = "";
	  password = "";
	  
	  if (configureWrite(server,user,password))
	    cout << "Logged out succesfully." << endl;
	  else
	    cerr << "Error saving logout on config.dat" << endl;
	  
  } else if (string(argv[1]) == "new") {

    if (argc < 3) {
      cout << "Expected argument" << endl;
      return 1;
    } else if (string(argv[2]) == "chat") {
    
      if (argc < 4) {
        cout << "Expected new chat's name" << endl;
        return 1;
      } else {
	    string chatName = string(argv[3]);
        if (CH.newChat(chatName)) {
		  cout << "New chat succefully created" << endl;
		} else {
		  cout << "New chat not created"<< endl;
		}
	  }
	
	} else {
	  cout << "Bad argument" << endl;
    }
	  
	  
	  
  } else if (string(argv[1]) == "signin") {
	
	cout << "User: ";
	getline(cin,user);
	cout << "Password: ";
	getline(cin,password);
	
    CH.setUser(user);
	CH.setPassword(password);
	
    if (CH.signIn()) {
	  cout << "Succeful Sign In!" << endl;
	  if (configureWrite(server,user,password))
	    cout << "Login as " << user << endl;
	  else
	    cerr << "Error saving login on config.dat" << endl;
	} else {
	  cout << "Not signed in. Error: "<< CH.error() << endl;
	  return 1;
	}

  } else if (string(argv[1]) == "status") {
	 
	 cout << endl;
	 cout << "Status" << endl;
	 cout << "======" << endl;
	 cout << endl;
	 if (server != "")
	   cout << "Server: " << server << endl;
	 else
	   cout << "Server: NOT ESTABLISHED"<< endl;
	 if (user != "")
	   cout << "User: " << user << endl;
  	 else
	   cout << "User: NOT LOGGED"<< endl;

	 cout << endl;
 
  } else {
  
    cout <<"'"<< argv[1] << "' is not a valid argument" << endl; 
  }
	
     
	

  return 0;
}
