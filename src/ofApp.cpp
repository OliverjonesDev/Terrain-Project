#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
	cam.setPosition(ofVec3f(0, 0, 0));
	cam.setPosition(0, 0, 300);
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.begin();
	light.enable();
	light.setPosition(400, 0, 300);
	ofEnableDepthTest();
	terrain.setup(gui.settings);
	terrain.draw();
	ofDisableDepthTest();
	cam.end();
	gui.draw();
	ofDrawBitmapString("Press S to Save Heightmap to the Bin Folder of this program",20,340);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 's')
		terrain.texture.save("heightmap" +ofGetTimestampString() +".jpeg");
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
