/*
 * Copyright (C) Francis Gagné 2015 <fragag1@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <sstream>
#include "comper.h"
#include "enigma.h"
#include "kosinski.h"
#include "nemesis.h"
#include "saxman.h"

template <typename Operation>
static bool perform(char *input, size_t input_size, char **output, size_t *output_size, Operation operation) {
    std::istringstream input_stream(std::string(input, input_size));
    std::stringstream output_stream;
    if (operation(input_stream, output_stream)) {
        std::string output_string(output_stream.str());
        *output_size = output_string.size();
        *output = static_cast<char *>(malloc(*output_size));
        memcpy(*output, output_string.data(), *output_size);
        return true;
    }
    
    return false;
}

extern "C" {
    bool comper_decode(char *input, size_t input_size, char **output, size_t *output_size) {
        return perform(input, input_size, output, output_size, [] (std::istream &is, std::iostream &os) { return comper::decode(is, os); });
    }

    bool comper_encode(char *input, size_t input_size, char **output, size_t *output_size) {
        return perform(input, input_size, output, output_size, comper::encode);
    }

    bool enigma_decode(char *input, size_t input_size, char **output, size_t *output_size) {
        return perform(input, input_size, output, output_size, [] (std::istream &is, std::ostream &os) { return enigma::decode(is, os); });
    }

    bool enigma_encode(char *input, size_t input_size, char **output, size_t *output_size) {
        return perform(input, input_size, output, output_size, [] (std::istream &is, std::ostream &os) { return enigma::encode(is, os); });
    }

    bool kosinski_decode(char *input, size_t input_size, char **output, size_t *output_size) {
        return perform(input, input_size, output, output_size, [] (std::istream &is, std::iostream &os) { return kosinski::decode(is, os); });
    }

    bool kosinski_encode(char *input, size_t input_size, char **output, size_t *output_size) {
        return perform(input, input_size, output, output_size, [] (std::istream &is, std::ostream &os) { return kosinski::encode(is, os); });
    }

    bool moduled_kosinski_decode(char *input, size_t input_size, char **output, size_t *output_size) {
        return perform(input, input_size, output, output_size, [] (std::istream &is, std::iostream &os) { return kosinski::decode(is, os, 0, true); });
    }

    bool moduled_kosinski_encode(char *input, size_t input_size, char **output, size_t *output_size) {
        return perform(input, input_size, output, output_size, [] (std::istream &is, std::ostream &os) { return kosinski::encode(is, os, 8192, 256, true); });
    }

    bool nemesis_decode(char *input, size_t input_size, char **output, size_t *output_size) {
        return perform(input, input_size, output, output_size, [] (std::istream &is, std::ostream &os) { return nemesis::decode(is, os); });
    }

    bool nemesis_encode(char *input, size_t input_size, char **output, size_t *output_size) {
        return perform(input, input_size, output, output_size, nemesis::encode);
    }

    bool saxman_decode(char *input, size_t input_size, char **output, size_t *output_size, size_t compressed_size) {
        return perform(input, input_size, output, output_size, [compressed_size] (std::istream &is, std::iostream &os) { return saxman::decode(is, os, 0, compressed_size); });
    }

    bool saxman_encode(char *input, size_t input_size, char **output, size_t *output_size, bool with_size) {
        return perform(input, input_size, output, output_size, [with_size] (std::istream &is, std::ostream &os) { return saxman::encode(is, os, with_size); });
    }
}
