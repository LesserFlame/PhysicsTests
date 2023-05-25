#include "World.h"
#include "Body.h"
#include "Forces/ForceGenerator.h"
#include "Constraints/Joint.h"
#include "Collisions/Collision.h"

#include <vector>

glm::vec2 World::gravity{ 0, -9.8f };
//glm::vec2 World::gravity{ 0, 0 };

World::~World()
{
	for (Body* body : m_bodies) delete body;
	m_bodies.clear();
}

void World::Step(float dt)
{
	std::vector<Body*> bodies(m_bodies.begin(), m_bodies.end());
	if (bodies.empty()) return;

	for (auto joint : m_joints) joint->Step(dt);
	if (!bodies.empty() && !m_forceGenerators.empty())
	{
		for (auto forceGenerator : m_forceGenerators)
		{
			forceGenerator->Apply(bodies);
		}
	}

	for (auto body : bodies) body->Step(dt);

	// collision
	std::vector<Contact> contacts;
	Collision::CreateContacts(bodies, contacts);
	Collision::SeparateContacts(contacts);
	Collision::ResolveContacts(contacts);
}

void World::Draw(Graphics* graphics)
{
	for (ForceGenerator* forceGenerator : m_forceGenerators) forceGenerator->Draw(graphics);
	for (Body* body : m_bodies) body->Draw(graphics);
	for (Joint* joint : m_joints) joint->Draw(graphics);
}

void World::AddBody(Body* body)
{
	m_bodies.push_back(body);
}

void World::RemoveBody(Body* body)
{
	m_bodies.remove(body);
}

void World::AddJoint(Joint* joint)
{
	m_joints.push_back(joint);
}

void World::RemoveJoint(Joint* joint)
{
	m_joints.remove(joint);
}

void World::AddForceGenerator(ForceGenerator* forceGenerator)
{
	m_forceGenerators.push_back(forceGenerator);
}
