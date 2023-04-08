#include<iostream>
#include<memory>
#include<string>
#include"tree_map.h"


int main()
{
    
    TreeMap map {};

    map["s"];
    map["s"]++;

    std::cout << map["s"].frequency << std::endl;

}