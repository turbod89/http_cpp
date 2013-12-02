#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <curl/curl.h>

using namespace std;


void displayArguments() {
  cout << endl;
  cout << endl;
  cout << "Arguments: " << endl;
  cout << "  -> " << "configure" << endl;
  cout << "  -> " << "login" << endl;
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

bool checkLogin(const string& server,const string& user,const string& password) {
    
  CURL *curl;
  CURLcode res;
 
  curl = curl_easy_init();
  
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, (server+"accounts.php?action=checkLogin").c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
    curl_easy_setopt(curl, CURLOPT_USERPWD, (user+":"+password).c_str());
 
    //* Perform the request, res will get the return code */ 
    res = curl_easy_perform(curl);
    
    //* Check for errors */ 
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
 
    //* always cleanup */ 
    curl_easy_cleanup(curl);
    
  }
  
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
        if (configureWrite(server,user,password))
          cout << "Server url set to: " << server << endl;
        else
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
	
	checkLogin(server,user,password);
	
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
