#include "ofxSelectSlider.h"

ofxSelectSlider::ofxSelectSlider() {}

ofxSelectSlider::~ofxSelectSlider() {}

ofxSelectSlider * ofxSelectSlider::setup(string sliderName, int _val, vector<string> & _labels){
	labels = _labels;
	setup(sliderName,_val,0,labels.size()-1);
	return this;
}

void ofxSelectSlider::setLabels(vector<string> & _labels){
	setMax(_labels.size()-1);
	if(value > getMax()){
		value = getMax();
	}
	labels = _labels;
}

void ofxSelectSlider::generateText(){
	if(value >= labels.size())
		return;
	string valStr = labels[value];
	textMesh = getTextMesh(getName(), b.x + textPadding, b.y + b.height / 2 + 4);
	textMesh.append(getTextMesh(valStr, b.x + b.width - textPadding - getTextBoundingBox(valStr,0,0).width, b.y + b.height / 2 + 4));
}

