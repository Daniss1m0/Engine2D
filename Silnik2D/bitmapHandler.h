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
    int GetWidth() const;
    int GetHeight() const;
    bool LoadFromFile(const char* filename);
    bool SaveToFile(const char* filename);
    void CopyFrom(const BitmapHandler& source);
    void Draw(float x, float y, float width, float height);
};