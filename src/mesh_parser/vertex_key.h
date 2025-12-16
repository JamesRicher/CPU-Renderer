#ifndef VERTEX_KEY_H
#define VERTEX_KEY_H

struct VertexKey {
    unsigned short pos_i, norm_i, tex_i;

    bool operator==(const VertexKey& other) const {
        return (
            pos_i == other.pos_i &&
            norm_i == other.norm_i &&
            tex_i == other.tex_i 
        );
    }
};

#endif