#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxGui.h"
#include "ofxXmlSettings.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void setBell(bool isON) {
            ofxOscMessage msg;
            msg.setAddress("/fairydoor/sole");
            msg.addInt32Arg(0);
            msg.addInt32Arg(isON ? 1 : 0);
            sender.sendMessage(msg, false);
        }
    
        void setKnock(bool isON) {
            ofxOscMessage msg;
            msg.setAddress("/fairydoor/sole");
            msg.addInt32Arg(1);
            msg.addInt32Arg(isON ? 1 : 0);
            sender.sendMessage(msg, false);
        }
    
        void setLamp(int r, int g, int b, float ratio) {
            ofxOscMessage msg;
            msg.setAddress("/fairydoor/lamp");
            msg.addInt32Arg(r * ratio);
            msg.addInt32Arg(g * ratio);
            msg.addInt32Arg(b * ratio);
            sender.sendMessage(msg, false);
        }

        void setBright(int r, int g, int b, float ratio) {
            ofxOscMessage msg;
            msg.setAddress("/fairydoor/bright");
            msg.addInt32Arg(r * ratio);
            msg.addInt32Arg(g * ratio);
            msg.addInt32Arg(b * ratio);
            sender.sendMessage(msg, false);
        }
    
        void onBellDurChanged(float& val) {
            bellAction.durTime = val;
        }
        
        void onKnockDurChanged(float& val) {
            knockAction.durTime = val;
        }
    
        void onLampDurChanged(float& val) {
            lampOnAction.durTime = val;
            lampOffAction.durTime = val;
        }
        
        void onBrightDurChanged(float& val) {
            brightOnAction.durTime = val;
            brightOffAction.durTime = val;
        }
        
		void onBrightChanged(int& val) {
            if (!brightBtn.isON) return;
            setBright(brightR, brightG, brightB, 1.0);
		}

		void onLampChanged(int& val) {
            if (!lampBtn.isON) return;            
            setLamp(lampR, lampG, lampB, 1.0);
		}

private:
	ofxOscSender sender;
	ofSerial serial;
		
	ofxPanel gui;
    ofxFloatSlider bellDurTime;
    ofxFloatSlider knockDurTime;
    ofxFloatSlider lampDurTime;
	ofxIntSlider lampR;
	ofxIntSlider lampG;
	ofxIntSlider lampB;
    ofxFloatSlider brightDurTime;
    ofxIntSlider brightR;
    ofxIntSlider brightG;
    ofxIntSlider brightB;
    bool guiIsVisible = false;
    
    class OriginalButton {
    public:
        ofImage onImg;
        ofImage offImg;
        ofRectangle rect;
        bool isON = false;
        
        void setup(float x, float y, float w, float h, string onImgPath, string offImgPath) {
            rect.set(x, y, w, h);
            onImg.load(onImgPath);
            offImg.load(offImgPath);
        }
        
        void turnON() {
            isON = true;
        }
        
        void turnOFF() {
            isON = false;
        }
        
        void onMousePressed(float x, float y, function<void(void)> onCallback = nullptr, function<void(void)> offCallback = nullptr) {
            if (!rect.inside(x, y)) return;
            
            isON = !isON;
            if (isON) {
                if (onCallback) onCallback();
            } else {
                if (offCallback) offCallback();
            }
        }
        
        void draw() {
            if (isON) {
                onImg.draw(rect);
            } else {
                offImg.draw(rect);
            }
        }
    };
    
    OriginalButton bellBtn;
    OriginalButton knockBtn;
    OriginalButton lampBtn;
    OriginalButton brightBtn;

    class OneAction {
    public:
        float durTime = 0;
        function<void()> startFunc = nullptr;
        function<void()> finishFunc = nullptr;
        function<void(float)> durFunc = nullptr;
        float onTime = 0;
        bool isON = false;
        
        void start() {
            onTime = ofGetElapsedTimef();
            isON = true;
            if (startFunc) startFunc();
            if (durFunc) durFunc(0.0);
        }
        
        void update() {
            if (!isON) return;
            
            float ratio = ofMap(ofGetElapsedTimef(), onTime, onTime + durTime, 0.0, 1.0, false);
            if (ratio < 1.0) {
                if (durFunc) durFunc(ratio);
            } else {
                if (durFunc) durFunc(1.0);
                if (finishFunc) finishFunc();
                isON = false;
            }
        }
    };
    
    OneAction bellAction;
    OneAction knockAction;
    OneAction lampOnAction;
    OneAction lampOffAction;
    OneAction brightOnAction;
    OneAction brightOffAction;
    
    ofxXmlSettings networkSettings;
};

