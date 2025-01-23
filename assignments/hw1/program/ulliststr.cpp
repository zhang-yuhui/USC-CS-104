#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

// Constructor to initialize an empty list
ULListStr::ULListStr()
{
    head_ = NULL;  // Pointer to the first item
    tail_ = NULL;  // Pointer to the last item
    size_ = 0;     // Size of the list
}

// Destructor to clean up all items in the list
ULListStr::~ULListStr()
{
    clear();  // Calls the clear method to delete items
}

// Check if the list is empty
bool ULListStr::empty() const
{
    return size_ == 0;  // Returns true if size is 0
}

// Return the size of the list
size_t ULListStr::size() const
{
    return size_;
}

// Set the value at a specific location
void ULListStr::set(size_t loc, const std::string& val)
{
    std::string* ptr = getValAtLoc(loc);
    if (ptr == NULL) {
        throw std::invalid_argument("Bad location");  // Invalid location
    }
    *ptr = val;  // Set the value at the specified location
}

// Get the value at a specific location (non-const)
std::string& ULListStr::get(size_t loc)
{
    std::string* ptr = getValAtLoc(loc);
    if (ptr == NULL) {
        throw std::invalid_argument("Bad location");  // Invalid location
    }
    return *ptr;  // Return reference to the value
}

// Get the value at a specific location (const)
std::string const & ULListStr::get(size_t loc) const
{
    std::string* ptr = getValAtLoc(loc);
    if (ptr == NULL) {
        throw std::invalid_argument("Bad location");  // Invalid location
    }
    return *ptr;  // Return reference to the value
}

// Clear the list and free memory
void ULListStr::clear()
{
    while (head_ != NULL) {
        Item *temp = head_->next;  // Store the next item
        delete head_;               // Delete the current head
        head_ = temp;               // Move to the next item
    }
    tail_ = NULL;  // Reset tail
    size_ = 0;     // Reset size
}

// Get a pointer to the value at a specific location
std::string* ULListStr::getValAtLoc(size_t loc) const
{
    std::string* ans = NULL;  // Pointer to store the result
    size_t count = 0;         // Counter to track the index
    
    for (auto i = head_; i; i = i->next) {  // Iterate through items
        for (size_t j = i->first; j < i->last; j++, count++) {  // Iterate through values
            if (count == loc) {
                return &(i->val[j]);  // Return pointer to the value
            }
        }
    }
    
    return ans;  // Return nullptr if location is invalid
}

// Get the front value of the list (const)
std::string const & ULListStr::front() const
{
    if (size_ == 0)
        return "";  // Return empty string if list is empty
    return head_->val[head_->first];  // Return the first value
}

// Get the back value of the list (const)
std::string const & ULListStr::back() const
{
    if (size_ == 0)
        return "";  // Return empty string if list is empty
    return tail_->val[tail_->last - 1];  // Return the last value
}

// Add a value to the end of the list
void ULListStr::push_back(const std::string& val)
{
    if (!size_) {  // If the list is empty
        auto tmp = new Item;  // Create a new item
        head_ = tail_ = tmp;  // Set head and tail to the new item
    }
    
    if (tail_->last == ARRSIZE) {  // If the current item is full
        auto tmp = new Item;  // Create a new item
        tail_->next = tmp;  // Link new item to the current tail
        tmp->prev = tail_;  // Set the previous pointer
        tail_ = tmp;        // Update tail to the new item
    }
    
    tail_->last++;                // Increment the count of values in the current item
    tail_->val[tail_->last - 1] = val;  // Set the new value
    size_++;                      // Increment size of the list
}

// Remove the value from the end of the list
void ULListStr::pop_back()
{
    if (!size_)  // If the list is empty
        return;  // Nothing to pop

    size_--;             // Decrement size
    tail_->last--;      // Remove last value from the current item

    // If the current item is now empty
    if (tail_->last == tail_->first) {
        if (size_ == 0) {  // Check if the list is now empty
            delete tail_;  // Delete the last item
            head_ = tail_ = NULL;  // Reset head and tail
        } else {
            tail_ = tail_->prev;  // Move tail back to the previous item
            delete tail_->next;    // Delete the now empty tail item
            tail_->next = NULL;    // Reset next pointer
        }
    }
}

// Add a value to the front of the list
void ULListStr::push_front(const std::string& val)
{
    if (!size_) {  // If the list is empty
        auto tmp = new Item;  // Create a new item
        head_ = tail_ = tmp;  // Set head and tail to the new item
        head_->first = head_->last = ARRSIZE;  // Initialize indices
    }
    
    if (head_->first == 0) {  // If the current item is full
        auto tmp = new Item();  // Create a new item
        head_->prev = tmp;      // Link the new item in front of head
        tmp->next = head_;      // Link the new item to head
        head_ = tmp;            // Update head to the new item
        head_->first = head_->last = ARRSIZE;  // Initialize indices
    }
    
    head_->first--;                             // Decrement the first index
    head_->val[head_->first] = val;             // Set the new value
    size_++;                                     // Increment size of the list
}

// Remove the value from the front of the list
void ULListStr::pop_front()
{
    if (!size_)  // If the list is empty
        return;  // Nothing to pop

    size_--;            // Decrement size
    head_->first++;    // Remove first value from the current item

    // If the current item is now empty
    if (head_->last == head_->first) {
        if (size_ == 0) {  // Check if the list is now empty
            delete tail_;  // Delete the last item
            head_ = tail_ = NULL;  // Reset head and tail
        } else {
            head_ = head_->next;  // Move head to the next item
            delete head_->prev;    // Delete the now empty head item
            head_->prev = NULL;    // Reset previous pointer
        }
    }
}