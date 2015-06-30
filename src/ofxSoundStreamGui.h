#pragma once

#include "ofMain.h"
#include "ofxGui.h"

//TODO
/*
 * onUpdate needed? how to make it thread safe otherwise?
 * try to use same sampleRate after device changed
 * disconnect & auto connect behavior?
 */

class ofxSoundStreamGui {
public:
	ofxSoundStreamGui();
	virtual ~ofxSoundStreamGui();

	ofxGuiGroup * setup(std::string name, ofSoundStream * stream, ofBaseApp * app = NULL);

	bool update();
protected:
	ofxGuiGroup gui;

	ofParameter<int> deviceID,sampleRateIdx,bufferSizeIdx;
	ofParameter<string> deviceLabel, sampleRateLabel, bufferSizeLabel, status;
	ofParameter<int> outputChannels,inputChannels,nBuffers;
	ofParameter<bool> bConnect,bConnectOnStart,eListDevices;

	ofBaseApp * app;
	ofSoundStream * stream;
	vector<ofSoundDevice> devices;
	vector<unsigned int> sampleRates;

	bool eDeviceChanged;

	void connect(bool & active);

	void updateLabels(int &);
	void updateDeviceId(int &);

	void reloadDeviceList();
};
