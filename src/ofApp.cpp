#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	sender.setup("192.168.0.18", 12345);

	//serial.setup("COM6", 115200);

	gui.setup();

	gui.add(brightR.setup("BRIGHT_R", 0, 0, 255));
	brightR.addListener(this, &ofApp::onBrightChanged);
	gui.add(brightG.setup("BRIGHT_G", 0, 0, 255));
	brightG.addListener(this, &ofApp::onBrightChanged);
	gui.add(brightB.setup("BRIGHT_B", 0, 0, 255));
	brightB.addListener(this, &ofApp::onBrightChanged);

	gui.add(lampR.setup("LAMP_R", 0, 0, 255));
	lampR.addListener(this, &ofApp::onLampChanged);
	gui.add(lampG.setup("LAMP_G", 0, 0, 255));
	lampG.addListener(this, &ofApp::onLampChanged);
	gui.add(lampB.setup("LAMP_B", 0, 0, 255));
	lampB.addListener(this, &ofApp::onLampChanged);
}

//--------------------------------------------------------------
void ofApp::update(){
	/*
	while (serial.available()) {
		char c = serial.readByte();
		cout << c;
	}
	*/
}

//--------------------------------------------------------------
void ofApp::draw(){
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case '1':
		{
			ofxOscMessage msg;
			msg.setAddress("/fairydoor/sole");
			msg.addInt32Arg(0);
			msg.addInt32Arg(1);
			sender.sendMessage(msg, false);

			//serial.writeBytes("001\n", 4);

			cout << "Send" << endl;
		}
	break;

	case '2':
		{
			ofxOscMessage msg;
			msg.setAddress("/fairydoor/sole");
			msg.addInt32Arg(1);
			msg.addInt32Arg(1);
			sender.sendMessage(msg, false);

			//serial.writeBytes("011\n", 4);

			cout << "Send" << endl;
			break;
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	switch (key) {
	case '1':
		{
			ofxOscMessage msg;
			msg.setAddress("/fairydoor/sole");
			msg.addInt32Arg(0);
			msg.addInt32Arg(0);
			sender.sendMessage(msg, false);

			//serial.writeBytes("000\n", 4);

			cout << "Send" << endl;
		}
		break;

	case '2':
		{
			ofxOscMessage msg;
			msg.setAddress("/fairydoor/sole");
			msg.addInt32Arg(1);
			msg.addInt32Arg(0);
			sender.sendMessage(msg, false);

			//serial.writeBytes("010\n", 4);

			cout << "Send" << endl;
		}
		break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
