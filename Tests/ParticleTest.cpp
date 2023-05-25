#include "ParticleTest.h"
#include "../Physics/Body.h"
#include "../Physics/Shapes/CircleShape.h"

void ParticleTest::Initialize()
{
	Test::Initialize();
}

void ParticleTest::Update()
{
	Test::Update();

	if (m_input->GetMouseButton(0))
	{
		//glm::vec2 velocity = { randomf(-100,100), randomf(-100,100)};
		glm::vec2 velocity = randomUnitCircle() * randomf(1, 2);
		auto body = new Body(new CircleShape(randomf(0.1f, 1.0f), { randomf(), randomf(), randomf(), randomf() }), m_graphics->ScreenToWorld(m_input->GetMousePosition()), velocity);
		body->damping = 1;
		body->gravityScale = 0;
		m_world->AddBody(body);
	};
}

void ParticleTest::FixedUpdate()
{
	m_world->Step(m_time->GetFixedDeltaTime());
}

void ParticleTest::Render()
{
	m_graphics->SetColor({ 0, 0, 0, 1 });
	m_graphics->Clear();

	m_graphics->DrawCircle(m_input->GetMousePosition(), 30, { randomf(), randomf(), randomf(), 1 });
	m_world->Draw(m_graphics);
	m_graphics->Present();
}
