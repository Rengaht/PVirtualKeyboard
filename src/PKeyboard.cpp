#include "PKeyboard.h"

ofxTrueTypeFontUC PKey::Font;
string PDatabase::db_path="gcin.db";
string PDatabase::cin_path="CnsMPSII107-03_GCIN.cin";		
string PDatabase::table_name="p2c";

void PKeyboard::loadKeyLayout(string layout_file,list<PKey>& key_){
	

	//string layout_file="keylayout_en.xml";
	ofxXmlSettings _param;

	if(_param.loadFile(layout_file)){
		ofLog()<<layout_file<<" loaded!";
	}else{
		ofLog()<<"Unable to load xml check data/ folder";
		return;
	}

	int mline=_param.getNumTags("LINE");		

	float wid=min(_size.x/KEY_PER_LINE,_size.y/mline);
	_size_key=ofVec2f(wid,wid);

	for(int i=0;i<mline;++i){

		float x=_param.getAttribute("LINE","dx",0.0,i)*wid;
		_param.pushTag("LINE",i);
		int mkey=_param.getNumTags("KEY");

		for(int j=0;j<mkey;++j){
			string s=_param.getValue("KEY","",j);
			float w=_param.getAttribute("KEY","wid",1.0,j);

			if(s=="NULL") x+=w*wid;
			else{
				key_.push_back(PKey(s,x+wid*KEY_MARGIN,i*wid+wid*KEY_MARGIN,w*wid-wid*KEY_MARGIN*2,wid-2*wid*KEY_MARGIN));
				//ofLog()<<s;
				x+=w*wid;
			}
		}
		
		_param.popTag();
	}

	
}
PKeyboard::PKeyboard(ofVec2f pos_,ofVec2f size_,int font_size_){

	_pos=pos_;
	_size=size_;
	PKey::Font.loadFont("font/NotoSansCJKtc-Regular.otf",font_size_);

	loadKeyLayout("keylayout_en.xml",_key_en);
	loadKeyLayout("keylayout_en_cap.xml",_key_en_cap);
	loadKeyLayout("keylayout_number.xml",_key_number);

	setLanguage(EN);
}
void PKeyboard::draw(){

	float x=0;
	float y=0;

	for(auto& k:*_key) k.draw();


}
void PKeyboard::checkMouse(ofPoint pt_){
	for(auto& k:*_key){
		if(k.inside(pt_)){
			ofLog()<<k._key;
			//_db.key2CWord(k._key);
			if(k._key=="SPACE"){
				str_+=" ";
				ofNotifyEvent(_event_input,str_);
			}else if(k._key=="BCK"){
				str_=str_.substr(0,str_.size()-1);
				ofNotifyEvent(_event_input,str_);
			}else if(k._key=="&123"){
				setLanguage(NUMBER);
			}else if(k._key=="abc"){
				setLanguage(EN);
			}else if(k._key=="EN"){
			
			}else if(k._key=="SHIFT"){
				if(_language==EN) setLanguage(ENCAP);
				else if(_language==ENCAP) setLanguage(EN);
			}else if(k._key=="ENTER"){
				int k=0;
				ofNotifyEvent(_event_enter,k);
			}else if(k._key=="LEFT"){
				int k=0;
				ofNotifyEvent(_event_left,k);
			}else if(k._key=="RIGHT"){
				int k=0;
				ofNotifyEvent(_event_right,k);
			}else{
				str_+=k._word;
				ofNotifyEvent(_event_input,str_);
			}
		}
	}
}

void PKeyboard::setLanguage(PLANGUAGE set_){
	switch(set_){
		case EN:
			_key=&_key_en;
			break;
		case ENCAP:
			_key=&_key_en_cap;
			break;
		case NUMBER:
			_key=&_key_number;
			break;
	}
	_language=set_;
}