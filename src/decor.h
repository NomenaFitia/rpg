#ifndef DECOR_H
#define DECOR_H

#include "src/entity.h"

class Decor : public Entity {
private:
    char symbol;

public:
    Decor(Vector2 position, char symbol);
    virtual ~Decor() = default;

    virtual char getSymbol() const;
};

#endif
