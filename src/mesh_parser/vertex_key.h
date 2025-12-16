#ifndef VERTEX_KEY_H
#define VERTEX_KEY_H

struct VertexKey {
    unsigned short vi, ni, ti;

    bool operator==(const VertexKey& other) {
        return (
            vi == other.vi &&
            ni == other.ni &&
            ti == other.ti 
        );
    }
};

#endif