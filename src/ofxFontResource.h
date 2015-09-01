#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxSelectSlider.h"

//TODO simple vs. extended vs. ... version

class ofxFontResource {
public:

	ofxGuiGroup * setup(const string & name, ofTrueTypeFont * font, string path = "");

	ofEvent<void> fontRebuildEvent;
protected:
	ofxGuiGroup guiGroup;

	bool isDir;
	vector<ofFile> fontFiles;

	ofParameter<string> filename;
	ofParameter<int> fontSize, dpi;
	ofParameter<bool> bAnitAliased, bFullCharacterSet, bMakeContour;
	ofParameter<float> simplifyAmt;

	ofxSelectSlider fontSelector;

	//TODO line height? spacing?

	ofTrueTypeFont * fontPtr;

	void reloadFont();
	void paramChanged(ofAbstractParameter&);
};
