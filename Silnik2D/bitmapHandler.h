#pragma once

#include <allegro5/allegro_image.h>
#include <allegro5/allegro.h>
#include <iostream>

class BitmapHandler {
private:
    ALLEGRO_BITMAP* bitmap;

public:
    BitmapHandler();
    ~BitmapHandler();
    bool LoadFromFile(const char* filename);
    bool SaveToFile(const char* filename);
    void CopyFrom(const BitmapHandler& source);
    int GetWidth() const;
    int GetHeight() const;
    void Draw(float x, float y);
};