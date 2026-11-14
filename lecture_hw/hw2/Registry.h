#ifndef MIPT_CPP_REGISTRY_H
#define MIPT_CPP_REGISTRY_H

#include <cstddef>
#include <utility>
#include <vector>

template <typename T>
class Registry {
public:
    void add(T entry) {
        entries_.push_back(std::move(entry));
    }

    void erase(std::size_t index) {
        entries_.erase(entries_.begin() + index);
    }

    std::size_t size() const {
        return entries_.size();
    }

    const T& operator[](std::size_t index) const {
        return entries_.at(index);
    }

private:
    std::vector<T> entries_;
};

#endif // MIPT_CPP_REGISTRY_H
