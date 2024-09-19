// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef WRAPPER_HELPERS_H
#define WRAPPER_HELPERS_H

#include <iostream>
#include <memory>

template<typename Result, typename Creator, typename... Arguments>
auto make_resource(Creator c, Arguments&&... args) {
    auto r = c(std::forward<Arguments>(args)...);
    if (!r) { throw std::system_error(errno, std::generic_category()); }
    return Result(r);
}

template <typename T, std::decay_t<T> t>
using constant_t = std::integral_constant<T, t>;

#endif //WRAPPER_HELPERS_H