/*
 *  Class: chatConnection
 *  Author: Daniel Torres
 *  Filename: chatConnection.h
 * 
 * 
 * 
 *  Notes: 
 * 
 *
 */

#ifndef H_CHATCONNECTION
#define H_CHATCONNECTION

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <curl/curl.h>

using namespace std;

class chatConnection {

  private:

    string user;
    string password;
    string server;
    
    string lastError;
    
    CURL *curl;
    CURLcode response;
    
    //size_t write_data(char *ptr, size_t size, size_t nmemb, void *userdata);

    bool getResponse(const string& s, stringstream& canal);
    
  public:
  
    chatConnection();
    chatConnection(const string& server);
    chatConnection(const string& server, const string& user, const string& password);
  
    void setServer(const string& server);
    void setUser(const string& user);
    void setPassword(const string& password);
    
    string error() const;
    
    bool checkLogin();
    bool signIn();
    bool newChat(const string& name);
    

};

#endif
