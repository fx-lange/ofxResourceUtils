#include "ofxFontResource.h"

ofParameterGroup & ofxFontResource::setup(const string & name, ofTrueTypeFont * font, const string & path){
	fontPtr = font;
	filename = path;

	group.setName(name);

	group.add(fontSize.set("fontSize",14,8,70)); //TODO min&max
	group.add(bAnitAliased.set("antiAliased",true));
	group.add(bFullCharacterSet.set("fullCharacterSet",true));
	group.add(bMakeContour.set("makeContour",false));
	group.add(simplifyAmt.set("simplyfyAmt",0.3,0.001,100)); //TODO min&max?
	group.add(dpi.set("dpi",0,0,96)); //TODO max?

	ofAddListener(group.parameterChangedE(),this,&ofxFontResource::paramChanged);

	reloadFont();

	return group;
}

void ofxFontResource::paramChanged(ofAbstractParameter &){
	reloadFont();
}

void ofxFontResource::reloadFont(){
	fontPtr->load(filename,fontSize,bAnitAliased,bFullCharacterSet,bMakeContour,simplifyAmt,dpi);
	ofNotifyEvent(fontRebuildEvent);
}

