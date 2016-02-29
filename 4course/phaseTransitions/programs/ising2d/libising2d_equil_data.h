#ifndef LIBISING2D_EQUIL_DATA
#define LIBISING2D_EQUIL_DATA

#include <cstdlib>
#include <cmath>
#include "mt64.h"

namespace libising2d {

    struct Ising2DConfiguration
    {
      size_t mc_collected_steps;
      size_t mc_excluded_steps;
      double temperature;
    };

    struct Ising2DSystem
    {
      size_t linear_size, spins_number;
      int **spin_structure;
    };

    struct Cumulant {
      long double m_cumulant, m2_cumulant, e_cumulant, e2_cumulant;
    };

    size_t get_relaxation_time(const Ising2DSystem, const double);
    void set_generator_seed(const unsigned long long);
    Cumulant run_equilibrium_research(const Ising2DConfiguration, const Ising2DSystem);
};

#endif