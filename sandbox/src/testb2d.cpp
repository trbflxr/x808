//
// Created by FLXR on 9/11/2018.
//

#include <xe/resources/texturemanager.hpp>
#include <xe/gfx/renderer.hpp>
#include "testb2d.hpp"

using namespace xe;

TestB2D::TestB2D() {
	const float width = app.getConfig().width;
	const float height = app.getConfig().height;

	TextureParameters params;

	TextureManager::add(new Texture("0", L"assets/textures/enemyspotted.png", params));
	TextureManager::add(new Texture("1", L"assets/textures/jdm.png", params));
	TextureManager::add(new Texture("2", L"assets/textures/star.png", params));
	TextureManager::add(new Texture("3", L"assets/textures/test1.png", params));
	TextureManager::add(new Texture("4", L"assets/textures/test6.png", params));
	TextureManager::add(new Texture("5", L"assets/textures/test8.png", params));

	params.wrap = TextureWrap::Repeat;
	TextureManager::add(new Texture("6", L"assets/textures/sp0.png", params));


	//create camera
	camera = new Camera(mat4::ortho(0, width, 0, height, -1, 1000));

	renderer = new BatchRenderer2D(width, height, camera);

	world = new PhysicsWorld2D({0.0f, -9.8f});

	//rectangles
	box = new RectangleShape({50.0f, 50.0f}, 1.0f);
	box->setTexture(GETTEXTURE("0"));
	box->transformation({400.0f, 400.0f});
	renderables.push_back(box);

	ground = new RectangleShape({500.0f, 5.0f}, 0.1f);
	ground->setTexture(GETTEXTURE("3"));
	ground->transformation({400.0f, 50.0f}, 20.0f);
	renderables.push_back(ground);

	jdm = new RectangleShape({50.0f, 50.0f}, 2.0f);
	jdm->setTexture(GETTEXTURE("1"));
	jdm->transformation({400.0f, 400.0f});
	renderables.push_back(jdm);

	//rect colliders
	boxCollider = new BoxCollider2D(world, ColliderType::Dynamic, box);
	boxCollider->setDensity(20.5f);
	boxCollider->setFriction(0.2f);
	boxCollider->setRestitution(0.5f);

	groundCollider = new BoxCollider2D(world, ColliderType::Static, ground);

	//circles
	circle0 = new CircleShape(100.0f, 0.3f);
	circle0->setTexture(GETTEXTURE("5"));
	circle0->setTextureRect({100, 100, 400, 400});
	circle0->transformation({370.0f, 200.0f});
	renderables.push_back(circle0);

	//circle colliders
	circleCollider0 = new CircleCollider2D(world, ColliderType::Static, circle0);

	//polygons
	poly0 = new Polygon(4.0f);
	poly0->setTexture(GETTEXTURE("6"));

//	polyCollider0 = new PolygonCollider2D(world, ColliderType::Static, poly0);

	//sprites
	Sprite *sp0 = new Sprite(GETTEXTURE("4"), 5.0f);
	sp0->transformation({20.0f, 20.0f});
	sp0->setTextureRect(rect(150, 130, 300, 320));
	sp0->setScale({0.3f, 0.3f});
	renderables.push_back(sp0);

	Renderer::setClearColor(color::rgba(0.55f, 1.0f, 0.93f, 1.0f));
}

TestB2D::~TestB2D() {
	delete camera;
	delete renderer;

	delete boxCollider;
	delete groundCollider;
	delete circleCollider0;
//	delete polyCollider0;

	for (const auto &r : renderables) {
		delete r;
	}
	delete poly0;

	delete world;
}

void TestB2D::render() {
	for (const auto &r : renderables) {
		renderer->submit(r);
	}
	for (const auto &p : points) {
		renderer->submit(p);
	}
	renderer->submit(poly0);

	renderer->renderSprites();
	renderer->renderText();

	renderer->clear();
}

void TestB2D::update(float delta) {
	if (Mouse::isButtonPressed(Mouse::Right)) {
		const vec2 p = Mouse::getPosition(window);
		boxCollider->set(p, boxCollider->getRotation());
		boxCollider->setAwake(true);
	}

	world->update(delta, 6, 3);
}

void TestB2D::input(xe::Event &event) {
	switch (event.type) {
		case Event::KeyPressed: {
			if (event.key.code == Keyboard::F1) {
				static bool wireframe = true;
				renderer->enableWireframe(wireframe);
				wireframe = !wireframe;
			}

			if (event.key.code == Keyboard::Up) {
				box->setSize(box->getSize() + 1);
			} else if (event.key.code == Keyboard::Down) {
				box->setSize(box->getSize() - 1);
			}

			if (event.key.code == Keyboard::R) {
				poly0->setVisible(false);

				for (const auto &p : points) {
					delete p;
				}
				points.clear();
				polyPoints.clear();
			}

			if (event.key.code == Keyboard::C) {
				poly0->reshape(polyPoints);
				poly0->setVisible(true);
			}

			if (event.key.code == Keyboard::W) {
				bool wake = boxCollider->isAwake();
				boxCollider->setAwake(!wake);
			}
			break;
		}

		case Event::MouseButtonPressed: {
			if (event.mouseButton.button == Mouse::Left) {
				const vec2 pos = {event.mouseButton.x, event.mouseButton.y};
				polyPoints.push_back(pos);

				RectangleShape *rs = new RectangleShape({5.0f, 5.0f}, poly0->getLayer() + 0.1f);
				rs->setColor(color::GREEN);
				rs->transformation(pos);
				points.push_back(rs);

//				XE_INFO(vec2(event.mouseButton.x, event.mouseButton.y));
			}
			break;
		}

		default: break;
	}
}

