#include "fontatlas.hpp"

#include <utility>
#include <fstream>

namespace fontatlas {

std::unordered_map<uint32_t, glyph_data> read_glyph_data_file(const std::string &filepath)
{
    std::unordered_map<uint32_t, glyph_data> result;

    std::ifstream file(filepath, std::ios::binary);

    if (file.fail()) {
        // Failed to open file
        return result;
    }

    header header;
    file.read(reinterpret_cast<char*>(&header), sizeof(header));

    glyph_data_row row;
    for (uint32_t i = 0; i < header.num_of_chars_in_atlas; i++) {
        file.read(reinterpret_cast<char*>(&row), sizeof(glyph_data_row));
        if (file.eof()) break;
        result.insert(std::make_pair(row.char_code, row.data));
    }

    return result;
}

}
