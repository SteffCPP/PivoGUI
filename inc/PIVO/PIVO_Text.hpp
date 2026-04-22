/*
PivoGUI
Copyright (c) 2026 Stefano Rando (randostefano39@proton.me)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required. 
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
*/

#pragma once

#include "PIVO_Widget.hpp"

#include <string>
#include <vector>

struct TTF_Font;
struct TTF_Text;
struct SDL_Renderer;

namespace pivo{
class Text {
public:
    /// Text style flags (bitmask).
    enum class Style {
        NORMAL         = 0,
        BOLD           = 1 << 0,
        ITALIC         = 1 << 1,
        UNDERLINE      = 1 << 2,
        STRIKETHROUGH  = 1 << 3
    };
	
    /// Horizontal text alignment options.
    enum class Alignment {
        INVALID = -1,
        LEFT,
        CENTER,
        RIGHT
    };

public:
    /// Sets the text content.
    /// @param txt New text string.
    void setText(const std::string& txt);

    /// Gets the current text content.
    /// @return Current text string.
    std::string getText() const;

    /// Appends text to the current content.
    /// @param txt Text to append.
    void appendText(const std::string& txt);

    /// Loads a font from file.
    /// @param path Path to font file.
    /// @param size Font size in pixels.
    void loadFont(const std::string& path, const float& size);

    /// Sets the font size.
    /// @param size New font size in pixels.
    void setFontSize(const float& size);

    /// Gets the font size.
    /// @return Font size in pixels.
    float getFontSize() const;

    /// Enables or disables a specific text style.
    /// @param style Style flag to modify.
    /// @param flag True to enable, false to disable.
    void setStyle(const Style& style, const bool& flag);

    /// Gets the current text style bitmask.
    /// @return Active style flags.
    Style getStyle() const;

    /// Sets the text color.
    /// @param color New text color.
    void setColor(const Color_RGBA& color);

    /// Gets the text color.
    /// @return Current text color.
    Color_RGBA getColor() const;

    /// Sets the rendered text size.
    /// @param size New size (width, height).
    void setSize(const Vector2D& size);

    /// Gets the rendered text size.
    /// @return Text size.
    Vector2D getSize() const;

    /// Sets horizontal alignment.
    /// @param align Text alignment mode.
    void setAlignment(Text::Alignment align);

    /// Default constructor.
    Text() {}

    /// Constructs a Text object.
    /// @param text Initial text content.
    /// @param fontPath Path to font file.
    /// @param size Font size in pixels.
    /// @param color Text color (default = white).
    Text(const std::string& text,
         const std::string& fontPath,
         const float& size,
         const Color_RGBA& color = colors::White);

    /// Destructor.
    ~Text();

private:
    Vector2D _size{0, 0};
    std::string _text{""};
    Color_RGBA _color{colors::White};
    short _styles;

    TTF_Text* _ttftext = nullptr;
    TTF_Font* _ttffont = nullptr;

    Alignment _alignment{Alignment::LEFT};

    friend class TextLabel;
    friend class TextLabelInput;
};

class TextLabel : public Widget, public sizeable, public rotatable{
public:

    /// Textbox alignment inside the label.
    enum class TextBoxAlignment {
        TOP_LEFT,
        TOP,
        TOP_RIGHT,
        LEFT,
        CENTER,
        RIGHT,
        BOTTOM_LEFT,
        BOTTOM,
        BOTTOM_RIGHT
    };

public:
    /// Sets internal padding.
    /// @param padding Padding in pixels.
    void setPadding(const float& padding);

    /// Sets text alignment inside the textbox.
    /// @param align Alignment mode.
    void setTextboxAlignment(const TextBoxAlignment align);

    /// Gets current textbox alignment.
    /// @return Alignment mode.
    TextBoxAlignment getTextboxAlignment() const;

    /// Text content of the label.
    Text text;

    /// Default constructor.
    TextLabel();

    /// Constructs a TextLabel.
    /// @param position Position in world space.
    /// @param size Size of the label.
    /// @param textStr Initial text.
    /// @param fontPath Font file path.
    /// @param fontSize Font size in pixels.
    /// @param textColor Text color (default = white).
    TextLabel(const Vector2D& position,
              const Vector2D& size,
              const std::string& textStr,
              const std::string& fontPath,
              const float& fontSize,
              const Color_RGBA& textColor = colors::White);

    /// Checks if a point is inside the label.
    /// @param point Point in world space.
    /// @return True if point is inside.
    virtual bool containsPoint(const Vector2D& point) const override;
private:
    /// Internal render function for the label.
    /// @param __renderer SDL rendering context.
    void _draw(SDL_Renderer* __renderer) override;

    virtual Vector2D _computePivotOffset() const override;

    float _padding{10};
    TextBoxAlignment _textboxAlignment{TextBoxAlignment::CENTER};
};

	/*class TextLabelInput : public Widget{
	public:

	private:
		
	};*/
}