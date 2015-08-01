#pragma once

#include "ofxAbstractDeviceGui.h"
#include "ofxSelectSlider.h"

//TODO
/*
 * onUpdate needed? how to make it thread safe otherwise?
 * try to use same sampleRate after device changed
 * reload device list
 * disabled events for labels?
 */

class ofxSoundStreamGui : public ofxAbstractDeviceGui {
public:
	ofxSoundStreamGui();
	virtual ~ofxSoundStreamGui();

	ofxGuiGroup * setup(std::string name, ofSoundStream * stream, ofBaseApp * app = NULL);

	virtual void update(); //TODO or no update at all?
protected:
	ofxSelectSlider deviceID,sampleRateIdx,bufferSizeIdx;
	ofParameter<int> outputChannels,inputChannels,nBuffers;
//	ofParameter<bool> eListDevices;

	ofSoundStream * stream;

	vector<ofSoundDevice> devices;
	vector<unsigned int> sampleRates;

	bool eDeviceChanged; //TODO-> abstract & virtual =0 handleDeviceChanged?

	virtual void connectSlot(bool & active);

	void paramChanged( int &);
	void updateDeviceId(int &);

//	void reloadDeviceList();
};
