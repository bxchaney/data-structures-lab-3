#include<iostream>
#include<memory>
#include<string>
#include"huffman.h"
#include"huff_tree.h"
#include"freq_table.h"
#include"code_table.h"

/// @brief Huffman constructor overloaded to allow constructing with 
/// a frequency table provided at initialization. This is equivalent to
/// providing a FrequencyTable via the from_freq method.
/// @param ft a non-empty FrequencyTable
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

/// @brief Builds a new huffman tree from the provided FrequencyTable
/// and stores internally
/// @param ft a non-empty FrequencyTable
void Huffman::from_freq(FrequencyTable ft)
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


/// @brief this is a wrapper method to the recursive min_heapify that
/// converts the array of HuffTree's to a heap as a part of building the
/// huffman tree
void Huffman::heapify() 
{
    int k = _heap_size / 2;
    for (int i = k; i >= 0; i--)
    {
        min_heapify(i);
    }
}

/// @brief a recursive method used to create the heap used to build the
/// huffman tree
/// @param i the index of the node being considered
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

/// @brief this method swaps the HuffTree's at indexes i and j in huff_heap
/// @param i 
/// @param j 
void Huffman::swap(int i, int j)
{
    HuffTree temp = huff_heap[i];
    huff_heap[i] = huff_heap[j];
    huff_heap[j] = temp;
}

/// @brief This method builds the huffman tree by repeatedly poping the two
/// elements with the lowest precedence, joining them together, then re-adding
/// them to the priority queue.
void Huffman::create_huff_tree()
{
    while (_heap_size > 1)
    {
        HuffTree left = pop();
        HuffTree right = pop();

        HuffTree joined = left + right;
        push(joined);
    }
    for (int i = _heap_max_size - 1; i >= 0; i--)
    {
        std::string encoding = get_code(characters[i]);
        code_table.push(characters[i], encoding);
    }
}

/// @brief This method removes the lowest precedence HuffTree from the priority queue
/// and brings the next least priority element to the front
/// @return 
HuffTree Huffman::pop()
{
    HuffTree most_precedent_node = huff_heap[0];
    swap(0,_heap_size - 1);
    _heap_size--;
    percolate_down(0);
    return most_precedent_node;
}

/// @brief Called after an element is removed from the priority queue, this
/// method percolates the element at index i down until the priority queue 
/// is once again a min heap
/// @param i 
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

/// @brief this method adds a HuffTree to the queue
/// @param huff_tree 
void Huffman::push(HuffTree& huff_tree)
{
    huff_heap[_heap_size] = huff_tree;
    _heap_size++;
    percolate_up(_heap_size-1);
}

/// @brief This method is called when a new item is added to the queue. It
/// swaps elements until the heap is once again a min-heap
/// @param i 
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

/// @brief this method returns true when the provided string is a valid
/// huffman encoding
/// @param str a string of 0's and 1's represting a possible huffman code
/// @return 
bool Huffman::is_character_encoding(std::string& str)
{
    return huff_heap[0].is_character_encoding(str);
}

/// @brief returns the character for the provided huffman code string
/// @param str a string of 0's and 1's
/// @return 
std::string& Huffman::get_character(std::string& str)
{
    return huff_heap[0].get_character(str);
}

/// @brief returns the huffman code for the provided character
/// @param c a single character
/// @return 
std::string Huffman::get_code(std::string c)
{
    return huff_heap[0].get_code(c);
}

/// @brief returns a reference to the member EncodingTable. This is used
/// to write the EncodingTable to the console
/// @return 
EncodingTable& Huffman::get_encoding_table()
{
    return code_table;
}

/// @brief returns a reference to the internally stored huffman tree. This
/// is used to write the huffman tree to the console.
/// @return 
HuffTree& Huffman::get_tree()
{
    return huff_heap[0];
}

