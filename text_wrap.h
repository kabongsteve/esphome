
using namespace esphome;
using namespace esphome::display;

void wrap_text(Display* it, int x, int y, const char* text, BaseFont* font, TextAlign align, float line_height) {
    // Calculate the bounds of a single space character
    int space_x1, space_y1, space_width, space_height;
    it->get_text_bounds(x, y, " ", font, align, &space_x1, &space_y1, &space_width, &space_height);

    // Break text into words
    std::vector<std::string> words;
    std::stringstream ss(text);
    std::string word;
    while (std::getline(ss, word, ' ')) {
        words.push_back(word);
    }

    // Initialize variables for the wrapped text
    int line_x = x;
    int line_y = y;
    int word_x1, word_y1, word_width, word_height;
    std::string line;

    // Iterate through the words and wrap them
    for (const auto& w : words) {
        it->get_text_bounds(line_x, line_y, w.c_str(), font, align, &word_x1, &word_y1, &word_width, &word_height);

        if (line_x + word_width >= it->get_width()) {
            // Print the current line and move to the next line
            it->printf(x, line_y, font, align, "%s", line.c_str());
            line_y += static_cast<int>(word_height * line_height);
            line_x = x;

            // Clear the line buffer
            line.clear();
        }

        // Add the word to the line buffer and move the cursor
        line += w;
        line_x += word_width + space_width;

        // If it's not the last word, add a space
        if (!line.empty() && &w != &words.back()) {
            line += " ";
        }
    }

    // Print the last line
    if (!line.empty()) {
        it->printf(x, line_y, font, align, "%s", line.c_str());
    }
}