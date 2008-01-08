#ifndef RANGE_ITERATOR_HPP
#define RANGE_ITERATOR_HPP

#include <iterator>
template<typename DATAITER, typename INDEXITER>
class RangeIterator {
private:
  DATAITER data_iterator_;
  const INDEXITER index_iterator_;
  size_t current_index_;
public:
  RangeIterator(const DATAITER data_iterator, const INDEXITER index_iterator);

  RangeIterator<DATAITER,INDEXITER>& operator++();
  RangeIterator<DATAITER,INDEXITER> operator++(int i);
  RangeIterator<DATAITER,INDEXITER>& operator--();
  RangeIterator<DATAITER,INDEXITER> operator--(int i);

  RangeIterator<DATAITER,INDEXITER>& operator+=(int i);
  RangeIterator<DATAITER,INDEXITER>& operator-=(int i);
  typename std::iterator_traits<DATAITER>::value_type operator*();
};

template<typename DATAITER, typename INDEXITER>
RangeIterator<DATAITER,INDEXITER>::RangeIterator(const DATAITER data_iterator, const INDEXITER index_iterator) :
  data_iterator_(data_iterator),
  index_iterator_(index_iterator),
  current_index_(0) {}

template<typename DATAITER, typename INDEXITER>
RangeIterator<DATAITER,INDEXITER>& RangeIterator<DATAITER,INDEXITER>::operator++() {
    ++current_index_;
    return *this;
}

template<typename DATAITER, typename INDEXITER>
RangeIterator<DATAITER,INDEXITER> RangeIterator<DATAITER,INDEXITER>::operator++(int i) {
  RangeIterator<DATAITER,INDEXITER> tmp = *this;
  ++*this;
  return tmp;
}

template<typename DATAITER, typename INDEXITER>
RangeIterator<DATAITER,INDEXITER>& RangeIterator<DATAITER,INDEXITER>::operator--() {
  --current_index_;
  return *this;
}

template<typename DATAITER, typename INDEXITER>
RangeIterator<DATAITER,INDEXITER> RangeIterator<DATAITER,INDEXITER>::operator--(int i) {
  RangeIterator<DATAITER,INDEXITER> tmp = *this;
  --*this;
  return tmp;
}

template<typename DATAITER, typename INDEXITER>
RangeIterator<DATAITER,INDEXITER>& RangeIterator<DATAITER,INDEXITER>::operator+=(int i) {
  current_index_ += i;
  return *this;
}

template<typename DATAITER, typename INDEXITER>
RangeIterator<DATAITER,INDEXITER>& RangeIterator<DATAITER,INDEXITER>::operator-=(int i) {
  current_index_ -= i;
  return *this;
}

template<typename DATAITER, typename INDEXITER>
typename std::iterator_traits<DATAITER>::value_type RangeIterator<DATAITER,INDEXITER>::operator*() {
  return data_iterator_[ index_iterator_[current_index_] ];
}

#endif // RANGE_ITERATOR_HPP
