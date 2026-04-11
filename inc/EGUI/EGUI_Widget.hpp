#pragma once

#include "EGUI_Dep.hpp"

struct SDL_Renderer;
struct SDL_FRect;

namespace egui{
	class Widget : public drawable, public interactable{		
	protected:
		enum class WidgetType{
			WIDGET,
			SHAPE,
			RECTANGLE,
			CIRCLE
		};
	public:
		virtual ~Widget() = default;

		constexpr Vector2D getPosition() const { return _pos; }
		constexpr std::size_t getLayerNumber() const { return _layerN; }

		inline void setPosition(const Vector2D& pos) { _pos = pos; _hitbox.setPosition(_pos); }
		inline void setLayerNumber(const std::size_t n) { _layerN = n; }
	protected:
		constexpr WidgetType _getType() const { return _type; }
		
		WidgetType _type{WidgetType::WIDGET};
		std::size_t _layerN{0};
		Vector2D _pos{0, 0};

		friend class Window;
	};
}