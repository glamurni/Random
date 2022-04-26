#include <iostream>
#include <random>
#include <cstdint>
#include <chrono>
#include <thread>
#include <utility>

struct GaussGenerator
{
    GaussGenerator(double mean, double stddev, std::uint32_t seed)
        : engine_(seed), distribution_(mean, stddev) {}

    GaussGenerator(double mean, double stddev)
        : distribution_(mean, stddev)
    {
        using namespace std;
        seed_seq seeds{
            (uint64_t)chrono::high_resolution_clock::now().time_since_epoch().count(),
            (uint64_t)chrono::system_clock::now().time_since_epoch().count(),
            (uint64_t)hash<thread::id>{}(this_thread::get_id()),
        };
        engine_.seed(seeds);
    }

    double operator()() { return distribution_(engine_); }

    std::mt19937 engine_;
    std::normal_distribution<double> distribution_;
};

int main()
{
    GaussGenerator rand(0, 1);
    for (int i = 0; i != 5; ++i)
        std::cout << rand() << '\n';
}