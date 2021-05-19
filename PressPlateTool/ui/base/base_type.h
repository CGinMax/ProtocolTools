#ifndef BASE_H
#define BASE_H

#include <functional>

template <typename Signature>
using Fn = std::function<Signature>;

#endif // BASE_H
