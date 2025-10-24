#include "decor.h"

Decor::Decor(Vector2 position, char symbol) : Entity(position), symbol(symbol) {}

char Decor::getSymbol() const {
    return symbol;
}
