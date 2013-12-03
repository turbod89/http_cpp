#include "chatConnection.h"

size_t __curl_write_data_to_stringstream(char *ptr, size_t size, size_t nmemb, void *userdata) {
  
  std::ostringstream *stream = (std::ostringstream*)userdata; 
  size_t count = size * nmemb; 
  stream->write(ptr, count); 
  return count; 
  
}


bool chatConnection::getResponse(const string& url, stringstream& canal) {
 
  this->curl = curl_easy_init();
  
  if (this->curl) {
	  
    curl_easy_setopt(this->curl, CURLOPT_URL, (this->server+url).c_str());
    curl_easy_setopt(this->curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
    curl_easy_setopt(this->curl, CURLOPT_USERPWD, (this->user+":"+this->password).c_str());
    curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, &__curl_write_data_to_stringstream); 
    curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, &canal);
 
    
    this->response = curl_easy_perform(this->curl);
    
    if(this->response != CURLE_OK)
      return false;
    
    curl_easy_cleanup(this->curl);
    
  } else
    return false;
  
  return true;

}

chatConnection::chatConnection() {
  this->server = "";
  this->user = "";
  this->password = "";
}

chatConnection::chatConnection(const string& server){
  this->server = server;
  this->user = "";
  this->password = "";
}

chatConnection::chatConnection(const string& server, const string& user, const string& password) {
  
  this->server = server;
  this->user = user;
  this->password = password;
  
}

void chatConnection::setServer(const string& server){
  this->server = server;
}
void chatConnection::setUser(const string& user){
  this->user = user;
}
void chatConnection::setPassword(const string& password){
  this->password = password;
}

string chatConnection::getServer() const{
  return this->server;
}

string chatConnection::getUser() const{
  return this->user;
}

string chatConnection::getPassword() const{
  return this->password;
}



string chatConnection::error() const {
  return this->lastError;
}

//
//  Concrete requests  
//


bool chatConnection::checkLogin(){
 
  stringstream canal;
  if (!this->getResponse("accounts.php?action=checkLogin",canal)) 
    return false;
  
  bool error, res;
  
  canal >> error;
  
  if (error) {
	canal >> this->lastError;
    return false;
  }
  this->lastError = "";
  canal >> res;
  return res;
}


bool chatConnection::signIn(){
 
  stringstream canal;
  if (!this->getResponse("accounts.php?action=signIn",canal)) 
    return false;
  
  bool error, res;
  
  canal >> error;
  
  if (error) {
	canal >> this->lastError;
    return false;
  }
  this->lastError = "";
  canal >> res;
  return res;
}

bool chatConnection::newChat(const string& name) {

  stringstream canal;
  if (!this->getResponse("chats.php?action=newChat&name="+name,canal)) 
    return false;
  
  bool error, res;
  
  canal >> error;
  
  if (error) {
	canal >> this->lastError;
    return false;
  }

  this->lastError = "";

  return true;
}
