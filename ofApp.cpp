#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();

	auto R = 100.f;
	auto r = 20.f;
	auto u = 0.f;
	auto u_step = 10.f;
	auto v_step = 5.f;

	ofColor color_1, color_2;
	for (int i = 0; i < 36; i++) {

		float angle = (i * 5) * DEG_TO_RAD;
		auto rotation = glm::rotate(glm::mat4(), angle, glm::vec3(0, 0, 1));
		
		color_1.setHsb(ofMap((i + ofGetFrameNum()) % 36, 0, 36, 0, 255), 200, 255);
		color_2.setHsb(ofMap((i + 1 + ofGetFrameNum()) % 36, 0, 36, 0, 255), 200, 255);

		for (auto v = 0; v < 360; v += v_step) {

			this->mesh.addVertex(glm::vec4(this->make_point(R, r, u, v), 0) * rotation);
			this->mesh.addColor(color_2);
			this->mesh.addVertex(glm::vec4(this->make_point(R, r, u + u_step, v + v_step), 0) * rotation);
			this->mesh.addColor(color_2);
			this->mesh.addVertex(glm::vec4(this->make_point(R, r, u, v + v_step), 0) * rotation);
			this->mesh.addColor(color_1);
			this->mesh.addVertex(glm::vec4(this->make_point(R, r, u - u_step, v), 0) * rotation);
			this->mesh.addColor(color_1);

			auto index = this->mesh.getVertices().size() - 1;

			this->mesh.addIndex(index - 3);
			this->mesh.addIndex(index - 2);
			this->mesh.addIndex(index - 1);

			this->mesh.addIndex(index);
			this->mesh.addIndex(index - 3);
			this->mesh.addIndex(index - 1);

			u += u_step;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	
	auto count = 0;
	for (auto x = -300; x <= 300; x += 300) {

		for (auto y = -300; y <= 300; y += 300) {

			ofPushMatrix();
			ofTranslate(x, y);
			ofRotateY(ofGetFrameNum() + count * 90);

			this->mesh.draw();

			ofPopMatrix();

			count++;
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}