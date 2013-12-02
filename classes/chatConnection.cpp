#include "chatConnection.h"

size_t chatConnection::write_data(char *ptr, size_t size, size_t nmemb, void *userdata) {
  
  std::ostringstream *stream = (std::ostringstream*)userdata; 
  size_t count = size * nmemb; 
  stream->write(ptr, count); 
  return count; 
  
}


bool chatConnection::getResponse(const string& url, stringstream& canal) {

}
