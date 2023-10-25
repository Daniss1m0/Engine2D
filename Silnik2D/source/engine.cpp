#include "engine.h"
#include "Point2D.h"
#include "LineSegment.h"

Engine::Engine(int width, int height, float fps) : screenWidth(width), screenHeight(height), FPS(fps) {}

bool Engine::Init() {
    if (!al_init()) {
        std::cerr << "Nie udało się zainicjować Allegro." << std::endl;
        return false;
    }

    al_install_keyboard();
    al_install_mouse();

    display = al_create_display(screenWidth, screenHeight);
    if (!display) {
        std::cerr << "Nie udało się utworzyć display." << std::endl;
        return false;
    }

    eventQueue = al_create_event_queue();
    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    al_register_event_source(eventQueue, al_get_mouse_event_source());

    fpsTimer = al_create_timer(1.0 / FPS);
    al_register_event_source(eventQueue, al_get_timer_event_source(fpsTimer));

    return true;
}

void Engine::Run() {
    bool running = true;
    al_start_timer(fpsTimer);

    PrimitiveRenderer& renderer = PrimitiveRenderer::getInstance();
    renderer.Initialize(display);

    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(eventQueue, &event);

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

        ALLEGRO_COLOR color = al_map_rgb(255, 0, 0); 
        renderer.DrawLineIncremental(300.0, 300.0, 400.0, 400.0, color, 10.0);
        renderer.DrawLine(400.0, 400.0, 500.0, 500.0, color, 10.0);

        Point2D start(100, 100);
        Point2D end(30, -150);
        LineSegment line(start, end);
        line.Draw(renderer, color, 2.0, true);
        //
        renderer.FlipDisplay();
    }
}

void Engine::Deinit() {
    al_destroy_display(display);
    al_destroy_event_queue(eventQueue);
    al_destroy_timer(fpsTimer);
}