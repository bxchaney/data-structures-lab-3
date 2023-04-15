#include<iostream>
#include<memory>
#include<string>
#include"huffman.h"
#include"huff_tree.h"
#include"freq_table.h"
#include"code_table.h"

Huffman::Huffman(FrequencyTable ft)
{
    huff_heap 
        = std::unique_ptr<HuffTree[]>(
            new HuffTree[ft.size()]
        );
    _heap_size = ft.size();
    _heap_max_size = ft.size();

    characters 
        = std::unique_ptr<std::string[]>(
            new std::string[ft.size()]
        );

    for (int i = 0; i< _heap_max_size; i++)
    {
        FrequencyTableRecord rec = ft.pop();
        huff_heap[i] = HuffTree{rec.str, rec.frequency};
        characters[i] = rec.str;
    }
    heapify();
    create_huff_tree();
}



void Huffman::heapify() 
{
    int k = _heap_size / 2;
    for (int i = k; i >= 0; i--)
    {
        min_heapify(i);
    }
}

void Huffman::min_heapify(int i)
{
    int left_child = 2 * i + 1;
    int right_child = 2 * (i + 1);
    int precedence = i;
    if (
        (left_child < _heap_size) 
        && 
        (huff_heap[left_child] < huff_heap[precedence])
        )
    {
        precedence = left_child;
    }
    if (
        (right_child < _heap_size) 
        && 
        (huff_heap[right_child] < huff_heap[precedence])
        )
    {
        precedence = right_child;
    }

    if (i != precedence)
    {
        swap(i, precedence);
        min_heapify(precedence);
    }
}

void Huffman::swap(int i, int j)
{
    HuffTree temp = huff_heap[i];
    huff_heap[i] = huff_heap[j];
    huff_heap[j] = temp;
}

void Huffman::create_huff_tree()
{
    while (_heap_size > 1)
    {
        HuffTree left = pop();
        HuffTree right = pop();

        HuffTree joined = left + right;
        push(joined);
    }
}

HuffTree Huffman::pop()
{
    HuffTree most_precedent_node = huff_heap[0];
    swap(0,_heap_size - 1);
    _heap_size--;
    percolate_down(0);
    return most_precedent_node;
}

void Huffman::percolate_down(int i)
{
    int left = 2 * i + 1;
    int right = 2 * (i + 1);
    int precedence = i;
    if (left < _heap_size && huff_heap[left] < huff_heap[precedence])
    {
        precedence = left;
    }
    if (right < _heap_size && huff_heap[right] < huff_heap[precedence])
    {
        precedence = right;
    }

    if (precedence != i)
    {
        swap(i, precedence);
        percolate_down(precedence);
    }
}

void Huffman::push(HuffTree& huff_tree)
{
    huff_heap[_heap_size] = huff_tree;
    _heap_size++;
    percolate_up(_heap_size-1);
}

void Huffman::percolate_up(int i)
{
    if (i == 0) return;
    int parent = (i - 1) / 2;
    if (huff_heap[i] < huff_heap[parent])
    {
        swap(i, parent);
        percolate_up(parent);
    }
}

std::ostream& operator<<(std::ostream& os, Huffman& huff)
{
    for (int i = 0; i < huff._heap_size; i++)
    {
        os << huff.huff_heap[i] << std::endl;
    }

    return os;
}

bool Huffman::is_character_encoding(std::string str)
{
    return huff_heap[0].is_character_encoding(str);
}

std::string& Huffman::get_character(std::string str)
{
    return huff_heap[0].get_character(str);
}

std::string Huffman::get_code(std::string c)
{
    return huff_heap[0].get_code(c);
}

EncodingTable Huffman::get_encoding_table()
{
    EncodingTable code_table {};
    for (int i = 0; i < _heap_max_size; i++)
    {
        std::string encoding = get_code(characters[i]);
        code_table.push(characters[i], encoding);
    }

    return code_table;
}

