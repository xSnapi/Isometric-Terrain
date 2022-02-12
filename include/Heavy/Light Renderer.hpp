#pragma once
#include <unordered_set>
#include <list>

#include "Heavy Renderer.hpp"

namespace std {
	template<> struct hash<sf::Vector2f> {
		std::size_t operator()(const sf::Vector2f& p) const noexcept {
			return size_t(p.x + 10.0f * p.y);
		}
	};
}

namespace hv {
	class  LightWorld;
	struct Edge;
	struct Light;

	struct Point
	{
		Point(sf::Vector2f position, float angle) :
			Position(position),
			Angle(angle)
		{

		}

		sf::Vector2f Position;
		float		 Angle = 0.0f;
	};
}

namespace hv {
	

	class LightRenderer {
	public:
		LightRenderer();
		~LightRenderer();

		void Resize(sf::Vector2u size);

		void DrawLights(Renderer& renderer);

	private:
		sf::Sprite m_texturer;

		sf::Shader m_spotShader;

		sf::Shader m_mergeShader;

		sf::RenderTexture m_lightMask;
		sf::RenderTexture m_lightMaskBuffer;

		sf::RenderTexture m_shadowMask;
		sf::RenderTexture m_shadowMaskBuffer;

		std::vector<Point>				 m_RayPoints;
		std::vector<sf::Vertex>			 m_ShadowVertexArray;
		std::unordered_set<sf::Vector2f> m_Vertices;

		std::list<Edge*> m_ShadowBox;

		// Debug Draw stuff
		std::vector<sf::Vertex> m_Lines;

		void CreateLightMask();
		void CreateShadowMask(const Light& light);

		void CastRays(sf::Vector2f pos);

		void ResizeTextures(sf::Vector2u size);
		void ResizeShaders(sf::Vector2f size);
		void ResizeShadowBox();

		void LoadShaders();
		void InitShadowBox();

		void DebugDraw(Renderer& renderer);

		friend class LightWorld;
	};
}