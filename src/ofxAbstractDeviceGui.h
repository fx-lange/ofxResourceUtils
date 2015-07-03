#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofxAbstractDeviceGui {
public:
	ofxAbstractDeviceGui();
	virtual ~ofxAbstractDeviceGui(){}

	virtual void update() = 0;
protected:
	ofxGuiGroup gui; //TODO is-a or has-a relation?

	ofParameter<bool> bConnect,bConnectOnStart;
	ofParameter<string> status;
	bool bOnStart;

	ofBaseApp * app;
	virtual void setup(std::string name, ofBaseApp * app);

	virtual void connect();
	virtual void connectSlot(bool & active) = 0;
	virtual void disconnect();
};
