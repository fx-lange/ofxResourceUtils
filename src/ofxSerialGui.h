#pragma once

#include "ofxAbstractDeviceGui.h"

class ofxSerialGui : public ofxAbstractDeviceGui {
public:
	ofxSerialGui();
	virtual ~ofxSerialGui(){}

	ofxGuiGroup * setup(std::string name, ofSerial * serial, ofBaseApp * app = NULL);

	virtual void update();
protected:
	ofParameter<int> deviceID, baudrateIdx;
	ofParameter<string> deviceLabel, baudrateLabel;

	ofSerial * serial;

	vector<ofSerialDeviceInfo> devices;

	virtual void connectSlot(bool & active);
};
