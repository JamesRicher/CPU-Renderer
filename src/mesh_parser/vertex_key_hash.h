#ifndef VERTEX_KEY_HASH_H
#define VERTEX_KEY_HASH_H

#include <cstddef>
#include <functional>
#include "vertex_key.h"

struct VertexKeyHash {
    std::size_t operator()(const VertexKey& vk) const {
        std::hash<int> hash_fn = std::hash<int>();
        std::size_t h = hash_fn(vk.ni);
        h = h*31 + hash_fn(vk.vi);
        h = h*31 + hash_fn(vk.ti);
        return h;
    }
};

#endif