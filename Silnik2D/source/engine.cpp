#include "engine.h"

Engine::Engine(int width, int height, float fps) : _screenWidth(width), _screenHeight(height), _FPS(fps) {}

bool Engine::Init() {
    if (!al_init()) {
        std::cerr << "Nie udało się zainicjować Allegro." << std::endl;
        return false;
    }

    al_install_keyboard();
    al_install_mouse();

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
    
    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(_eventQueue, &event);

        switch(event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE: {
                running = false;
                break;
            }
       
            case ALLEGRO_EVENT_TIMER: {
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

        ALLEGRO_COLOR color = al_map_rgb(255, 255, 255);

        Point2D start(100, 300);
        Point2D end(30, -150);

        LineSegment line(start, end);
        line.Draw(renderer, color, 1.0f, true);

        //renderer.DrawLineIncremental(start, end, color, 10.0);
        //renderer.DrawLine(start, end, color, 10.0);

        Point2D point1(700.0f, 300.0f);
        //renderer.DrawPixel(point1, color);

        Point2D point2(800.0f, 300.0f);
        //renderer.DrawPixel(point2, color);

        renderer.DrawLine(point1, point2, color, 5.0);
        //renderer.DrawPolyline(renderer.GenerateSquareSpiralPoints(400.0f, 300.0f, 404, 2.0f), color, 1.0);

        renderer.FlipDisplay();
    }
}

void Engine::Deinit() {
    al_destroy_display(_display);
    al_destroy_event_queue(_eventQueue);
    al_destroy_timer(_fpsTimer);
}