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
	std::vector<string> deviceNames;
	for(size_t i=0;i<devices.size();++i){
		deviceNames.push_back(devices[i].name);
	}
	gui.add(deviceID.setup("device",0,deviceNames));

	std::vector<string> bufferSizeStrings;
	for(size_t i=8;i<=12;++i){
		bufferSizeStrings.push_back(ofToString(pow(2,i)));
	}
	gui.add(bufferSizeIdx.setup("bufferSizeExp",0,bufferSizeStrings));

	std::vector<string> emptyRates;
	emptyRates.push_back("");
	gui.add(sampleRateIdx.setup("sampleRateIdx",0,emptyRates));

	gui.add(outputChannels.set("outputChannels",0,0,8));
	gui.add(inputChannels.set("inputChannels",0,0,8));
	gui.add(nBuffers.set("nBuffers",4,1,8));

	//id -> deviceLabel && sampleRateList => sampleRateMax&sampleRateIdx (on update)
	deviceID.addListener(this,&ofxSoundStreamGui::updateDeviceId);

	//param change -> disconnect
	sampleRateIdx.addListener(this,&ofxSoundStreamGui::paramChanged);
	bufferSizeIdx.addListener(this,&ofxSoundStreamGui::paramChanged);
	outputChannels.addListener(this,&ofxSoundStreamGui::paramChanged);
	inputChannels.addListener(this,&ofxSoundStreamGui::paramChanged);
	nBuffers.addListener(this,&ofxSoundStreamGui::paramChanged);

	return &gui;
}

void ofxSoundStreamGui::update(){
	if(eDeviceChanged){
		sampleRates = devices[deviceID].sampleRates;
		std::vector<string> rateStrings;
		for(size_t i=0;i<sampleRates.size();++i){
			rateStrings.push_back(ofToString(sampleRates[i]));
		}
		sampleRateIdx.setLabels(rateStrings);

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
		int bufferSize = pow(2,(int)bufferSizeIdx+8);

		ofLogNotice("ofxSoundStreamGui") << ofToString(sampleRate);
		ofLogNotice("ofxSoundStreamGui") << ofToString(bufferSize);
		ofLogNotice("ofxSoundStreamGui") << ofToString(nBuffers);

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

void ofxSoundStreamGui::updateDeviceId(int &){
	eDeviceChanged = true; //... more on update
	disconnect();
}

//void ofxSoundStreamGui::reloadDeviceList(){
//	devices = stream->getDeviceList();
//	//TODO not fully implemented yet
//}
