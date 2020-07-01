#ifndef EFFECT_HPP
#define EFFECT_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML3D/Graphics.hpp>
#include <cassert>
#include <string>


////////////////////////////////////////////////////////////
// Base class for effects
////////////////////////////////////////////////////////////
class Effect : public sf3d::Drawable
{
public :

    virtual ~Effect()
    {
    }

    static void setFont(const sf3d::Font& font)
    {
        s_font = &font;
    }

    const std::string& getName() const
    {
        return m_name;
    }

    void load()
    {
        m_isLoaded = sf3d::Shader::isAvailable() && onLoad();
    }

    void update(float time, float x, float y)
    {
        if (m_isLoaded)
            onUpdate(time, x, y);
    }

    void draw(sf3d::RenderTarget& target, sf3d::RenderStates states) const
    {
        if (m_isLoaded)
        {
            onDraw(target, states);
        }
        else
        {
            sf3d::Text error("Shader not\nsupported", getFont());
            error.setPosition(320.f, 200.f);
            error.setCharacterSize(36);
            target.draw(error, states);
        }
    }

protected :

    Effect(const std::string& name) :
    m_name(name),
    m_isLoaded(false)
    {
    }

    static const sf3d::Font& getFont()
    {
        assert(s_font != NULL);
        return *s_font;
    }

private :

    // Virtual functions to be implemented in derived effects
    virtual bool onLoad() = 0;
    virtual void onUpdate(float time, float x, float y) = 0;
    virtual void onDraw(sf3d::RenderTarget& target, sf3d::RenderStates states) const = 0;

private :

    std::string m_name;
    bool m_isLoaded;

    static const sf3d::Font* s_font;
};

#endif // EFFECT_HPP
