#include "ofxSoundStreamGui.h"

ofxSoundStreamGui::ofxSoundStreamGui()
:stream(NULL),app(NULL){
	eDeviceChanged = true;
	bOnStart = true;
}

ofxSoundStreamGui::~ofxSoundStreamGui() {}

ofxGuiGroup * ofxSoundStreamGui::setup(std::string name, ofSoundStream * stream, ofBaseApp * app){
	this->stream = stream;
	if(app != NULL){
		this->app = app;
	}else{
		this->app = ofGetAppPtr();
	}

	devices = stream->getDeviceList();

	gui.setup(name);

	gui.add(bConnectOnStart.set("connectOnStart",false));

	gui.add(deviceID.set("deviceId",0,0,devices.size()-1));
	gui.add(deviceLabel.set("device",""));

	gui.add(bufferSizeIdx.set("bufferSizeExp",8,8,12));
	gui.add(bufferSizeLabel.set("bufferSize","256"));

	gui.add(sampleRateIdx.set("sampleRateIdx",0,0,0));
	gui.add(sampleRateLabel.set("sampleRate",""));

	gui.add(outputChannels.set("outputChannels",0,0,8));
	gui.add(inputChannels.set("inputChannels",0,0,8));
	gui.add(nBuffers.set("nBuffers",4,1,8));

	gui.add(bConnect.set("setup",false));
	gui.add(status.set("status","close"));

	//id -> deviceLabel && sampleRateList => sampleRateMax&sampleRateIdx (on update)
	deviceID.addListener(this,&ofxSoundStreamGui::updateDeviceId);

	//bufferSizeIdx -> bufferSizeLabel (instant)
	//sampleRateIdx -> sampleRateLabel (instant)
	bufferSizeIdx.addListener(this,&ofxSoundStreamGui::updateLabels);
	sampleRateIdx.addListener(this,&ofxSoundStreamGui::updateLabels);
	//param change -> disconnect
	outputChannels.addListener(this,&ofxSoundStreamGui::paramChanged);
	inputChannels.addListener(this,&ofxSoundStreamGui::paramChanged);
	nBuffers.addListener(this,&ofxSoundStreamGui::paramChanged);

	//connect -> open/fail (instant)
	bConnect.addListener(this,&ofxSoundStreamGui::connectSlot);

	//connection status & labels shouldn't be stored
	bConnect.setSerializable(false);
	status.setSerializable(false);
	sampleRateLabel.setSerializable(false);
	bufferSizeLabel.setSerializable(false);
	deviceLabel.setSerializable(false);

//	ofAddListener(((ofParameterGroup&)gui.getParameter()).parameterChangedE,this,&ofxSoundStreamGui::parameterChanged);

	return &gui;
}

bool ofxSoundStreamGui::update(){
	if(eDeviceChanged){
		deviceLabel = devices[deviceID].name;
		sampleRates = devices[deviceID].sampleRates;
		sampleRateIdx.setMax(sampleRates.size()-1);
		sampleRateIdx = min((int)sampleRateIdx,sampleRateIdx.getMax());

		eDeviceChanged = false;

		return true;
	}else if(bOnStart){
		bOnStart = false;
		if(bConnectOnStart){
			connect();
		}
	}

	return false;
}

void ofxSoundStreamGui::connect(){
	bConnect.set(true); //triggers connectSlot(true)
}

void ofxSoundStreamGui::connectSlot(bool & active){
	if(active){
		stream->setDeviceID(deviceID);
		int sampleRate = sampleRates[sampleRateIdx];
		int bufferSize = pow(2,(int)bufferSizeIdx);

		bool result = stream->setup(app,outputChannels,inputChannels,sampleRate,bufferSize,nBuffers);

		if(result){
			status = "open";
		}else{
			disconnect();
		}
	}else{
		status = "close";
		stream->close();
	}
}

void ofxSoundStreamGui::disconnect(){
	bConnect.set(false); //triggers connectSlot(false);
}

void ofxSoundStreamGui::paramChanged( int &){
	disconnect();
}

void ofxSoundStreamGui::updateLabels(int &){
	bufferSizeLabel = ofToString(pow(2,(int)bufferSizeIdx));
	if(sampleRateIdx < (int)sampleRates.size()){
		sampleRateLabel = ofToString(sampleRates[sampleRateIdx]);
	}
	disconnect();
}

void ofxSoundStreamGui::updateDeviceId(int &){
	eDeviceChanged = true; //... more on update
	disconnect();
}

//void ofxSoundStreamGui::parameterChanged( ofAbstractParameter & parameter ){
//	ofLogNotice("ofxSoundStreamGui::parameterChanged");
//	disconnect();
//}

void ofxSoundStreamGui::reloadDeviceList(){
	devices = stream->getDeviceList();
	//TODO not fully implemented yet
}
