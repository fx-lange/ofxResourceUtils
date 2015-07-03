#include "ofxSoundStreamGui.h"

ofxSoundStreamGui::ofxSoundStreamGui()
:stream(NULL){
	eDeviceChanged = true;
}

ofxSoundStreamGui::~ofxSoundStreamGui() {}

ofxGuiGroup * ofxSoundStreamGui::setup(std::string name, ofSoundStream * stream, ofBaseApp * app){
	ofxAbstractDeviceGui::setup(name,app);

	this->stream = stream;

	devices = stream->getDeviceList();

	gui.add(deviceID.set("deviceId",0,0,devices.size()-1));
	gui.add(deviceLabel.set("device",""));

	gui.add(bufferSizeIdx.set("bufferSizeExp",8,8,12));
	gui.add(bufferSizeLabel.set("bufferSize","256"));

	gui.add(sampleRateIdx.set("sampleRateIdx",0,0,0));
	gui.add(sampleRateLabel.set("sampleRate",""));

	gui.add(outputChannels.set("outputChannels",0,0,8));
	gui.add(inputChannels.set("inputChannels",0,0,8));
	gui.add(nBuffers.set("nBuffers",4,1,8));

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

	sampleRateLabel.setSerializable(false);
	bufferSizeLabel.setSerializable(false);
	deviceLabel.setSerializable(false);

	return &gui;
}

void ofxSoundStreamGui::update(){
	if(eDeviceChanged){
		deviceLabel = devices[deviceID].name;
		sampleRates = devices[deviceID].sampleRates;
		sampleRateIdx.setMax(sampleRates.size()-1);
		sampleRateIdx = min((int)sampleRateIdx,sampleRateIdx.getMax());

		eDeviceChanged = false;

	}else if(bOnStart){
		bOnStart = false;
		if(bConnectOnStart){
			connect();
		}
	}
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

//void ofxSoundStreamGui::reloadDeviceList(){
//	devices = stream->getDeviceList();
//	//TODO not fully implemented yet
//}
