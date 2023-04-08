#include<iostream>
#include<memory>
#include<string>
#include"encoding/utils/tree_map.h"
#include"encoding/utils/freq_table.h"


int main()
{
    
    TreeMap map {};

    map["a"]++;
    map["b"];
    map["c"];
    map["d"];
    map["f"]++;
    map["g"];
    map["h"];
    map["i"];
    map["j"];
    map["k"];

    FrequencyTable ft {};

    map.preorder_traversal();

    map.fill_freq_table(ft);

    std::cout << ft << std::endl;

}