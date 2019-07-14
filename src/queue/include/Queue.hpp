#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <cstddef>

namespace algorithms {

template <typename T>
class Queue {
public:
    virtual ~Queue() = default;

    /**
     * Enqueue item to the queue.
     *
     * @param item The reference to the item.
     */
    virtual void push(const T& item) = 0;

    /**
     * Dequeue item from the queue.
     *
     * @return The item object.
     */
    virtual T pop() = 0;

    /**
     * Returns reference to the first element in the queue.
     *
     * @return Reference to the first element.
     */
    virtual T& front() = 0;

    /**
     * Returns constant reference to the first element in the queue.
     *
     * @return Constant reference to the first element.
     */
    virtual const T& front() const = 0;

    /**
     * Returns reference to the last element in the queue.
     *
     * @return Reference to the last element.
     */
    virtual T& back() = 0;

    /**
     * Returns constant reference to the last element in the queue.
     *
     * @return Constant reference to the last element.
     */
    virtual const T& back() const = 0;

    /**
     * Check for queue is empty.
     *
     * @return The flag which indicated that queue is empty.
     */
    virtual bool empty() const = 0;

    /**
     * Return the number of elements.
     *
     * @return The number of elements.
     */
    virtual std::size_t size() const = 0;
};

} // namespace algorithms

#endif // QUEUE_HPP
