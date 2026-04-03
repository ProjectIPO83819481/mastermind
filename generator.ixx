module; 
#include <random>
#include <exception>

export module mastermind:generator;

export class BaseGenerator {
private:
    std::random_device rd{};
    std::mt19937 gen{ rd() };
    std::uniform_real_distribution<double> urd{ 0., 1. };
public:

    double generate() { return urd(gen); }
    virtual ~BaseGenerator() {};
};
