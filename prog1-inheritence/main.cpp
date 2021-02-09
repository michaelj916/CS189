#include <iostream>

// base classes: Animal & Vehicle
class Animal
{
public:
        void Eat()
        {
                std::cout << "I am Eating . . .\n";
        }
        void Speak()
        {
                std::cout << "I am speaking . . .\n";
        }
        void Die()
        {
                std::cout << "I am dead!\n";
        }
};

class Vehicle
{
private:
        int color;
public:
        void Drive()
        {
                std::cout << "Vrooom!\n";
        }
        void Fly()
        {
                std::cout << "Flying  . . !\n";
        }
        int GetColor()
        {
                return color;
        }
};

// Animal Classes
class Dog : public Animal {};
class Duck : public Animal {};
class Cat : public Animal {};
class Horse : public Animal {};
class Pigeon : public Animal {};
class Fish : public Animal {};
class Finch : public Animal {};
class Seahorse : public Animal {};

// Vehicle Classes
class Airplane : public Vehicle {};
class Car : public Vehicle {};
class Bicycle : public Vehicle {};

int main()
{
        // testing animal class
        Dog toby;
        toby.Eat();
        toby.Speak();
        toby.Die();

        // testing vehicle class
        Car prius;
        prius.Drive();
        prius.GetColor(); // will return nothing

        return 0;
}

// vim: syntax=cpp
