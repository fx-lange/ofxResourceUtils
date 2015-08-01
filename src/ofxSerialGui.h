#pragma once

#include "ofxAbstractDeviceGui.h"
#include "ofxSelectSlider.h"

class ofxSerialGui : public ofxAbstractDeviceGui {
public:
	ofxSerialGui();
	virtual ~ofxSerialGui(){}

	ofxGuiGroup * setup(std::string name, ofSerial * serial, ofBaseApp * app = NULL);

	virtual void update();
protected:
	ofxSelectSlider baudrateSelect, deviceID;

	ofSerial * serial;

	vector<ofSerialDeviceInfo> devices;

	virtual void connectSlot(bool & active);

	void paramChanged( int &);
};
