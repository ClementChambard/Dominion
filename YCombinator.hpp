#ifndef YCOMBINATOR_H_
#define YCOMBINATOR_H_

/*
 * No idea how it works, code is by Barry on stack overflow
 * https://stackoverflow.com/questions/2067988/recursive-lambda-functions-in-c11
 *
 * Used by Library to make recursive lambda function
 */

#include <functional>

template <class F>
struct y_combinator {
    F f; // the lambda will be stored here

    // a forwarding operator():
    template <class... Args>
    decltype(auto) operator()(Args&&... args) const {
        // we pass ourselves to f, then the arguments.
        return f(*this, std::forward<Args>(args)...);
    }
};

// helper function that deduces the type of the lambda:
template <class F>
y_combinator<std::decay_t<F>> make_y_combinator(F&& f) {
    return {std::forward<F>(f)};
}


#endif // YCOMBINATOR_H_
