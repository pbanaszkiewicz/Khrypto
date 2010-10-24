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
