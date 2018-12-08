#ifndef QUEUE_HPP
#define QUEUE_HPP

namespace algorithms {

template<typename T>
class Queue {
public:
    virtual ~Queue() = default;

    /**
     * Enqueue item to the queue.
     *
     * @param item The reference to the item.
     */
    virtual void enqueue(const T& item) = 0;

    /**
     * Dequeue item from the queue.
     *
     * @return The item object.
     */
    virtual T dequeue() = 0;

    /**
     * Check for queue is empty.
     *
     * @return The flag which indicated that queue is empty.
     */
    virtual bool isEmpty() const = 0;
};


} // namespace algorithms

#endif // QUEUE_HPP
