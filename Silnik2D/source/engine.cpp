//zrobic hierarchi klass (np. jak w instrukcji 4 pierwsze zadanie)

#include "engine.h"

Engine::Engine(int width, int height, float fps) : _screenWidth(width), _screenHeight(height), _FPS(fps) {}

bool Engine::Init() {
    if (!al_init()) {
        std::cerr << "Nie udało się zainicjować Allegro." << std::endl;
        return false;
    }

    al_install_keyboard();
    al_install_mouse();

    al_init_image_addon(); //

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
    ply.LoadFromFile("example.png");
    ply.SetScale(0.1);
    ply.Move(Vector2(150.0,300.0));
    float i = 0.0;

    std::vector<Point2D> polygonPoints;
    polygonPoints.push_back(Point2D(-100.0, 100.0));
    polygonPoints.push_back(Point2D(100.0, 100.0));
    polygonPoints.push_back(Point2D(100.0, -100.0));
    polygonPoints.push_back(Point2D(-100.0, -100.0));

    game::Polygon polygon(Vector2(650.0, 300),polygonPoints);
    polygon.SetThickness(10.0);
    float scale = 1.0;
    bool up = true;

    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(_eventQueue, &event);

        switch(event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE: {
                running = false;
                break;
            }
       
            case ALLEGRO_EVENT_TIMER: {
                ply.SetOrientation(i);
                polygon.Rotate(6);
                polygon.Scale(scale);
                i += 0.1;
                if (up == true)
                {
                    scale += 0.01;
                    if(scale > 2.0)
                        up = false;
                }
                else
                {
                    scale -= 0.01;
                    if(scale < 0.5)
                        up = true;
                }
             
                break;
            }

            case ALLEGRO_EVENT_KEY_DOWN: {
                break;
            }

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
                break;
            }
        }
        renderer.ClearScreen();
        ply.Draw();
        polygon.Draw();
        renderer.FlipDisplay();
    }
}

void Engine::Deinit() {
    al_destroy_display(_display);
    al_destroy_event_queue(_eventQueue);
    al_destroy_timer(_fpsTimer);
}