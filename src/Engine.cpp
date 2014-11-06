#include <Graphics/Text.h>
#include <Engine.h>
#include <IGameState.h>
#include <Components/ClickableComponent.h>

namespace kte
{

    Engine::~Engine()
    {
        for(unsigned int i = 0; i<gameObjects.size(); i++)
            delete gameObjects[i];

        for(unsigned int i = 0; i<guiTexts.size(); i++)
            delete guiTexts[i];
    }
    Engine* Engine::getInstance()
    {
        static Engine engine;
        return &engine;
    }


    bool Engine::pushGameState(IGameState *gs)
    {
        if(!isRunning && !initialize())
            return false;

        gameStates.push_back(gs);
        bool result = gs->initialize();

        return result;
    }

    void Engine::popGameState()
    {
        gameStates.back()->release();
        gameStates.pop_back();
    }

    bool Engine::initialize()
    {
        bool result = renderSystem.initialize(title, width, height);

        return result;
    }

    //Game loop
    void Engine::run()
    {
        if(gameStates.size() == 0)
            return;

        if(!isRunning)
            isRunning = true;

        while(isRunning)
        {
            gameStates.back()->update();

            renderSystem.getWindow()->clearScreen();
            renderSystem.render(gameObjects);
            renderSystem.render(guiTexts);
            renderSystem.getWindow()->swapBuffers();

        }
    }
    GameObject* Engine::addGameObject()
    {
        GameObject* go = new GameObject();
        gameObjects.push_back(go);
        return go;
    }
    GameObject* Engine::addGameObject(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation)
    {
        GameObject* go = new GameObject(position, scale, rotation);
        gameObjects.push_back(go);

        return go;
    }

    GameObject* Engine::getGameObjectAt2DPosition(float x, float y)
    {
        for(unsigned int i = 0; i<gameObjects.size(); i++)
        {
            if(gameObjects[i]->getComponent<ClickableComponent>() != NULL)
            {
                Transformation *trans = gameObjects[i]->getTransformation();
                if (trans->contains2DPoint(x, y))
                {
                    std::cout<<"Clicked on GO ID: "<<gameObjects[i]->getId()<<std::endl;
                    return (gameObjects[i]);
                }
            }
        }
        return NULL;
    }

    void Engine::exit()
    {
        isRunning = false;
    }

    Engine::Engine()
    {

    }

    kte::Text* Engine::createGuiText(Font *font, glm::vec3 position, glm::vec3 scale)
    {
        Text* text = new Text();
        text->setFont(font);
        text->getTransformation()->setPosition(position);
        text->getTransformation()->setScale(scale);

        guiTexts.push_back(text);
        return text;
    }


}