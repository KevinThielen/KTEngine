#ifndef KTE_GAME_ENGINE_H
#define KTE_GAME_ENGINE_H


/*
    The Main Class for the client.
    It manages the game scenes.
    There can only be one GameEngine-Instance per game
 */

#include <string>

namespace kte
{
    struct WindowDesc
    {
        std::string title;
        int width;
        int height;
    };

    class GameEngine
    {
    public:
        static GameEngine &instance()
        {
            static GameEngine *instance = new GameEngine();
            return *instance;
        }

        //run the game. The parameter is the first gameScene that should run.
        void run();

        //exit the whole game
        void exit();

    private:
        //only one instance
        GameEngine() {}

        
    };
}
#endif