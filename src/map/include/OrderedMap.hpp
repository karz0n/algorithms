#ifndef ELEMENTARYMAP_HPP
#define ELEMENTARYMAP_HPP

#include <algorithm>
#include <vector>
#include <utility>

#include "Map.hpp"

namespace algorithms {

template <typename Key, typename Value, typename Comparator = std::less<Key>>
class OrderedMap : public Map<Key, Value, Comparator> {
public:
    using KeyOrNull = typename Map<Key, Value, Comparator>::KeyOrNull;
    using Keys = std::vector<Key>;

    using ValueOrNull = typename Map<Key, Value, Comparator>::ValueOrNull;
    using Values = std::vector<ValueOrNull>;

    void put(const Key& key, Value&& value) override
    {
        auto it
            = std::find_if(_keys.cbegin(), _keys.cend(), [this, &key](const Key& k) { return (compare(k, key) >= 0); });

        if (it == _keys.cend()) {
            _keys.push_back(key);
            _values.push_back(std::make_optional<Value>(std::forward<Value>(value)));
        }
        else {
            std::size_t r = std::distance(_keys.cbegin(), it);
            if (compare(key, _keys[r]) == 0) {
                _values[r] = std::make_optional<Value>(std::forward<Value>(value));
            }
            else {
                _keys.insert(it, key);
                _values.insert(_values.cbegin() + r, std::make_optional<Value>(std::forward<Value>(value)));
            }
        }
    }

    Value& get(const Key& key) override
    {
        if (empty()) {
            throw std::runtime_error{"Item not found"};
        }
        std::size_t r = rank(key);
        if (r >= _keys.size() || _keys[r] != key) {
            throw std::runtime_error{"Item not found"};
        }
        return _values[r].value();
    }

    const Value& get(const Key& key) const override
    {
        if (empty()) {
            throw std::runtime_error{"Item not found"};
        }
        std::size_t r = rank(key);
        if (r >= _keys.size() || _keys[r] != key) {
            throw std::runtime_error{"Item not found"};
        }
        return _values[r].value();
    }

    ValueOrNull pick(const Key& key) const override
    {
        if (empty()) {
            return std::nullopt;
        }
        std::size_t r = rank(key);
        if (r >= _keys.size() || _keys[r] != key) {
            return std::nullopt;
        }
        return _values[r];
    }

    bool contains(const Key& key) const override
    {
        if (empty()) {
            return false;
        }

        std::size_t r = rank(key);
        return (r < _keys.size() && compare(key, _keys[r]) == 0);
    }

    void erase(const Key& key) override
    {
        if (empty()) {
            return;
        }

        std::size_t r = rank(key);
        if (r < _keys.size() && compare(key, _keys[r]) == 0) {
            _keys.erase(_keys.cbegin() + r);
            _values.erase(_values.cbegin() + r);
        }
    }

    void eraseMin() override
    {
        if (empty()) {
            throw std::runtime_error{"Empty map"};
        }
        erase(min());
    }

    void eraseMax() override
    {
        if (empty()) {
            throw std::runtime_error{"Empty map"};
        }
        erase(max());
    }

    bool empty() const override
    {
        return _keys.empty();
    }

    std::size_t size() const override
    {
        return _keys.size();
    }

    std::size_t rank(const Key& key) const override
    {
        int lo = 0;
        int hi = _keys.size() - 1;
        while (lo <= hi) {
            std::size_t mi = lo + (hi - lo) / 2;
            int c = compare(key, _keys[mi]);
            if (c < 0) {
                hi = mi - 1;
            }
            else if (c > 0) {
                lo = mi + 1;
            }
            else {
                return mi;
            }
        }
        return lo;
    }

    Key min() const override
    {
        if (empty()) {
            throw std::runtime_error{"Map is empty"};
        }
        return _keys.front();
    }

    Key max() const override
    {
        if (empty()) {
            throw std::runtime_error{"Map is empty"};
        }
        return _keys.back();
    }

    KeyOrNull floor(const Key& key) const
    {
        if (empty()) {
            return std::nullopt;
        }

        auto r = rank(key);
        if (r < _keys.size() && compare(key, _keys[r]) == 0) {
            return std::make_optional<Key>(_keys[r]);
        }
        return (r == 0) ? std::nullopt : std::make_optional<Key>(_keys[r - 1]);
    }

    KeyOrNull ceiling(const Key& key) const
    {
        if (empty()) {
            return std::nullopt;
        }

        auto r = rank(key);
        return (r == _keys.size()) ? std::nullopt : std::make_optional<Key>(_keys[r]);
    }

private:
    int compare(const Key& key1, const Key& key2) const
    {
        if (_comparator(key1, key2)) {
            return -1;
        }
        if (_comparator(key2, key1)) {
            return +1;
        }
        return 0;
    }

private:
    Comparator _comparator;
    Keys _keys;
    Values _values;
};

} // namespace algorithms

#endif // ELEMENTARYMAP_HPP
