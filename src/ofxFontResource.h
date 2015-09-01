#pragma once

#include "ofMain.h"

//TODO add filename as label
//TODO simple vs. extended vs. ... version

class ofxFontResource {
public:

	ofParameterGroup & setup(const string & name, ofTrueTypeFont * font, const string & path);

	ofEvent<void> fontRebuildEvent;
protected:
	ofParameterGroup group;

	ofParameter<string> filename;
	ofParameter<int> fontSize, dpi;
	ofParameter<bool> bAnitAliased, bFullCharacterSet, bMakeContour;
	ofParameter<float> simplifyAmt;
	//TODO line height? spacing?

	ofTrueTypeFont * fontPtr;

	void reloadFont();
	void paramChanged(ofAbstractParameter&);
};
