/******************************************************************************
 *
 * Copyright (c) 2013-2022, Lawrence Livermore National Security, LLC
 * and other libROM project developers. See the top-level COPYRIGHT
 * file for details.
 *
 * SPDX-License-Identifier: (Apache-2.0 OR MIT)
 *
 *****************************************************************************/

// Description: Computes the AdaptiveDMD algorithm on the given snapshot matrix.
//              The AdaptiveDMD algorithm should be used if the dt changes
//              between the samples. This algorithm uniformly interpolates the samples
//              that may have been taken with variable steps, using the constant step dt
//              (a prequisite of the DMD algorithm). The smaller dt is, the finer
//              the fidelity of the interpolation.

#ifndef included_AdaptiveDMD_h
#define included_AdaptiveDMD_h

#include "DMD.h"
#include <vector>

namespace CAROM {

class Vector;

/**
 * Class AdaptiveDMD implements the AdaptiveDMD algorithm on a given snapshot matrix.
 */
class AdaptiveDMD : public DMD
{
public:

    /**
     * @brief Constructor.
     *
     * @param[in] dim            The full-order state dimension.
     * @param[in] desired_dt     The constant step size for uniform interpolation of samples.
     *                           If set equal to or below 0.0, desired_dt will be set to the median of
     *                           the different dt's between the samples.
     * @param[in] rbf            The RBF type ("G" == gaussian, "MQ" == multiquadric,
     *                           "IQ" == inverse quadratic, "IMQ" == inverse
     *                           multiquadric)
     * @param[in] interp_method  The interpolation method type ("LS" == linear solve,
     *                           "IDW" == inverse distance weighting, "LP" == lagrangian polynomials)
     * @param[in] epsilon        The RBF parameter that determines the width of influence.
     *                           If set equal to or below 0.0, epsilon will be estimated to 0.5 / desired_dt.
     */
    AdaptiveDMD(int dim, double desired_dt = -1.0, std::string rbf = "G", std::string interp_method = "LS",
                double epsilon = -1.0);

    /**
     * @brief Sample the new state, u_in.
     *
     * @pre u_in != 0
     * @pre t >= 0.0
     *
     * @param[in] u_in The new state.
     * @param[in] t    The time of the newly sampled state.
     */
    void takeSample(double* u_in, double t);

    /**
     * @param[in] energy_fraction The energy fraction to keep after doing SVD.
     */
    void train(double energy_fraction);

    /**
     * @param[in] k The number of modes (eigenvalues) to keep after doing SVD.
     */
    void train(int k);

    /**
     * @brief Get the true dt between interpolated snapshots.
     */
    double getTrueDt() const;

    /**
     * @brief Get the interpolated snapshot matrix contained within d_interp_snapshots.
     */
    const Matrix* getInterpolatedSnapshots();

private:

    /**
     * @brief Unimplemented default constructor.
     */
    AdaptiveDMD();

    /**
     * @brief Unimplemented copy constructor.
     */
    AdaptiveDMD(
        const AdaptiveDMD& other);

    /**
     * @brief Unimplemented assignment operator.
     */
    AdaptiveDMD&
    operator = (
        const AdaptiveDMD& rhs);

    /**
     * @brief The stored times of each sample.
     */
    std::vector<Vector*> d_sampled_times;

    /**
     * @brief The RBF type (gaussian, multiquadric, inverse quadratic, inverse
     *        multiquadric)
     */
    std::string d_rbf;

    /**
     * @brief The interpolation method (linear solve, inverse distance weighting,
     *        lagrangian polynomials)
     */
    std::string d_interp_method;

    /**
     * @brief std::vector holding the interpolated snapshots.
     */
    std::vector<Vector*> d_interp_snapshots;

    /**
     * @brief Internal function to obtain the interpolated snapshots.
     */
    void interpolateSnapshots();

    /**
     * @brief The RBF parameter that determines the width of influence.
     *        a small epsilon: larger influential width
     *        a large epsilon: smaller influential width
     */
    double d_epsilon;
};

}

#endif