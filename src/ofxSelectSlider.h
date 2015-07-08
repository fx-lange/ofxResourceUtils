#pragma once

#include "ofxGui.h"

using namespace std;

class ofxSelectSlider : public ofxIntSlider{
public:
	ofxSelectSlider();
	virtual ~ofxSelectSlider();

	ofxSelectSlider * setup(string sliderName, int _val, vector<string> & _labels);

	void setLabels(vector<string> & _labels);
protected:
	vector<string> labels;

	virtual void generateText();

	//hide normal setups
	virtual ofxIntSlider* setup(ofParameter<int> _val, float width = defaultWidth, float height = defaultHeight){
		return ofxIntSlider::setup(_val,width,height);
	}
	virtual ofxSlider* setup(string sliderName, int _val, int _min, int _max, float width = defaultWidth, float height = defaultHeight){
		return ofxIntSlider::setup(sliderName,_val,_min,_max,width,height);
	}
};
