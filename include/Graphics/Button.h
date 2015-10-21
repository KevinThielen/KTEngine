#ifndef KTE_BUTTON_H
#define KTE_BUTTON_H

#include "GameSprite.h"
#include "Text.h" 

namespace kte 
{
    class Button 
    {
    public:
	Button(GameObject* parent, glm::vec2 position, glm::vec2 size, int layer, Texture* background, FontTexture* font)
	{
	    this->background = kte::GameSprite(parent, background);
	    this->background.setPosition(position);
	    this->background.setSize(size);
	    this->background.setLayer(layer);

	    
	    text.setFont(font);
	    text.setPosition(this->background.getWorldPosition().x, this->background.getWorldPosition().y+5);
	    text.setColor(glm::vec4(1,0,0,1));
	    
	}
	
	void isActive(bool active) { background.setActive(active); }
	bool isActive() { return background.isActive();
	    
	}	void setText(std::string text) { this->text.setString(text); }
	Text getText() { return text; }
	
	void setOnClick(std::function<void(void)> callback) { background.setOnReleaseEvent(callback); }
    private:
	kte::GameSprite background;
	kte::Text text;
    };
}
#endif