#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	_keyboard=new PKeyboard(ofVec2f(0,0),ofVec2f(ofGetWidth(),ofGetHeight()),12);

	//ofAddListener(_keyboard->_event_input,this,&ofApp::onInputUpdate);
	_textinput=new PTextInput(0,ofGetHeight()-20,24,*_keyboard);
}

//--------------------------------------------------------------
void ofApp::update(){

}

void ofApp::onInputUpdate(string& str_){
//	_text=str_;
}
//--------------------------------------------------------------
void ofApp::draw(){
	ofSetBackgroundColor(0);
	_keyboard->draw();

//	PKey::Font.drawString(_text,0,ofGetHeight()-20);
	_textinput->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch(key){
		case 'l':
			PDatabase::generate();
			break;		
		case 'r':
			_textinput->reset();
			break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}



//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	_keyboard->checkMouse(ofPoint(x,y));
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

