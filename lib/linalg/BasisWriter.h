/******************************************************************************
 *
 * Copyright (c) 2013-2021, Lawrence Livermore National Security, LLC
 * and other libROM project developers. See the top-level COPYRIGHT
 * file for details.
 *
 * SPDX-License-Identifier: (Apache-2.0 OR MIT)
 *
 *****************************************************************************/

// Description: A class that writes basis vectors to a file.

#ifndef included_BasisWriter_h
#define included_BasisWriter_h

#include "utils/Database.h"
#include <string>

namespace CAROM {

class BasisGenerator;

/**
 * Class BasisWriter writes the basis vectors created by an BasisGenerator.
 */
class BasisWriter {
public:
    /**
     * @brief Constructor.
     *
     * @pre basis_generator != 0
     * @pre !base_file_name.empty()
     *
     * @param[in] basis_generator The generator of the basis vectors to be
     *                            written.
     * @param[in] base_file_name The base part of the name of the files
     *                           holding the basis vectors.
     * @param[in] db_format Format of the file to read.
     *                      One of the implemented file formats defined in
     *                      Database.
     */
    BasisWriter(
        BasisGenerator* basis_generator,
        const std::string& base_file_name,
        Database::formats db_format = Database::HDF5);

    /**
     * @brief Destructor.
     */
    ~BasisWriter();

    /**
     * @brief Write basis or state vectors generated by d_basis_generator.
     */
    void
    writeBasis(const std::string& kind = "basis");

private:
    /**
     * @brief Unimplemented default constructor.
     */
    BasisWriter();

    /**
     * @brief Unimplemented copy constructor.
     */
    BasisWriter(
        const BasisWriter& other);

    /**
     * @brief Unimplemented assignment operator.
     */
    BasisWriter&
    operator = (
        const BasisWriter& rhs);

    /**
     * @brief Basis generator whose basis vectors are being written.
     */
    BasisGenerator* d_basis_generator;

    /**
     * @brief Database to which basis vectors are being written.
     */
    Database* d_database;

    /**
     * @brief Database with which the state is written.
     */
    Database* d_snap_database;

    /**
     * @brief Database format, as specified by user or default value.
     */
    Database::formats db_format_;

    /**
     * @brief Names with which to create new files.
     */
    std::string full_file_name;
    std::string snap_file_name;

    /**
     * @brief Number of time intervals for which basis vectors have been
     * written.
     */
    int d_num_intervals_written;
};

}

#endif