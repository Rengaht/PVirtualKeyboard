#pragma once

#include "ofMain.h"
#include "PKeyboard.h"
#include "PTextInput.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		
		void onInputUpdate(string& str_);

		//string _text;
		PTextInput* _textinput;
		PKeyboard* _keyboard;
};
