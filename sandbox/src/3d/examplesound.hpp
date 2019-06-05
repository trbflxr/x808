//
// Created by FLXR on 6/4/2019.
//

#ifndef X808_EXAMPLESOUND_HPP
#define X808_EXAMPLESOUND_HPP


#include "iexamplelayer.hpp"
#include "dummyplayer.hpp"
#include "examplescene.hpp"
#include <xe/gfx/deferredrenderer.hpp>
#include <xe/audio/audiosource.hpp>

class ExampleSound : public IExampleLayer {
public:
	void init() override;

	void render() override;
	void renderImGui() override;

	void update(float delta) override;
	void fixedUpdate(float delta) override;

	void input(xe::Event &event) override;

	IEXAMPLE_LAYER_METHODS(ExampleSound)

protected:
	explicit ExampleSound();
	~ExampleSound() override;

private:
	static ExampleSound *instance;

	xe::Camera *camera;
	DummyPlayer *player;

	ExampleScene *exampleScene;
	xe::Scene *scene;
	xe::DeferredRenderer *renderer;

	xe::AudioSource *as0;
};


#endif //X808_EXAMPLESOUND_HPP
