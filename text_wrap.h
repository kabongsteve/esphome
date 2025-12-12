#pragma once

#include "esphome/components/display/display_buffer.h"

void wrap_text(
    esphome::display::Display* it, int x, int y,
    const char* text, esphome::display::BaseFont* font,
    esphome::display::TextAlign align, float line_height
);