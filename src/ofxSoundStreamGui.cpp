#include "ofxSoundStreamGui.h"

ofxSoundStreamGui::ofxSoundStreamGui()
:stream(NULL),app(NULL){
	eDeviceChanged = true;
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

	//connect -> open/fail
	bConnect.addListener(this,&ofxSoundStreamGui::connect);

	//connection status & labels shouldn't be stored
	bConnect.setSerializable(false);
	status.setSerializable(false);
	sampleRateLabel.setSerializable(false);
	bufferSizeLabel.setSerializable(false);
	deviceLabel.setSerializable(false);

	return &gui;
}

void ofxSoundStreamGui::connect(bool & active){
	if(active){
		stream->setDeviceID(deviceID);
		int sampleRate = sampleRates[sampleRateIdx];
		int bufferSize = pow(2,(int)bufferSizeIdx);

		bool result = stream->setup(app,outputChannels,inputChannels,sampleRate,bufferSize,nBuffers);

		if(result){
			status = "open";
		}else{
			bConnect.set(false);
		}
	}else{
		stream->close();
		status = "close";
	}
}

bool ofxSoundStreamGui::update(){
	//disconnect and toggle off on update (deviceId || settings)

	if(eDeviceChanged){
		deviceLabel = devices[deviceID].name;
		sampleRates = devices[deviceID].sampleRates;
		sampleRateIdx.setMax(sampleRates.size()-1);
		sampleRateIdx = min((int)sampleRateIdx,sampleRateIdx.getMax());

		eDeviceChanged = false;

		return true;
	}

	return false;
}

void ofxSoundStreamGui::updateLabels(int &){
	bufferSizeLabel = ofToString(pow(2,(int)bufferSizeIdx));
	if(sampleRateIdx < (int)sampleRates.size()){
		sampleRateLabel = ofToString(sampleRates[sampleRateIdx]);
	}
}

void ofxSoundStreamGui::updateDeviceId(int &){
	eDeviceChanged = true;
}

void ofxSoundStreamGui::reloadDeviceList(){
	devices = stream->getDeviceList();

	//TODO set deviceID max
}
