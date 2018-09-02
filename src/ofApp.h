#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxGui.h"


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

		void onBrightChanged(int& val) {
			cout << "Bright:" << brightR << "," << brightG << "," << brightB << endl;

			ofxOscMessage msg;
			msg.setAddress("/fairydoor/bright");
			msg.addInt32Arg(brightR);
			msg.addInt32Arg(brightG);
			msg.addInt32Arg(brightB);
			sender.sendMessage(msg, false);
		}

		void onLampChanged(int& val) {
			cout << "Lamp:" << lampR << "," << lampG << "," << lampB << endl;

			ofxOscMessage msg;
			msg.setAddress("/fairydoor/lamp");
			msg.addInt32Arg(lampR);
			msg.addInt32Arg(lampG);
			msg.addInt32Arg(lampB);
			sender.sendMessage(msg, false);
		}

private:
	ofxOscSender sender;
	ofSerial serial;
		
	ofxPanel gui;
	ofxIntSlider brightR;
	ofxIntSlider brightG;
	ofxIntSlider brightB;
	ofxIntSlider lampR;
	ofxIntSlider lampG;
	ofxIntSlider lampB;
};
