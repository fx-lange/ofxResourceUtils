#include "ofxSerialGui.h"

int baudrates[12]={300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, 115200};

ofxSerialGui::ofxSerialGui()
:serial(NULL){

}

ofxGuiGroup * ofxSerialGui::setup(string name, ofSerial * serial, ofBaseApp * app){
	ofxAbstractDeviceGui::setup(name,app);

	this->serial = serial;

	devices = serial->getDeviceList();

	std::vector<string> deviceNames;
	for(size_t i=0;i<devices.size();++i){
		deviceNames.push_back(devices[i].getDeviceName());
	}
	gui.add(deviceID.setup("device",0,deviceNames));

	std::vector<string> labels;
	for(int i=0;i<12;++i){
		labels.push_back(ofToString(baudrates[i]));
	}
	gui.add(baudrateSelect.setup("baudrate",10,labels));

	//id -> deviceLabel && disconnect
	deviceID.addListener(this,&ofxSerialGui::paramChanged);

	baudrateSelect.addListener(this,&ofxSerialGui::paramChanged);

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
		bool result = serial->setup(deviceID,baudrates[baudrateSelect]);
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
}
