#include "ContactListener.h"
#include "GameObject.h"
#include "Player.h"
#include "CollisionHandler.h"
#include "Macros.h"

#include <fstream>

void ContactListener::BeginContact(b2Contact* contact)
{
	auto gameObject1 = static_cast<GameObject*>(contact->GetFixtureA()->GetBody()->GetUserData());
	auto gameObject2 = static_cast<GameObject*>(contact->GetFixtureB()->GetBody()->GetUserData());

	if (gameObject1 && gameObject2)
	{
		if (gameObject1->getObjectType() == object::player || gameObject2->getObjectType() == object::player)
		{
			if (int(contact->GetFixtureA()->GetUserData()) == 1 || int(contact->GetFixtureB()->GetUserData()) == 1)
			{
				auto player = gameObject1->getObjectType() == object::player ? static_cast<Player*>(gameObject1) :
																			   static_cast<Player*>(gameObject2);
				player->incFootContacts();
				return;
			}
		}

		CollisionHandler::getCollisionHandler().processCollision(gameObject1, gameObject2, true);
	}
}

void ContactListener::EndContact(b2Contact* contact)
{
	auto gameObject1 = static_cast<GameObject*>(contact->GetFixtureA()->GetBody()->GetUserData());
	auto gameObject2 = static_cast<GameObject*>(contact->GetFixtureB()->GetBody()->GetUserData());

	if (gameObject1 && gameObject2)
	{
		if (gameObject1->getObjectType() == object::player || gameObject2->getObjectType() == object::player)
		{
			if (int(contact->GetFixtureA()->GetUserData()) == 1 || int(contact->GetFixtureB()->GetUserData()) == 1)
			{
				auto player = gameObject1->getObjectType() == object::player ? static_cast<Player*>(gameObject1) :
					static_cast<Player*>(gameObject2);
				player->decFootContacts();
				return;
			}
		}
		CollisionHandler::getCollisionHandler().processCollision(gameObject1, gameObject2, false);
	}
}