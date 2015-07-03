#include "ofxAbstractDeviceGui.h"

ofxAbstractDeviceGui::ofxAbstractDeviceGui()
:app(NULL){
	bOnStart = true;
}

void ofxAbstractDeviceGui::setup(string name, ofBaseApp * app){
	if(app != NULL){
		this->app = app;
	}else{
		this->app = ofGetAppPtr();
	}

	gui.setup(name);

	gui.add(status.set("status","close"));
	gui.add(bConnect.set("setup",false));
	gui.add(bConnectOnStart.set("connectOnStart",false));

	//connect -> open/fail (instant)
	bConnect.addListener(this,&ofxAbstractDeviceGui::connectSlot);

	//connection status & labels shouldn't be stored
	bConnect.setSerializable(false);
	status.setSerializable(false);
}

void ofxAbstractDeviceGui::connect(){
	bConnect.set(true); //triggers connectSlot(true)
}

void ofxAbstractDeviceGui::disconnect(){
	bConnect.set(false); //triggers connectSlot(false);
}
