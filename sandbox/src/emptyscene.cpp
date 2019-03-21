//
// Created by FLXR on 3/21/2019.
//

#include "emptyscene.hpp"

using namespace xe;

EmptyScene::EmptyScene() {

}

EmptyScene::~EmptyScene() {

}

void EmptyScene::render() {

}

void EmptyScene::renderImGui() {

}

void EmptyScene::update(float delta) {

}

void EmptyScene::input(Event &event) {
	if (event.key.code == Keyboard::Escape) {
		Application::exit();
	}
}
