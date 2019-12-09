#pragma once

#include <functional>
#include <optional>
#include <vector>

namespace algorithms {

template<typename Key, typename Value, typename Compare = std::less<Key>>
class Tree {
public:
    enum class TraverseOrder {
        DepthPreOrder,
        DepthInOrder,
        DepthPostOrder,
        Breadth
    };

    using KeyType = Key;
    using ValueType = Value;
    using KeyTypeOrNull = std::optional<KeyType>;
    using ValueTypeOrNull = std::optional<ValueType>;
    using KeysType = std::vector<KeyType>;
    using Callback = std::function<void(const KeyType& key, ValueType& value)>;

public:
    virtual ~Tree() = default;

    /**
     * Puts element with given key and value.
     *
     * @param key The key of element
     * @param value The value of element
     */
    virtual void put(const KeyType& key, const ValueType& value) = 0;

    /**
     * Get element with given key.
     *
     * @param key The target key
     *
     * @return The reference to element
     */
    virtual ValueType& get(const KeyType& key) = 0;

    /**
     * Get element with given key.
     *
     * @param key The target key
     *
     * @return The reference to element
     */
    virtual const ValueType& get(const KeyType& key) const = 0;

    /**
     * Picks element with given key.
     *
     * @param key The target key
     *
     * @return The element or null
     */
    virtual ValueTypeOrNull pick(const KeyType& key) const = 0;

    /**
     * Checks if tree contains element with given key
     *
     * @param key The target key.
     *
     * @return \c true if contained, \c false otherwise
     */
    virtual bool contains(const KeyType& key) const = 0;

    /**
     * Erase element by given key.
     *
     * @param key The key of element to erase
     */
    virtual void erase(const KeyType& key) = 0;

    /**
     * Erase min element.
     */
    virtual void eraseMin() = 0;

    /**
     * Erase max element.
     */
    virtual void eraseMax() = 0;

    /**
     * Erase all elements.
     */
    virtual void clear() = 0;

    /**
     * Checks for empty.
     *
     * @return \c true If empty, \c false otherwise
     */
    virtual bool empty() const = 0;

    /**
     * Returns the total number of elements.
     *
     * @return The number of elements
     */
    virtual std::size_t size() const = 0;

    /**
     * Returns the number of elements in the range [lo, hi].
     *
     * @param lo The left bound
     * @param hi The right bound
     *
     * @return The number of element
     */
    virtual std::size_t size(KeyType lo, KeyType hi) const = 0;

    /**
     * Returns the order number of element with given number.
     *
     * @param key The key of element
     *
     * @return The order number of element
     */
    virtual std::size_t rank(const KeyType& key) const = 0;

    /**
     * Returns the key of min element.
     *
     * @return The key of element
     */
    virtual KeyType min() const = 0;

    /**
     * Returns the key of max element.
     *
     * @return The key of element
     */
    virtual KeyType max() const = 0;

    /**
     * Returns the last not greater or equal of given key.
     *
     * @param key The target key
     *
     * @return The key value or null
     */
    virtual KeyTypeOrNull floor(const KeyType& key) const = 0;

    /**
     * Returns the firts greater than given key.
     *
     * @param key The target key.
     *
     * @return
     */
    virtual KeyTypeOrNull ceiling(const KeyType& key) const = 0;

    /**
     * Returns the list of contained keys.
     *
     * @return The list of contained keys
     */
    virtual KeysType keys() const = 0;

    /**
     * Returns the keys in the range [lo, hi].
     *
     * @param lo The left bound
     * @param hi The right bound
     *
     * @return The list of keys
     */
    virtual KeysType keys(KeyType lo, KeyType hi) const = 0;

    /**
     * Traverse through tree according to given order and call provided
     * callback with particular key and value of element.
     *
     * @param type The type of order
     * @param callback The callback to call
     */
    virtual void traverse(TraverseOrder type, Callback callback) = 0;
};

} // namespace algorithms
