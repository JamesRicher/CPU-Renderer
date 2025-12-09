#ifndef VECTOR3_H
#define VECTOR3_H

struct Vector3 {
    float x,y,z;
    
    Vector3(float x, float y, float z);
    float magnitude() const;
    void normalise();

    friend Vector3 operator+ (const Vector3& a, const Vector3& b);
    friend Vector3 operator+ (const Vectro3& a, const float& b);
    friend Vector3 operator- (const Vector3& a, const Vector3& b);
    friend Vector3 operator/ (const Vector3& a, const float& b);
};

#endif
