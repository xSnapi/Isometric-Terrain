#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <box2d/b2_draw.h>

namespace hv {
	enum class DebugDrawType { Collider = 0, Joint, AABB, MassCenter, Light, LightEdge };

	class b2DebugDraw : public b2Draw {
	public:
        b2DebugDraw();
        ~b2DebugDraw();

        void SetWindow(sf::RenderWindow& window);
	private:
        sf::RenderWindow* m_window = nullptr;

        virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
        virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
        virtual void DrawCircle(const b2Vec2& center, float radius, const b2Color& color);
        virtual void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color);
        virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
        virtual void DrawTransform(const b2Transform& xf);
        virtual void DrawPoint(const b2Vec2& p, float size, const b2Color& color);
        virtual void DrawAABB(b2AABB* aabb, const b2Color& color);
	};
}