/*
 * etl_profile.h
 *
 *  Created on: Oct 14, 2018
 *      Author: tamas
 */
#ifndef INC_ETL_PROFILE_H_
#define INC_ETL_PROFILE_H_
/**
 * @brief A necessary configuring header for the ETL library
 */
#define ETL_VERBOSE_ERRORS

#ifdef _MSC_VER
#include "etl/include/etl/profiles/msvc.h"
#else
#include "etl/include/etl/profiles/gcc_generic.h"
#endif
#endif
