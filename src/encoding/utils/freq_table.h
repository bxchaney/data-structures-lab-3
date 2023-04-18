/**
 * Frequency table is doubly-linked list storing a single character string
 * and its frequency at each node. This ADT is an abstraction of the frequency
 * table used to create a huffman tree with each node being a record in the
 * frequency table.
 * 
 */
#pragma once
#include<iostream>
#include<memory>
#include<string>

struct FrequencyTableRecord
{
    std::string str;
    int frequency;

    FrequencyTableRecord() = default;
    FrequencyTableRecord(std::string&, int);
};

class FrequencyTable
{
    private:

        struct FrequencyTableNode
        {
            std::shared_ptr<FrequencyTableNode> prev, next;
            FrequencyTableRecord record;

            FrequencyTableNode() = default;
            FrequencyTableNode(FrequencyTableRecord&);
            ~FrequencyTableNode();
        };

        std::shared_ptr<FrequencyTableNode> _head, _tail;
        int _size;

    public:     

        FrequencyTable();
        FrequencyTable(std::istream&);
        ~FrequencyTable();
        
        // Overloading copy constructor and assignment copy

        FrequencyTable(const FrequencyTable&);
        FrequencyTable& operator = (const FrequencyTable&);
        
        friend std::ostream& operator << (std::ostream&, FrequencyTable&);

        void push(std::string, int);
        void push(FrequencyTableRecord);
        FrequencyTableRecord& pop();
        int size();
        bool is_empty();
};