#include "ForceTest.h"
#include "../Physics/Body.h"
#include "../Physics/Shapes/CircleShape.h"

#include "../Physics/Forces/GravitationalForce.h"
#include "../Physics/Forces/PointForce.h"
#include "../Physics/Forces/DragForce.h"
#include "../Physics/Forces/AreaForce.h"

#define POINT_FORCE
//#define AREA_FORCE
//#define DRAG_FORCE

void ForceTest::Initialize()
{
	Test::Initialize();

	//auto forceGenerator1 = new GravitationalForce(400);

	//m_world->AddForceGenerator(forceGenerator1);

	//World::gravity = { 0, 9.8 };
	//World::gravity = { 0, 0 };
#if defined(POINT_FORCE)
	auto body = new Body(new CircleShape(5, { 1, 1, 1, 0.2f }), { 0, 0 }, { 0, 0 }, 0, Body::STATIC);
	ForceGenerator* forceGenerator = new PointForce(body, 20);
	m_world->AddForceGenerator(forceGenerator);
#elif defined(AREA_FORCE)
	auto body = new Body(new CircleShape(5, { 1, 1, 1, 0.2f }), { 0, 0 }, { 0, 0 }, 0, Body::STATIC);
	ForceGenerator* forceGenerator = new AreaForce(body, 20,90);
	m_world->AddForceGenerator(forceGenerator);
#elif defined(DRAG_FORCE)
	auto body = new Body(new CircleShape(5, { 1, 1, 1, 0.2f }), { 0, 0 }, { 0, 0 }, 0, Body::STATIC);
	ForceGenerator* forceGenerator = new DragForce(body, 0.5f);
	m_world->AddForceGenerator(forceGenerator);
#endif
}

void ForceTest::Update()
{
	Test::Update();

	glm::vec2 position = m_graphics->ScreenToWorld(m_input->GetMousePosition());
	//m_user->velocity = position - m_user->position;
	//m_user->position = position;

	if (m_input->GetMouseButton(0))
	{
		glm::vec2 velocity = { 0, 0 };// randomUnitCircle() * randomf(1, 3);
		float size = randomf(0.1f, 1.0f);

		auto body = new Body(new CircleShape(size, { randomf(), randomf(), randomf(), 1 }), position, velocity, size);
		body->damping = 0;
		body->gravityScale = 1;

		body->restitution = 1;

		m_world->AddBody(body);
	}
}

void ForceTest::FixedUpdate()
{
	m_world->Step(m_time->GetFixedDeltaTime());
}

void ForceTest::Render()
{
	m_graphics->SetColor({ 0, 0, 0, 1 });
	m_graphics->Clear();

	m_graphics->DrawCircle(m_input->GetMousePosition(), 30, { randomf(), randomf(), randomf(), 1 });
	m_world->Draw(m_graphics);
	m_graphics->Present();
}
