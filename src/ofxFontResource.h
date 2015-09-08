#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxSelectSlider.h"

//TODO simple vs. extended vs. ... version

class ofxFontResource {
public:

	ofxGuiGroup * setup(const string & name, ofTrueTypeFont * font, string path = "");
	void update(); //if event reload is not active you need to handle it via update [important for multi-window setup]

	ofEvent<void> fontRebuildEvent;
protected:
	ofxGuiGroup guiGroup;

	bool isDir;
	vector<ofFile> fontFiles;

	ofParameter<string> filename;
	ofParameter<int> fontSize, dpi;
	ofParameter<bool> bAnitAliased, bFullCharacterSet, bMakeContour;
	ofParameter<float> simplifyAmt;
	ofParameter<bool> bEventReload;

	ofxSelectSlider fontSelector;

	//TODO line height? spacing?

	ofTrueTypeFont * fontPtr;

	bool ebParamChanged;
	void reloadFont();
	void paramChanged(ofAbstractParameter&);

	bool bUpdateUsed; //flag to check correct usage
};
