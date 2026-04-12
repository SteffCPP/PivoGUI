#pragma once

#include "EGUI_Dep.hpp"

#include <cstddef>

namespace egui{
	class Widget : public drawable, public transformable, public interactable{		
	protected:
		enum class WidgetType{
			WIDGET,
			SHAPE,
			RECTANGLE,
			CIRCLE
		};
	public:
		virtual ~Widget() = default;

		constexpr std::size_t getLayerNumber() const { return _layerN; }
		inline void setLayerNumber(const std::size_t n) { _layerN = n; }

	protected:
		constexpr WidgetType _getType() const { return _type; }
		
		WidgetType _type{WidgetType::WIDGET};
		std::size_t _layerN{0};

		friend class Window;
	};
}