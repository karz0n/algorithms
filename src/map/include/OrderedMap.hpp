#ifndef ELEMENTARYMAP_HPP
#define ELEMENTARYMAP_HPP

#include <algorithm>
#include <vector>
#include <utility>
#include <optional>

namespace algorithms {

template <typename Key,
          typename T,
          typename Comparator = std::less<Key>>
class OrderedMap {
public:
    using KeyOrNull = std::optional<Key>;
    using Keys = std::vector<Key>;
    using Value = std::optional<T>;
    using Values = std::vector<Value>;

    void put(const Key& key, const T& value)
    {
        auto it = std::find_if(_keys.cbegin(), _keys.cend(), [this, &key] (const Key& k) {
            return (compare(k, key) >= 0);
        });

        if (it == _keys.cend()) {
            _keys.push_back(key);
            _values.push_back(std::make_optional<T>(value));
        }
        else {
            std::size_t r = std::distance(_keys.cbegin(), it);
            if (compare(key, _keys[r]) == 0) {
                _values[r] = std::make_optional<T>(value);
            }
            else {
                _keys.insert(it, key);
                _values.insert(_values.cbegin() + r, std::make_optional<T>(value));
            }
        }
    }

    Value get(const Key& key) const
    {
        if (empty()) {
            return std::nullopt;
        }

        std::size_t r = rank(key);
        if (r < _keys.size() && compare(key, _keys[r]) == 0) {
            return _values[r];
        }
        return std::nullopt;
    }

    bool contains(const Key& key) const
    {
        if (empty()) {
            return false;
        }

        std::size_t r = rank(key);
        return (r < _keys.size() && compare(key, _keys[r]) == 0);
    }

    void erase(const Key& key)
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

    bool empty() const
    {
        return _keys.empty();
    }

    std::size_t size() const
    {
        return _keys.size();
    }

    std::size_t size(const Key& lo, const Key& hi)
    {
        return keys(lo, hi).size();
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
        return (r == 0)
            ? std::nullopt
            : std::make_optional<Key>(_keys[r - 1]);
    }

    KeyOrNull ceiling(const Key& key) const
    {
        if (empty()) {
            return std::nullopt;
        }

        auto r = rank(key);
        return (r == _keys.size())
            ? std::nullopt
            : std::make_optional<Key>(_keys[r]);
    }

    KeyOrNull select(std::size_t n)
    {
        if (empty() || n >= _keys.size()) {
            return std::nullopt;
        }

        return _keys[n - 1];
    }

    Keys keys(const Key& lo, const Key& hi)
    {
        if (empty()) {
            return Keys{};
        }

        Keys keys;
        for (std::size_t i = rank(lo); i < rank(hi); ++i) {
            keys.push_back(_keys[i]);
        }
        if (contains(hi)) {
            keys.push_back(_keys[rank(hi)]);
        }
        return keys;
    }

    KeyOrNull min() const
    {
        if (empty()) {
            return std::nullopt;
        }

        return std::make_optional<Key>(_keys.front());
    }

    KeyOrNull max() const
    {
        if (empty()) {
            return std::nullopt;
        }

        return std::make_optional<Key>(_keys.back());
    }

private:
    std::size_t rank(const Key& key) const
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
