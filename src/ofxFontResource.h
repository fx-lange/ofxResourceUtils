#pragma once

#include "ofMain.h"

class ofxFontResource {
public:

	ofParameterGroup * setup(string name, ofTrueTypeFont * font,string path);

protected:
	ofParameterGroup group;

	ofParameter<string> filename;
	ofParameter<int> fontSize, dpi;
	ofParameter<bool> bAnitAliased, bFullCharacterSet, bMakeContour;
	ofParameter<float> simplifyAmt;

	ofTrueTypeFont * fontPtr;

	void reloadFont();
	void paramChanged(ofAbstractParameter&);
};
