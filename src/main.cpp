#include<iostream>
#include<memory>
#include<string>
#include"encoding/utils/tree_map.h"
#include"encoding/utils/freq_table.h"
#include"encoding/utils/huff_tree.h"


int main()
{
    HuffTree h1 {"b", 1};
    HuffTree h2 {"a", 1};

    HuffTree h3 = h1 + h2;

    std::cout << h3 << std::endl;

    std::cout << (h1 < h2) << std::endl;


    // TreeMap map {};

    // map["a"]++;
    // map["b"];
    // map["c"];
    // map["d"];
    // map["f"]++;
    // map["g"];
    // map["h"];
    // map["i"];
    // map["j"];
    // map["k"];

    // FrequencyTable ft {};

    // map.preorder_traversal();

    // map.fill_freq_table(ft);

    // std::cout << ft << std::endl;

}