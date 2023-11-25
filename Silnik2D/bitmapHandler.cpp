#include "bitmapHandler.h"

BitmapHandler::BitmapHandler() {
	bitmap = al_create_bitmap(1, 1);
	if (!bitmap) {
		std::cerr << "Failed to create bitmap!" << std::endl;
	}
}

BitmapHandler::~BitmapHandler() {
	if (bitmap) {
		al_destroy_bitmap(bitmap);
	}
}

int BitmapHandler::GetWidth() const {
	return al_get_bitmap_width(bitmap);
}

int BitmapHandler::GetHeight() const {
	return al_get_bitmap_height(bitmap);
}

bool BitmapHandler::LoadFromFile(const char* filename) {
	ALLEGRO_BITMAP* loadedBitmap = al_load_bitmap(filename);
	if (loadedBitmap) {
		if (bitmap) {
			al_destroy_bitmap(bitmap);
		}
		bitmap = loadedBitmap;
		return true;
	}
	else {
		std::cerr << "Failed to load bitmap from file: " << filename << std::endl;
		return false;
	}
}

bool BitmapHandler::SaveToFile(const char* filename) {
	if (bitmap) {
		return al_save_bitmap(filename, bitmap);
	}
	else {
		std::cerr << "Cannot save. Bitmap is not initialized." << std::endl;
		return false;
	}
}

void BitmapHandler::CopyFrom(const BitmapHandler& source) { //
	if (source.bitmap) {
		al_set_target_bitmap(bitmap);
		al_draw_bitmap(source.bitmap, 0, 0, 0);
		al_set_target_backbuffer(al_get_current_display());
	}
	else {
		std::cerr << "Cannot copy. Source bitmap is not initialized." << std::endl;
	}
}


void BitmapHandler::Draw(float x, float y, float width, float height) {
	if (bitmap) {
		al_draw_scaled_bitmap(bitmap, 0, 0, al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap),x, y, width, height, 0);
	}
	else {
		std::cerr << "Cannot draw. Bitmap is not initialized." << std::endl;
	}
}