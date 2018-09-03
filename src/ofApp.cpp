#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    gui.setup("SETTINGS", "settings.xml", 0, 0	);
    
    gui.add(bellDurTime.setup("BELL_DUR", 0.1, 0, 1.0));
    bellDurTime.addListener(this, &ofApp::onBellDurChanged);
    gui.add(knockDurTime.setup("KNOCK_DUR", 0.1, 0, 1.0));
    knockDurTime.addListener(this, &ofApp::onKnockDurChanged);
    
    gui.add(lampDurTime.setup("LAMP_DUR", 0.5, 0, 5.0));
    lampDurTime.addListener(this, &ofApp::onLampDurChanged);
    gui.add(lampR.setup("LAMP_R", 0, 0, 255));
    lampR.addListener(this, &ofApp::onLampChanged);
    gui.add(lampG.setup("LAMP_G", 100, 0, 255));
    lampG.addListener(this, &ofApp::onLampChanged);
    gui.add(lampB.setup("LAMP_B", 0, 0, 255));
    lampB.addListener(this, &ofApp::onLampChanged);

    gui.add(brightDurTime.setup("BRIGHT_DUR", 0.5, 0, 5.0));
    brightDurTime.addListener(this, &ofApp::onBrightDurChanged);
    gui.add(brightR.setup("BRIGHT_R", 0, 0, 255));
    brightR.addListener(this, &ofApp::onBrightChanged);
    gui.add(brightG.setup("BRIGHT_G", 255, 0, 255));
    brightG.addListener(this, &ofApp::onBrightChanged);
    gui.add(brightB.setup("BRIGHT_B", 0, 0, 255));
    brightB.addListener(this, &ofApp::onBrightChanged);
    
    gui.loadFromFile("settings.xml");
    

    networkSettings.loadFile("network_settings.xml");
    string ip = networkSettings.getValue("network:ip", "192.168.0.100");
    int port  = networkSettings.getValue("network:port", 12345);
    cout << "Send To: " << ip << "(" << port << ")" << endl;
    sender.setup(ip, port);
    
    //serial.setup("COM6", 115200);


    float btnSize = ofGetHeight();
    
    bellBtn.setup(btnSize * 0, 0, btnSize, btnSize, "bell_on.png", "bell_off.png");
    knockBtn.setup(btnSize * 1, 0, btnSize, btnSize, "knock_on.png", "knock_off.png");
    lampBtn.setup(btnSize * 2, 0, btnSize, btnSize, "lamp_on.png", "lamp_off.png");
    brightBtn.setup(btnSize * 3, 0, btnSize, btnSize, "bright_on.png", "bright_off.png");

    
    bellAction.durTime = bellDurTime;
    bellAction.startFunc = [&]() {
        cout << "Bell ON" << endl;
        setBell(true);
    };
    bellAction.finishFunc = [&]() {
        cout << "Bell OFF" << endl;
        setBell(false);
        bellBtn.turnOFF();
    };
    
    knockAction.durTime = knockDurTime;
    knockAction.startFunc = [&]() {
        cout << "Knock ON" << endl;
        setKnock(true);
    };
    knockAction.finishFunc = [&]() {
        cout << "Knock OFF" << endl;
        setKnock(false);
        knockBtn.turnOFF();
    };
    
    lampOnAction.durTime = lampDurTime;
    lampOnAction.durFunc = [&](float ratio) {
        cout << "Lamp ON:" << ratio << endl;
        setLamp(lampR, lampG, lampB, ratio);
    };

    lampOffAction.durTime = lampDurTime;
    lampOffAction.durFunc = [&](float ratio) {
        cout << "Lamp OFF:" << ratio << endl;
        setLamp(lampR, lampG, lampB, 1.0 - ratio);
    };

    brightOnAction.durTime = brightDurTime;
    brightOnAction.durFunc = [&](float ratio) {
        cout << "Bright ON:" << ratio << endl;
        setBright(brightR, brightG, brightB, ratio);
    };
    
    brightOffAction.durTime = brightDurTime;
    brightOffAction.durFunc = [&](float ratio) {
        cout << "Bright OFF:" << ratio << endl;
        setBright(brightR, brightG, brightB, 1.0 - ratio);
    };
}

//--------------------------------------------------------------
void ofApp::update(){
	/*
	while (serial.available()) {
		char c = serial.readByte();
		cout << c;
	}
	*/
    
    bellAction.update();
    knockAction.update();
    lampOnAction.update();
    lampOffAction.update();
    brightOnAction.update();
    brightOffAction.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    bellBtn.draw();
    knockBtn.draw();
    lampBtn.draw();
    brightBtn.draw();
    
    if (guiIsVisible) gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
        case '1':
            bellAction.start();
            bellBtn.turnON();
            break;

        case '2':
            knockAction.start();
            knockBtn.turnON();
            break;
        
        case '3':
            if (!lampBtn.isON) {
                lampOnAction.start();
                lampBtn.turnON();
            } else {
                lampOffAction.start();
                lampBtn.turnOFF();
            }
            break;
            
        case '4':
            if (!brightBtn.isON) {
                brightOnAction.start();
                brightBtn.turnON();
            } else {
                brightOffAction.start();
                brightBtn.turnOFF();
            }
            break;
            
        case 'd':
            guiIsVisible = !guiIsVisible;
            break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    bellBtn.onMousePressed(x, y, [&]() { bellAction.start(); });
    knockBtn.onMousePressed(x, y, [&]() { knockAction.start(); });
    lampBtn.onMousePressed(x, y, [&]() { lampOnAction.start(); }, [&]() { lampOffAction.start(); });
    brightBtn.onMousePressed(x, y, [&]() { brightOnAction.start(); }, [&]() { brightOffAction.start(); });
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
