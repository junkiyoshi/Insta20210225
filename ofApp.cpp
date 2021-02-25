#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(3);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	auto n = 9;
	for (int x = 140; x <= 720; x += 220) {

		for (int y = 140; y <= 720; y += 220) {

			ofPushMatrix();
			ofTranslate(x, y);

			auto radius = 80;
			auto deg_start = 0;
			auto deg_end = deg_start + 180;
			auto deg_span = 10;
			for (int deg = deg_start; deg < deg_end; deg += deg_span) {

				auto center = glm::vec2(radius * cos((deg + deg_span / 2) * DEG_TO_RAD), 0);
				auto rotate = ofMap(ofNoise(y, x + deg * 0.0035 + ofGetFrameNum() * 0.005), 0, 1, 0, 360);

				ofPushMatrix();
				ofTranslate(center);
				ofRotateX(rotate);

				vector<glm::vec2> vertices_1, vertices_2;
				for (int tmp_deg = deg + 1; tmp_deg < deg + deg_span; tmp_deg++) {

					auto point = glm::vec2(radius * cos(tmp_deg * DEG_TO_RAD), radius * sin(tmp_deg * DEG_TO_RAD));
					vertices_1.push_back(point - center);
					vertices_2.push_back(glm::vec2(point.x, -point.y) - center);
				}

				reverse(vertices_2.begin(), vertices_2.end());

				ofFill();
				ofSetColor(239);
				ofBeginShape();
				ofVertices(vertices_1);
				ofVertices(vertices_2);
				ofEndShape(true);

				ofNoFill();
				ofSetColor(39);
				ofBeginShape();
				ofVertices(vertices_1);
				ofVertices(vertices_2);
				ofEndShape(true);

				ofPopMatrix();
			}

			ofPopMatrix();
			n--;
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}