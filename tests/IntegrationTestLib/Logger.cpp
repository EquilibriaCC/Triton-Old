/*
 * Copyright (c) 2017-2018, The Alloy Developers.
 * Portions Copyright (c) 2012-2017, The CryptoNote Developers, The Bytecoin Developers.
 *
 * This file is part of Alloy.
 *
 * This file is subject to the terms and conditions defined in the
 * file 'LICENSE', which is part of this source code package.
 */

#include "Logger.h"

#include <algorithm>
#include <boost/date_time.hpp>

CLogger& CLogger::Instance()
{
	static CLogger theSingleInstance;
	return theSingleInstance;
}
void CLogger::init(LOG_LEVEL log_lvl)
{
  level_names[TRACE]   = "[ TRACE ]";
  level_names[DEBUG]   = "[ DEBUG ]";
  level_names[_ERROR]  = "[ ERROR ]";
  level_names[WARNING] = "[WARNING]";
  level_names[VERBOSE] = "[VERBOSE]";
  log_level = log_lvl;
  indent = 0;
}
void CLogger::Log(const std::string & log_info, LOG_LEVEL log_lvl, int indent_inc)
{
	if(log_lvl>=log_level)
	{
		std::lock_guard<std::mutex> lock(mutex);
		if (indent_inc<0)indent+=indent_inc;
		std::string sindent(std::max(0,indent),' ');
		if (indent_inc>0)indent+=indent_inc;
    (log_lvl<WARNING?std::cout:std::cerr)<<boost::posix_time::to_iso_extended_string(boost::posix_time::second_clock::local_time())<<level_names[log_lvl].c_str()<<sindent<<log_info.c_str()<<std::endl;
	}
}
