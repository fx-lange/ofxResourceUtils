#include "ofxFontResource.h"

ofxGuiGroup * ofxFontResource::setup(const string & name, const string path){
	ofTrueTypeFont * font = new ofTrueTypeFont();
	return setup(name,font,path);
}

ofxGuiGroup * ofxFontResource::setup(const string & name, ofTrueTypeFont * font, const string path){
	ebParamChanged = false;
	bUpdateUsed = false;

	this->fontPtr = font;

	//check if path is a non empty directory or one specific font
	ofDirectory dir = ofDirectory(path);
	if(dir.isDirectory()){
		dir.allowExt("ttf"); //TODO what else?
		dir.sort();
		fontFiles = dir.getFiles();

		if(!fontFiles.empty()){
			isDir = true;
			ofLogVerbose("ofxFontResource::setup") << "setup font resource with directory: " << path;
		}else{
			isDir = false;
			ofLogError("ofxFontResource::setup") << "setup font resource with empty directory: " << path;
		}
	}else{
		isDir = false;
		filename.setName("font");
		filename = path;
		ofLogVerbose("ofxFontResource::setup") << "setup font resource with font: " << filename;
	}

	guiGroup.setup(name);

	if(isDir){
		std::vector<string> labels;
		for(int i=0;i<(int)fontFiles.size();++i){
			labels.push_back(fontFiles[i].getBaseName());
		}
		guiGroup.add(fontSelector.setup("font",0,labels));
		filename = fontFiles[0].getAbsolutePath();
	}else{
		guiGroup.add(filename);
	}

	guiGroup.add(fontSize.set("fontSize",14,8,70)); //TODO min&max
	guiGroup.add(bAnitAliased.set("antiAliased",true));
	guiGroup.add(bFullCharacterSet.set("fullCharacterSet",true));
	guiGroup.add(bMakeContour.set("makeContour",false));
	guiGroup.add(simplifyAmt.set("simplyfyAmt",0.3,0.001,100)); //TODO min&max?
	guiGroup.add(dpi.set("dpi",0,0,500));
	guiGroup.add(bEventReload.set("eventReload",true));

	ofParameterGroup & paramGroup = (ofParameterGroup&)guiGroup.getParameter();
	ofAddListener(paramGroup.parameterChangedE(),this,&ofxFontResource::paramChanged);

	reloadFont();

	return &guiGroup;
}

ofTrueTypeFont * ofxFontResource::getFont(){
	return fontPtr;
}

void ofxFontResource::update(){
	bUpdateUsed = true;
	if(ebParamChanged){
		reloadFont();
	}
}

void ofxFontResource::paramChanged(ofAbstractParameter &){
	ebParamChanged = true;
	if(bEventReload){
		reloadFont();
	}else{
		if(!bUpdateUsed)
			ofLogWarning("ofxFontResource::paramChanged") << "font not reloading! activate eventReload or integrate ofxFontResource::update";
	}
}

void ofxFontResource::reloadFont(){
	ebParamChanged = false;
	if(isDir){
		filename = fontFiles[fontSelector].getAbsolutePath();
	}
	fontPtr->load(filename,fontSize,bAnitAliased,bFullCharacterSet,bMakeContour,simplifyAmt,dpi);
	ofNotifyEvent(fontRebuildEvent);
}

