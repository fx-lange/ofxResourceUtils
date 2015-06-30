#pragma once

#include "ofMain.h"
#include "ofxGui.h"

//TODO
/*
 * onUpdate needed? how to make it thread safe otherwise?
 * try to use same sampleRate after device changed
 * reload device list
 * disabled events for labels?
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

	ofSoundStream * stream;
	ofBaseApp * app;
	vector<ofSoundDevice> devices;
	vector<unsigned int> sampleRates;

	bool eDeviceChanged, bOnStart;

	void connect();
	void connectSlot(bool & active);
	void disconnect();

	void updateLabels(int &);
	void paramChanged( int &);
	void updateDeviceId(int &);
//	void parameterChanged( ofAbstractParameter & parameter );

	void reloadDeviceList();
};
