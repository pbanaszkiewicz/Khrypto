/*  This file is part of Khrypto.

    Khrypto is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Khrypto is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Khrypto.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef HUFFMAN_H
#define HUFFMAN_H


#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;


typedef struct HuffmanCode {
    char c;
    int v;
} HUFFMAN_CODE;


bool compare_huffman_codes(HUFFMAN_CODE a, HUFFMAN_CODE b) {
    return (a.v > b.v);
}


void huffman_code(string text) {
    vector< HUFFMAN_CODE > codes;
    //codes.clear();

    map< char, unsigned int >  codes_map;
    int v;
    for (int i=0; i<text.length(); i++) {
        v = codes_map[ text[i] ];
        codes_map[ text[i] ] = ++v;
    }

    map< char, unsigned int >::iterator iter;
    HUFFMAN_CODE hc;
    for (iter = codes_map.begin(); iter != codes_map.end(); iter++) {
        hc.c = iter->first;
        hc.v = iter->second;
        codes.push_back(hc);
    }

    sort(codes.begin(), codes.end(), compare_huffman_codes);


}


void huffman_compress(string text, vector< HUFFMAN_CODE > codes, string &result,
                      unsigned &length) {
    //
}


#endif // HUFFMAN_H
