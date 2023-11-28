﻿//zrobic hierarchi klass (np. jak w instrukcji 4 pierwsze zadanie)

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
    ply.LoadFromFile("player.png");
    ply.Move(Vector2(400.0f, 500.0f));

    struct KeysPushed
    {
        bool KeyA = false;
        bool KeyB = false;
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
                if (KeysPushed.KeyA)
                    ply.Move(Vector2(-3.0f, 0.0f));
                else if (KeysPushed.KeyB)
                    ply.Move(Vector2(3.0f, 0.0f));

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
                }
                break;
            }

            case ALLEGRO_EVENT_KEY_UP:
                KeysPushed.KeyA = false;
                KeysPushed.KeyB = false;
                break;
        }

        renderer.ClearScreen();
        ply.Draw();
        renderer.FlipDisplay();
    }
}

void Engine::Deinit() {
    al_destroy_display(_display);
    al_destroy_event_queue(_eventQueue);
    al_destroy_timer(_fpsTimer);
}