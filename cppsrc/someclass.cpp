#include "someclass.h"

SomeClass::SomeClass(double value){
    this->value_ = value;
}

double SomeClass::getValue()
{
  return this->value_;
}

double SomeClass::add(double toAdd)
{
  this->value_ += toAdd;
  return this->value_;
}
