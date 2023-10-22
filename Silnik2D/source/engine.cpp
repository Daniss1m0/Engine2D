#include "engine.h"

Engine::Engine(int width, int height) : screenWidth(width), screenHeight(height) {}

bool Engine::Init() {
    if (!al_init()) {
        std::cerr << "Nie udało się zainicjować Allegro." << std::endl;
        return false;
    }

    al_init_primitives_addon();
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

    timer = al_create_timer(1.0 / FPS);
    al_register_event_source(eventQueue, al_get_timer_event_source(timer));

    return true;
}

void Engine::Run() {
    bool running = true;
    al_start_timer(timer);

    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(eventQueue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }
        else if (event.type == ALLEGRO_EVENT_TIMER) {

        }
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {

        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

        }

        al_clear_to_color(al_map_rgb(255, 255, 255));

        al_flip_display();
    }
}

void Engine::Deinit() {
    al_destroy_display(display);
    al_destroy_event_queue(eventQueue);
    al_destroy_timer(timer);
}