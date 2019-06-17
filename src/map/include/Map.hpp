#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include <optional>

namespace algorithms {

template <typename Key, typename Value, typename Comparator = std::less<Key>>
class Map {
public:
    using KeyOrNull = std::optional<Key>;

    using ValueOrNull = std::optional<Value>;

    using Keys = std::vector<Key>;

public:
    virtual ~Map() = default;

    virtual void put(const Key& key, Value&& value) = 0;

    virtual Value& get(const Key& key) = 0;

    virtual const Value& get(const Key& key) const = 0;

    virtual ValueOrNull pick(const Key& key) const = 0;

    virtual bool contains(const Key& key) const = 0;

    virtual void erase(const Key& key) = 0;

    virtual void eraseMin() = 0;

    virtual void eraseMax() = 0;

    virtual bool empty() const = 0;

    virtual std::size_t size() const = 0;

    virtual std::size_t size(Key lo, Key hi) const = 0;

    virtual std::size_t rank(const Key& key) const = 0;

    virtual Key min() const = 0;

    virtual Key max() const = 0;

    virtual KeyOrNull floor(const Key& key) const = 0;

    virtual KeyOrNull ceiling(const Key& key) const = 0;

    virtual Keys keys() const = 0;

    virtual Keys keys(Key lo, Key hi) const = 0;
};

} // namespace algorithms

#endif // MAP_HPP
