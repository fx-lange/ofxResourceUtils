#include "ofxSerialGui.h"

int baudrates[12]={300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, 115200};

ofxSerialGui::ofxSerialGui()
:serial(NULL){

}

ofxGuiGroup * ofxSerialGui::setup(string name, ofSerial * serial, ofBaseApp * app){
	ofxAbstractDeviceGui::setup(name,app);

	this->serial = serial;

	devices = serial->getDeviceList();

	gui.add(deviceID.set("deviceId",0,0,devices.size()-1));
	gui.add(deviceLabel.set("device",""));

	gui.add(baudrateIdx.set("baudrateIdx",10,0,11));
	gui.add(baudrateLabel.set("baudrate",""));

	//id -> deviceLabel && disconnect
	deviceID.addListener(this,&ofxSerialGui::paramChanged);

	baudrateIdx.addListener(this,&ofxSerialGui::paramChanged);

	baudrateLabel.setSerializable(false);
	deviceLabel.setSerializable(false);

	return &gui;
}

void ofxSerialGui::update(){
	if(bOnStart){
		bOnStart = false;
		if(bConnectOnStart){
			connect();
		}
	}
}

void ofxSerialGui::connectSlot(bool & active){
	if(active){
		bool result = serial->setup(deviceID,baudrates[baudrateIdx]);
		if(result){
			status = "open";
		}else{
			disconnect();
		}
	}else{
		status = "close";
		serial->close();
	}
}

void ofxSerialGui::paramChanged( int &){
	disconnect();

	baudrateLabel = ofToString(baudrates[baudrateIdx]);
	deviceLabel = devices[deviceID].getDeviceName();
}
