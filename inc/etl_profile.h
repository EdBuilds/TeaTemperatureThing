/*
 * etl_profile.h
 *
 *  Created on: Oct 14, 2018
 *      Author: tamas
 */
#ifndef __ETL_PROFILE_H__
#define __ETL_PROFILE_H__

#define ETL_VERBOSE_ERRORS

#ifdef _MSC_VER
#include "etl/include/etl/profiles/msvc.h"
#else
#include "etl/include/etl/profiles/gcc_generic.h"
#endif
#endif
