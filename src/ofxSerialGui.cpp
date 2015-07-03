#include "ofxSerialGui.h"

ofxSerialGui::ofxSerialGui()
:serial(NULL){

}

ofxGuiGroup * ofxSerialGui::setup(string name, ofSerial * serial, ofBaseApp * app){
	ofxAbstractDeviceGui::setup(name,app);

	this->serial = serial;

	devices = serial->getDeviceList();

	gui.add(deviceID.set("deviceId",0,0,devices.size()-1));
	gui.add(deviceLabel.set("device",""));

	//TOOD NEXT baudrates!!!

	return &gui;
}

void ofxSerialGui::update(){

}

void ofxSerialGui::connectSlot(bool & active){

}
