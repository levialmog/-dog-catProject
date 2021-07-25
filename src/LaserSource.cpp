#include "LaserSource.h"

#include "Resources.h"
#include "Factory.h"
#include "LaserDestination.h"

bool LaserSource::m_registerIt = Factory<LaserSource>::registerIt(LASER_SOURCE, [](sf::Vector2f position, char type, b2World& world) ->
	std::unique_ptr<LaserSource> { return std::make_unique<LaserSource>(position, type, world); });

LaserSource::LaserSource(sf::Vector2f sourcePosition, char, b2World& world)
	:StaticObject(Resources::getResources().getSprite(type::laserSource),
				  sf::Vector2f(sourcePosition.x - (CELL_DIMENSIONS.x * HALF_RATIO), sourcePosition.y),
				  QUARTER_RATIO, STANDARD_RATIO)
{
	setBody(world, b2_staticBody, false, false);
}

void LaserSource::laser(b2World& world)
{
    float rayLength = float(WINDOW_DIMENSIONS.x);
    b2Vec2 p1(getBody()->GetPosition());
    b2Vec2 p2 = p1 + rayLength * b2Vec2(cosf(0), sinf(0));
    laserRayCast(p1, p2, world);
}

void LaserSource::laserRayCast(b2Vec2 p1, b2Vec2 p2, b2World& world)
{
    //set up input
    b2RayCastInput input;
    input.p1 = p1;
    input.p2 = p2;
    input.maxFraction = 1;
    sf::VertexArray laserRay(sf::Lines, 2);
    sf::VertexArray laserRayGlow(sf::Quads, 4);

    setLazerRayColor(laserRay, laserRayGlow);

    float closestFraction = 1;
    b2Vec2 intersectionNormal(0, 0);
    GameObject* intersectionBody = nullptr;

    //find the closest intersection to the source
    for (b2Body* b = world.GetBodyList(); b; b = b->GetNext())
    {
        for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
        {
            b2RayCastOutput output;
            if (!f->RayCast(&output, input, 0))
                continue;

            auto body = static_cast<GameObject*>(b->GetUserData());

            if ((body->getObjectType() == object::mirrorBox || body->getObjectType() == object::rightAngleMirror) &&
                (int(f->GetUserData()) != 1))
            {
                continue;
            }
            if (output.fraction < closestFraction) {
                closestFraction = output.fraction;
                intersectionNormal = output.normal;
                intersectionBody = body;
            }
        }
    }
    b2Vec2 intersectionPoint = p1 + closestFraction * (p2 - p1);

    if (abs(p1.y - intersectionPoint.y) > EPSILON)
    {
        setLazerRayPosition(laserRay, laserRayGlow, DIFF, 0, p1, intersectionPoint);
    }
    else
    {
        setLazerRayPosition(laserRay, laserRayGlow, 0, DIFF, p1, intersectionPoint);
    }

    m_laserRay.emplace_back(laserRay);
    m_laserRayGlow.emplace_back(laserRayGlow);

    if (intersectionBody->getObjectType() == object::laserDestination)
    {
        auto laserDestination = static_cast<LaserDestination*>(intersectionBody);
        laserDestination->activateControlledObject();
    }

    if (closestFraction == 1)
        return;
    if (closestFraction == 0)
        return;

    if (intersectionBody->getObjectType() == object::mirrorBox || intersectionBody->getObjectType() == object::rightAngleMirror)
    {
        b2Vec2 remainingRay = (p2 - intersectionPoint);
        b2Vec2 projectedOntoNormal = b2Dot(remainingRay, intersectionNormal) * intersectionNormal;
        b2Vec2 nextp2 = p2 - 2 * projectedOntoNormal;
        laserRayCast(intersectionPoint, nextp2, world);
    }
}

void LaserSource::draw(sf::RenderWindow& window)
{
    for (const auto& laserRayGlow : m_laserRayGlow)
    {
        window.draw(laserRayGlow);
    }
    
    for (const auto& laserRay : m_laserRay)
    {
        window.draw(laserRay);
    }

    m_laserRayGlow.clear();
    m_laserRay.clear();

    GameObject::draw(window);
}

void LaserSource::setLazerRayColor(sf::VertexArray& laserRay, sf::VertexArray& laserRayGlow)
{
    laserRay[0].color = sf::Color::Yellow;
    laserRay[1].color = sf::Color::Yellow;

    laserRayGlow[0].color = sf::Color(255, 255, 0, 60);
    laserRayGlow[1].color = sf::Color(255, 255, 0, 60);
    laserRayGlow[2].color = sf::Color(255, 255, 0, 60);
    laserRayGlow[3].color = sf::Color(255, 255, 0, 60);
}

void LaserSource::setLazerRayPosition(sf::VertexArray& laserRay, sf::VertexArray& laserRayGlow, float diffX, float diffY, b2Vec2 p1, b2Vec2 intersectionPoint)
{
    laserRay[0].position = sf::Vector2f(p1.x * PIXEL_METER_RATIO, p1.y * PIXEL_METER_RATIO);
    laserRay[1].position = sf::Vector2f(intersectionPoint.x * PIXEL_METER_RATIO, intersectionPoint.y * PIXEL_METER_RATIO);

    laserRayGlow[0].position = sf::Vector2f((p1.x * PIXEL_METER_RATIO) - diffX, (p1.y * PIXEL_METER_RATIO) - diffY);
    laserRayGlow[1].position = sf::Vector2f((intersectionPoint.x * PIXEL_METER_RATIO) - diffX, (intersectionPoint.y * PIXEL_METER_RATIO) - diffY);
    laserRayGlow[2].position = sf::Vector2f((intersectionPoint.x * PIXEL_METER_RATIO) + diffX, (intersectionPoint.y * PIXEL_METER_RATIO) + diffY);
    laserRayGlow[3].position = sf::Vector2f((p1.x * PIXEL_METER_RATIO) + diffX, (p1.y * PIXEL_METER_RATIO) + diffY);
}
