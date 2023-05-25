#include "JointTest.h"
#include "../Physics/Shapes/CircleShape.h"
#include "../Physics/World.h"
#include "../Physics/Body.h"
#include "../Physics/Constraints/Joint.h"

#define SPRING_STIFFNESS	100
#define SPRING_LENGTH		2
#define BODY_DAMPING		10
#define CHAIN_SIZE			4

void JointTest::Initialize()
{
	Test::Initialize();
	//m_world->gravity = { 0, 0 };

	m_anchor = new Body(new CircleShape(1, { 1, 1, 1, 1 }), { 0, 0 }, { 0, 0 }, 0, Body::KINEMATIC);
	m_world->AddBody(m_anchor);

	Body* body = nullptr;
	auto prevBody = m_anchor;

	int chainType = 0;

	if (chainType == 0)
	{
		for (int i = 0; i < CHAIN_SIZE; i++)
		{
			body = new Body(new CircleShape(0.5f, { 1, 1, 1, 1 }), { 0, 0 });
			body->damping = BODY_DAMPING;
			m_world->AddBody(body);

			auto joint = new Joint(prevBody, body, SPRING_STIFFNESS, SPRING_LENGTH);
			m_world->AddJoint(joint);
			prevBody = body;
		}
	}
	else if (chainType == 1)
	{
		Body* prev1 = prevBody;
		Body* prev2 = prevBody;

		for (int i = 0; i < CHAIN_SIZE; i++)
		{
			Body* body1 = new Body(new CircleShape(20, { 1, 1, 1, 1 }), { 400, 200 + i * 100}, { 0, 0 }, 1, Body::DYNAMIC);
			body1->gravityScale = 250;
			body1->damping = BODY_DAMPING;
			m_world->AddBody(body1);

			Joint* joint = new Joint(prev1, body1, SPRING_STIFFNESS, SPRING_LENGTH);
			m_world->AddJoint(joint);
			if (prev1 != prev2)
			{
				joint = new Joint(prev2, body1, SPRING_STIFFNESS, SPRING_LENGTH);
				m_world->AddJoint(joint);
			}

			Body* body2 = new Body(new CircleShape(20, { 1, 1, 1, 1 }), { 500, 200 + i * 100 }, { 0, 0 }, 1, Body::DYNAMIC);
			body2->gravityScale = 250;
			body2->damping = BODY_DAMPING;
			m_world->AddBody(body2);

			joint = new Joint(prev1, body2, SPRING_STIFFNESS, SPRING_LENGTH);
			m_world->AddJoint(joint);
			if (prev1 != prev2)
			{
				joint = new Joint(prev2, body2, SPRING_STIFFNESS, SPRING_LENGTH);
				m_world->AddJoint(joint);
			}
			joint = new Joint(body1, body2, SPRING_STIFFNESS, SPRING_LENGTH);
			m_world->AddJoint(joint);

			prev1 = body1;
			prev2 = body2;
		}
	}
}

void JointTest::Update()
{
	Test::Update();
	m_anchor->position = m_graphics->ScreenToWorld(m_input->GetMousePosition());
}

void JointTest::FixedUpdate()
{
	m_world->Step(m_time->GetFixedDeltaTime());
}

void JointTest::Render()
{
	m_world->Draw(m_graphics);
	m_graphics->DrawCircle(m_input->GetMousePosition(), 10, { randomf(), randomf(), randomf(), 1 });
}