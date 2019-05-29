#include <FS.h>
#include "HttpServer.h"
#include "Led.h"

WebServer::WebServer()
{  
}

void WebServer::initialize(const CallBack toggleCallback)
{
  _server.on("/toggle", [=]() {this->onToggleRequest();});
  _server.on("/status", [=]() {this->onStatusRequest();});
  _server.onNotFound([=]() {this->defaultRequestHandler();});

  _server.begin();
  
   

  _toggleCallback = toggleCallback;
}

void WebServer::run()
{
  _server.handleClient();
}

void WebServer::onToggleRequest()
{  
  _server.send(200, "application/json", "{'data': 'recieved'}");

  _toggleCallback();
}

void WebServer::onStatusRequest()
{
  String statusMessage( 
  String("{") +
  String("   'ledStatus': '") + true + String("'") +
  String("}"));

  _server.send(200, "application/json", statusMessage);  
}

void WebServer::defaultRequestHandler()
{  
  if (!serverFile(_server.uri()))
  {
      _server.send(404, "text/plain", "index.html could not be found");
      //_led.blink(125,4);
  }
}

bool WebServer::serverFile(String path)
{
  if (path.endsWith("/")) 
  {
    path += "index.html";
  }

  if (path.startsWith("/priv") || !SPIFFS.exists(path))
  {
      return false;
  }
  
  File file = SPIFFS.open(path, "r");
  _server.streamFile(file, getContentType(file.name()));
  file.close();

  return true;
}

String WebServer::getContentType(const String& filename) 
{
  if (_server.hasArg("download")) {
    return "application/octet-stream";
  } else if (filename.endsWith(".htm")) {
    return "text/html";
  } else if (filename.endsWith(".html")) {
    return "text/html";
  } else if (filename.endsWith(".css")) {
    return "text/css";
  } else if (filename.endsWith(".js")) {
    return "application/javascript";
  } else if (filename.endsWith(".png")) {
    return "image/png";
  } else if (filename.endsWith(".gif")) {
    return "image/gif";
  } else if (filename.endsWith(".jpg")) {
    return "image/jpeg";
  } else if (filename.endsWith(".ico")) {
    return "image/x-icon";
  } else if (filename.endsWith(".xml")) {
    return "text/xml";
  } else if (filename.endsWith(".pdf")) {
    return "application/x-pdf";
  } else if (filename.endsWith(".zip")) {
    return "application/x-zip";
  } else if (filename.endsWith(".gz")) {
    return "application/x-gzip";
  }
  return "text/plain";
}