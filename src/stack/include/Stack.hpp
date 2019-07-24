#ifndef STACK_HPP
#define STACK_HPP

namespace algorithms {

/**
 * Interface class for stack implementations.
 */
template <typename T>
class Stack {
public:
    virtual ~Stack() = default;

    /**
     * Push item to the stack.
     *
     * @param item The reference to the item.
     */
    virtual void push(const T& item) = 0;

    /**
     * Pop item from the stack.
     *
     * @return The item object.
     */
    virtual T pop() = 0;

    /**
     * Check for stack is empty.
     *
     * @return The flag which indicated that stack is empty.
     */
    virtual bool empty() const = 0;
};

} // namespace algorithms

#endif // STACK_HPP
