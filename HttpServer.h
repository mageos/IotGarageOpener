#ifndef HttpServer_h
#define HttpServer_h

#include <ESP8266WebServer.h>

#include "Scheduler.h"
#include "Led.h"

typedef void (*CallBack)();

class WebServer : public Runable
{
public:
    WebServer();

    void initialize(const CallBack toggleCallback);

    void run();

private:
    ESP8266WebServer _server = {80};
    CallBack _toggleCallback;

    //Led _led;
    void onToggleRequest();
    void onStatusRequest();
    void defaultRequestHandler();
    bool serverFile(String path);
    String getContentType(const String& filename);
};

#endif