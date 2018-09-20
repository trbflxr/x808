//
// Created by FLXR on 9/11/2018.
//

#include <xe/resources/texturemanager.hpp>
#include "testb2d.hpp"

#include <xe/math/triangulator.hpp>

using namespace xe;

TestB2D::TestB2D() {
	const float width = app.getConfig().width;
	const float height = app.getConfig().height;

	TextureParameters params;

	TextureManager::add(new Texture("0", "assets/textures/enemyspotted.png", params));
	TextureManager::add(new Texture("1", "assets/textures/jdm.png", params, true));
	TextureManager::add(new Texture("2", "assets/textures/star.png", params, true));
	TextureManager::add(new Texture("3", "assets/textures/test1.png", params));
	TextureManager::add(new Texture("4", "assets/textures/test6.png", params));
	TextureManager::add(new Texture("5", "assets/textures/test8.png", params));

	params.wrap = TextureWrap::Repeat;
	TextureManager::add(new Texture("6", "assets/textures/sp0.png", params));


	//create camera
	camera = new Camera(mat4::ortho(0, width, 0, height, -1, 1000));

	renderer = new BatchRenderer2D(width, height, camera);

	world = new PhysicsWorld2D({0.0f, -9.8f});

	//rectangles
	box = new RectangleShape({50.0f, 50.0f}, 1.0f);
	box->setTexture(GETTEXTURE("0"));
	box->transformation({400.0f, 400.0f});

	ground = new RectangleShape({500.0f, 5.0f}, 0.0f);
	ground->setTexture(GETTEXTURE("3"));
	ground->transformation({400.0f, 50.0f}, 20.0f);

	jdm = new RectangleShape({50.0f, 50.0f}, 2.0f);
	jdm->setTexture(GETTEXTURE("1"));
	jdm->transformation({400.0f, 400.0f});

	//rect colliders
	boxCollider = new BoxCollider2D(world, ColliderType::Dynamic, box);
	boxCollider->setDensity(20.5f);
	boxCollider->setFriction(0.2f);
	boxCollider->setRestitution(0.5f);

	groundCollider = new BoxCollider2D(world, ColliderType::Static, ground);

	//circles
	circle0 = new CircleShape(100.0f, 0.0f);
	circle0->setTexture(GETTEXTURE("5"));
	circle0->transformation({370.0f, 200.0f});

	//circle colliders
	circleCollider0 = new CircleCollider2D(world, ColliderType::Static, circle0);

	//polygons
//	poly0 = new Polygon(33, 5.0f);
//	poly0->setPoint(0, {769.000f, 377.000f});
//	poly0->setPoint(1, {753.000f, 407.000f});
//	poly0->setPoint(2, {746.000f, 447.000f});
//	poly0->setPoint(3, {752.000f, 488.000f});
//	poly0->setPoint(4, {767.000f, 520.000f});
//	poly0->setPoint(5, {797.000f, 544.000f});
//	poly0->setPoint(6, {831.000f, 553.000f});
//	poly0->setPoint(7, {863.000f, 550.000f});
//	poly0->setPoint(8, {907.000f, 518.000f});
//	poly0->setPoint(9, {929.000f, 482.000f});
//	poly0->setPoint(10, {934.000f, 446.000f});
//	poly0->setPoint(11, {931.000f, 399.000f});
//	poly0->setPoint(12, {935.000f, 365.000f});
//	poly0->setPoint(13, {952.000f, 333.000f});
//	poly0->setPoint(14, {1002.000f, 320.000f});
//	poly0->setPoint(15, {1054.000f, 331.000f});
//	poly0->setPoint(16, {1076.000f, 365.000f});
//	poly0->setPoint(17, {1091.000f, 424.000f});
//	poly0->setPoint(18, {1115.000f, 489.000f});
//	poly0->setPoint(19, {1128.000f, 507.000f});
//	poly0->setPoint(20, {1161.000f, 499.000f});
//	poly0->setPoint(21, {1196.000f, 417.000f});
//	poly0->setPoint(22, {1175.000f, 318.000f});
//	poly0->setPoint(23, {1146.000f, 250.000f});
//	poly0->setPoint(24, {1052.000f, 190.000f});
//	poly0->setPoint(25, {931.000f, 184.000f});
//	poly0->setPoint(26, {841.000f, 208.000f});
//	poly0->setPoint(27, {776.000f, 255.000f});
//	poly0->setPoint(28, {737.000f, 298.000f});
//	poly0->setPoint(29, {713.000f, 331.000f});
//	poly0->setPoint(30, {721.000f, 364.000f});
//	poly0->setPoint(31, {738.000f, 378.000f});
//	poly0->setPoint(32, {774.000f, 380.000f});
//	poly0->create();
//	poly0->setTexture(GETTEXTURE("6"));
//	poly0->setColor(color::GREEN);

	//sprites
	sp0 = new Sprite(GETTEXTURE("4"), 2.0f);
	sp0->transformation({20.0f, 20.0f});
	sp0->setTextureRect(rect(150, 130, 300, 320));
	sp0->setScale({0.3f, 0.3f});


	std::vector<vec2> vertices{{10,  10},
	                           {100, 10},
	                           {200, 200},
	                           {10,  100},
	                           {50,  50}};

	std::vector<uint> triangles;
	triangulator::compute(vertices, triangles);


	printf("1\n");
}

TestB2D::~TestB2D() {
	delete camera;
	delete renderer;

	delete boxCollider;
	delete groundCollider;

	delete box;
	delete ground;
	delete jdm;

	delete circle0;

	delete circleCollider0;

//	delete poly0;

	delete sp0;

	delete world;
}

void TestB2D::render() {
	renderer->submit(box);
	renderer->submit(ground);
	renderer->submit(jdm);
	renderer->submit(circle0);
//	renderer->submit(poly0);
	renderer->submit(sp0);

	renderer->renderSprites();
	renderer->renderText();

	renderer->clear();
}

void TestB2D::update(float delta) {
	if (Mouse::isButtonPressed(Mouse::Left)) {
		const vec2 p = Mouse::getPosition(window);
		boxCollider->set(p, boxCollider->getRotation());
		boxCollider->setAwake(true);
	}

	world->update(delta, 6, 3);
}

void TestB2D::input(xe::Event &event) {


	switch (event.type) {
		case Event::KeyPressed: {
			if (event.key.code == Keyboard::Up) {
				box->setSize(box->getSize() + 1);
			} else if (event.key.code == Keyboard::Down) {
				box->setSize(box->getSize() - 1);
			}

			if (event.key.code == Keyboard::R) {
				poly0->setPointCount(0);
				poly0->create();
			}
			break;
		}

		case Event::MouseButtonPressed: {
			if (event.mouseButton.button == Mouse::Left) {
//				uint size = poly0->getPointCount();
//				poly0->setPointCount(size + 1);
//				poly0->setPoint(size, {event.mouseButton.x, event.mouseButton.y});
//				poly0->create();
//
//				XE_INFO(vec2(event.mouseButton.x, event.mouseButton.y));
			}

			if (event.mouseButton.button == Mouse::Right) {
				static bool wake = false;
				boxCollider->setAwake(wake);
				wake = !wake;

//				poly0->create();
			}

			break;
		}

		default: break;
	}
}

void TestB2D::tick() {

}
