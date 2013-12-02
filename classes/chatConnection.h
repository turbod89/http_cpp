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
    
    CURL *curl;
    CURLcode response;
    
    size_t write_data(char *ptr, size_t size, size_t nmemb, void *userdata);

    bool getResponse(stringstream& canal);
    
  public:
  
    
    

};

#endif
