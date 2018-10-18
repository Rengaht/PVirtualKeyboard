#pragma once
#ifndef PTEXTINPUT_H
#define PTEXT_INPUT_H

#define CURSOR_SPACE .2
#include "PKeyboard.h"

class PTextInput{
	ofVec2f _pos;
	float _font_size;
	string _str;
	int _cursor;
public:
	ofxTrueTypeFontUC Font;
	PTextInput(){}
	PTextInput(float x,float y,float font_size_,PKeyboard& kb_){
		_pos=ofVec2f(x,y);
		Font.loadFont("font/NotoSansCJKtc-Regular.otf",font_size_);
		_font_size=font_size_;

		ofAddListener(kb_._event_input,this,&PTextInput::onInputUpdate);
		ofAddListener(kb_._event_enter,this,&PTextInput::onKeyEnter);
		ofAddListener(kb_._event_left,this,&PTextInput::onKeyLeft);
		ofAddListener(kb_._event_right,this,&PTextInput::onKeyRight);

	}
	void reset(){
		_str="";
		_cursor=0;
	}
	void draw(){
		ofPushMatrix();
		ofTranslate(_pos);

			if(_str.length()>0){
			Font.drawString(_str.substr(0,_cursor),0,0);
			
			float x=Font.getStringBoundingBox(_str.substr(0,_cursor),0,0).width;
			ofTranslate(x+_font_size*CURSOR_SPACE,0);
			}
			ofDrawLine(0,_font_size*.2,0,-_font_size*1.2);
			
			ofTranslate(_font_size*CURSOR_SPACE,0);
			if(_str.length()>_cursor) Font.drawString(_str.substr(_cursor,_str.length()-_cursor),0,0);
		ofPopMatrix();
	}
	void onInputUpdate(string& set_){
		_str=set_;
		_cursor=set_.size();
	}
	void onKeyEnter(int& e){
		
	}
	void onKeyLeft(int& e){
		_cursor=ofClamp(_cursor-1,0,_str.length());
	}
	void onKeyRight(int& e){
		_cursor=ofClamp(_cursor+1,0,_str.length());
	}



};
#endif