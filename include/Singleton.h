#pragma once
template<typename T>
struct Singleton
{
public:
    static T& Instance()
    {
        static T instance;
        return instance;
    }

private:
    Singleton() {}
};