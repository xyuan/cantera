/*
 * Copyright 2004 Sandia Corporation. Under the terms of Contract
 * DE-AC04-94AL85000, there is a non-exclusive license for use of this
 * work by or on behalf of the U.S. Government.
 */

#ifndef TEMPERATURE_TABLE_H
#define  TEMPERATURE_TABLE_H

#include <vector>
#include <algorithm>

using std::vector;

/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/**
 *   This Class constructs a vector of temperature from which to make
 *   a table.
 */
class TemperatureTable
{

public:
    int    NPoints;
    bool   Include298;
    double Tlow;                 //!<   Min temperature for thermo data fit
    double Thigh;                //!<   Max temperature for thermo table
    double DeltaT;
    vector<double> T;
    int numAddedTs;
    vector<double> AddedTempVector;
public:
    /*
     * Default constructor for TemperatureTable()
     */
    TemperatureTable(const int nPts = 14,
                     const bool inc298 = true,
                     const double tlow = 300.,
                     const double deltaT = 100.,
                     const int numAdded = 0,
                     const double* addedTempVector = 0) :
        NPoints(nPts),
        Include298(inc298),
        Tlow(tlow),
        DeltaT(deltaT),
        T(0),
        numAddedTs(numAdded) {
        /****************************/
        int i;
        AddedTempVector.resize(numAdded, 0.0);
        for (int i = 0; i < numAdded; i++) {
            AddedTempVector[i] = addedTempVector[i];
        }
        T.resize(NPoints, 0.0);
        double TCurrent = Tlow;
        for (i = 0; i < NPoints; i++) {
            T[i] = TCurrent;
            TCurrent += DeltaT;
        }
        if (Include298) {
            T.push_back(298.15);
            NPoints++;
        }
        if (numAdded > 0) {
            T.resize(NPoints+numAdded, 0.0);
            for (i = 0; i < numAdded; i++) {
                T[i+NPoints] = addedTempVector[i];
            }
            NPoints += numAdded;
        }
        std::sort(T.begin(), T.end());
    }
    /***********************************************************************/
    /***********************************************************************/
    /***********************************************************************/
    /*
     * Destructor
     */
    ~TemperatureTable() {}

    /***********************************************************************/
    /***********************************************************************/
    /***********************************************************************/
    /*
     *  Overloaded operator[]
     *
     *       return the array value in the vector
     */
    double operator[](const int i)  {
        return T[i];
    }
    /***********************************************************************/
    /***********************************************************************/
    /***********************************************************************/
    /*
     *  size()
     */
    int size() {
        return NPoints;
    }
    /***********************************************************************/
    /***********************************************************************/
    /***********************************************************************/
    /*
     * Block assignment and copy constructors: not needed.
     */
private:
    TemperatureTable(const TemperatureTable&);
    TemperatureTable& operator=(const TemperatureTable&);
};
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
#endif