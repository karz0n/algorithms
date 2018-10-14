#ifndef STACK_HPP
#define STACK_HPP

namespace algorithms
{

template<typename T>
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
     * Pop item from the item.
     *
     * @return The item object.
     */
    virtual T pop() = 0;

    /**
     * Check for stack is empty.
     *
     * @return The flag which indicated that stack is empty.
     */
    virtual bool isEmpty() const = 0;
};

} // namespace algorithms

#endif // STACK_HPP
