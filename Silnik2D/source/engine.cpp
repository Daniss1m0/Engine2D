#include "engine.h"

Engine::Engine(int width, int height, float fps) : _screenWidth(width), _screenHeight(height), _FPS(fps) {}

bool Engine::Init() {
    if (!al_init()) {
        std::cerr << "Nie udało się zainicjować Allegro." << std::endl;
        return false;
    }

    al_install_keyboard();
    al_install_mouse();

    al_init_image_addon(); //metoda inicjalizacja

    _display = al_create_display(_screenWidth, _screenHeight);
    if (!_display) {
        std::cerr << "Nie udało się utworzyć display." << std::endl;
        return false;
    }

    _eventQueue = al_create_event_queue();
    al_register_event_source(_eventQueue, al_get_display_event_source(_display));
    al_register_event_source(_eventQueue, al_get_keyboard_event_source());
    al_register_event_source(_eventQueue, al_get_mouse_event_source());

    _fpsTimer = al_create_timer(1.0 / _FPS);
    al_register_event_source(_eventQueue, al_get_timer_event_source(_fpsTimer));

    return true;
}

void Engine::Run() {
    bool running = true;
    al_start_timer(_fpsTimer);

    PrimitiveRenderer& renderer = PrimitiveRenderer::getInstance();
    renderer.Initialize(_display);

    game::Player ply;
    ply.LoadFromFile("player.png");
    ply.Move(Vector2(400.0f, 500.0f));

    game::SpriteObject object;
    object.SetSprite("anim/Shoe1.png", 0);
    object.SetSprite("anim/Shoe2.png", 1);
    object.SetSprite("anim/Shoe3.png", 2);
    object.SetSprite("anim/Shoe4.png", 3);
    object.Move(Vector2(150.0, 300.0));

    std::vector<Point2D> polygon;
    polygon.push_back(Point2D(-50.0, -50.0));
    polygon.push_back(Point2D(50.0, -50.0));
    polygon.push_back(Point2D(50.0, 50.0));
    polygon.push_back(Point2D(-50.0, 50.0));

    game::Polygon wielokat(Vector2(500.0,300.0),polygon);
    wielokat.Set_thickness(1.0);
    bool transformationFlag = false;

    struct KeysPushed
    {
        bool KeyA = false;
        bool KeyB = false;
        bool KeyW = false;
        bool KeyS = false;
        bool KeyQ = false;
        bool KeyE = false;
        bool KeyX = false;
        bool KeyZ = false;
    } KeysPushed;

    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(_eventQueue, &event);

        switch(event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE: {
                running = false;
                break;
            }

            case ALLEGRO_EVENT_TIMER: {
                renderer.ClearScreen();

                //int k = 0;
                for (const auto& obiekt : game::UpdatableVector) {
                    obiekt->Update();
                    //k++;
                }
                //std::cout <<"liczba obiektow w updatable vector: "<< k << std::endl;

                if(wielokat.GetScale() > 2.0 or wielokat.GetScale()<-2.0)
                {
                    transformationFlag = not transformationFlag;
                }
                if (transformationFlag)
                    wielokat.Scale(wielokat.GetScale()+0.05);
                else
                    wielokat.Scale(wielokat.GetScale() - 0.05);
                wielokat.Rotate(3.0);


                if (KeysPushed.KeyA)
                    ply.Move(Vector2(-3.0f, 0.0f));
                else if (KeysPushed.KeyB)
                    ply.Move(Vector2(3.0f, 0.0f));
                else if (KeysPushed.KeyW)
                    ply.Move(Vector2(0.0f, -3.0f));
                else if (KeysPushed.KeyS)
                    ply.Move(Vector2(0.0f, 3.0f));
                else if (KeysPushed.KeyQ)
                    ply.SetOrientation(ply.GetOrientation() - 0.1);
                else if (KeysPushed.KeyE)
                    ply.SetOrientation(ply.GetOrientation() + 0.1);
                else if (KeysPushed.KeyX)
                    ply.SetScale(ply.GetScale() + 0.1);
                else if (KeysPushed.KeyZ)
                    ply.SetScale(ply.GetScale() - 0.1);

                renderer.FlipDisplay();
                break;
            }

            case ALLEGRO_EVENT_KEY_DOWN: {
                switch (event.keyboard.keycode)
                {
                case ALLEGRO_KEY_A:
                    KeysPushed.KeyA = true;
                    break;

                case ALLEGRO_KEY_D:
                    KeysPushed.KeyB = true;
                    break;

                case ALLEGRO_KEY_S:
                    KeysPushed.KeyS = true;
                    break;

                case ALLEGRO_KEY_W:
                    KeysPushed.KeyW = true;
                    break;

                case ALLEGRO_KEY_Q:
                    KeysPushed.KeyQ = true;
                    break;

                case ALLEGRO_KEY_E:
                    KeysPushed.KeyE = true;
                    break;

                case ALLEGRO_KEY_X:
                    KeysPushed.KeyX = true;
                    break;

                case ALLEGRO_KEY_Z:
                    KeysPushed.KeyZ = true;
                    break;


                }


                break;
            }

            case ALLEGRO_EVENT_KEY_UP:
                KeysPushed.KeyA = false;
                KeysPushed.KeyB = false;
                KeysPushed.KeyQ = false;
                KeysPushed.KeyE = false;
                KeysPushed.KeyS = false;
                KeysPushed.KeyW = false;
                KeysPushed.KeyX = false;
                KeysPushed.KeyZ = false;
                break;
        }   
    }
}

void Engine::Deinit() {
    al_destroy_display(_display);
    al_destroy_event_queue(_eventQueue);
    al_destroy_timer(_fpsTimer);
}