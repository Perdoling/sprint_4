#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
template <typename Iterator>
class IteratorRange {
    public:
    IteratorRange(Iterator& it_begin,Iterator it_end) 
    :begin_(it_begin),
    end_(it_end),
    size_page_(distance(it_begin, it_end))
    {
    }
    Iterator begin() const {
        return begin_;
    }

    Iterator end() const {
        return end_;
    }

    std::size_t size() const {
        return size_page_;
    }

    private:
    Iterator begin_, end_;
    std::size_t size_page_;

};

template <typename Iterator>
class Paginator {
    public:
    //Paginator(begin(c), end(c), page_size) 
    Paginator(Iterator begin, Iterator end, std::size_t page_size) {
        for (std::size_t left = distance(begin, end); left > 0;) {
            const size_t current_page_size = std::min(page_size, left);
            const Iterator current_page_end = next(begin, current_page_size);
            page_.push_back({begin, current_page_end});

            left -= current_page_size;
            begin = current_page_end;
        }
    }

    auto begin() const {
        return page_.begin();
    }

    auto end() const {
        return page_.end();
    }

    size_t size() const {
        return page_.size();
    }
    private:
    std::vector<IteratorRange<Iterator>> page_;
        // тело класса
}; 

template <typename Container>
auto Paginate(const Container& c, size_t page_size) {
    return Paginator(begin(c), end(c), page_size);
}

template <typename Iterator>
std::ostream& operator<<(std::ostream& out ,const IteratorRange<Iterator>& it ) {

    for(Iterator a = it.begin(); a != it.end(); ++a) {
        out << *a;
    }
    return out;
}