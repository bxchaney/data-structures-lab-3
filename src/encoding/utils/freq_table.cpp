#include<memory>
#include<string>
#include"freq_table.h"

FrequencyTableRecord::FrequencyTableRecord(std::string& str, int frequency)
{
    this->str = str;
    this->frequency = frequency;
}

FrequencyTable::FrequencyTableNode::FrequencyTableNode(FrequencyTableRecord& rec)
{
    prev = nullptr;
    next = nullptr;
    record = std::move(rec);
}

FrequencyTable::FrequencyTableNode::~FrequencyTableNode()
{
    prev = nullptr;
    next = nullptr;
}

FrequencyTable::FrequencyTable()
{
    _size = 0;
    _head = nullptr;
    _tail = nullptr;
}

FrequencyTable::~FrequencyTable()
{
    while (_head != nullptr)
    {
        std::shared_ptr<FrequencyTableNode> curr_node = _head;
        _head = _head->next;

        curr_node->~FrequencyTableNode();
    }
    _tail = nullptr;
}

/// @brief FrequencyTable constructor is overloaded to read a frequency
/// table from an opened file via a std::istream.
/// @param is an open file of a frequency table.
FrequencyTable::FrequencyTable(std::istream& is)
{
    _size = 0;
    _head = nullptr;
    _tail = nullptr;
    // assuming the istream is of the form:
    // c - 123
    // where each line has exactly one character, " - ", then an integer
    // followed by a newline.
    std::string s;
    std::string _;
    int i; 

    // first check that the first character is not " "
    s = is.get();
    is >> _;
    is >> i;
    push(s,i);
    while (!is.eof())
    {
        is >> s;
        is >> _;
        is >> i;
        if (is.eof()) break;
        push(s,i);
    } 
}

FrequencyTable::FrequencyTable(const FrequencyTable& other)
{
    _head = nullptr;
    _tail = nullptr;
    _size = 0;
    std::shared_ptr<FrequencyTableNode> node = other._head;
    while (node != nullptr)
    {
        push(node->record);
        node = node->next;
    }
}
FrequencyTable& FrequencyTable::operator=(const FrequencyTable& other)
{
    _head = nullptr;
    _tail = nullptr;
    _size = 0;
    std::shared_ptr<FrequencyTableNode> node = other._head;
    while (node != nullptr)
    {
        push(node->record);
        node = node->next;
    }
    return *this;
}

std::ostream& operator<< (std::ostream& os, FrequencyTable& ft)
{
    std::shared_ptr<FrequencyTable::FrequencyTableNode> node = ft._head;
    while( node != nullptr)
    {
        os << node->record.str << " - " << node->record.frequency << std::endl;
        node = node->next;
    }
    return os;
}

/// @brief add a new record to the FrequencyTable
/// @param str a single character string
/// @param frequency str's frequency
void FrequencyTable::push(std::string str, int frequency)
{
    FrequencyTableRecord rec {str, frequency};
    std::shared_ptr<FrequencyTableNode> node 
        = std::shared_ptr<FrequencyTableNode>(new FrequencyTableNode(rec));
    if (_head == nullptr) // list is currently empty
    {
        _head = node;
        _tail = node;
    }
    else
    {
        _tail->next = node;
        node->prev = _tail;
        _tail = node;
    }
    _size++;
}

/// @brief Add a FrequencyTableRecord to the end of FrequencyTable
/// @param rec
void FrequencyTable::push(FrequencyTableRecord rec)
{
    std::shared_ptr<FrequencyTableNode> node 
        = std::shared_ptr<FrequencyTableNode>(new FrequencyTableNode(rec));
    if (_head == nullptr) // list is currently empty
    {
        _head = node;
        _tail = node;
    }
    else
    {
        _tail->next = node;
        node->prev = _tail;
        _tail = node;
    }
    _size++;
}

/// @brief remove and return the last node of FrequencyTable
/// @return a reference to a FrequencyTableRecord struct
FrequencyTableRecord& FrequencyTable::pop()
{
    std::shared_ptr<FrequencyTableNode> node;
    if (_size == 1) // last remaining element
    {
         node = _head;
        _head = nullptr;
        _tail = nullptr;
    }
    else 
    {
        node = _tail;
        _tail = _tail->prev;
        _tail->next = nullptr;
    }
    node->next = nullptr;
    node->prev = nullptr;
    _size--;
    return node->record;
}

int FrequencyTable::size()
{
    return _size;
}

bool FrequencyTable::is_empty()
{
    return _size == 0;
}