/*
 * Copyright (c) 2017-2018, The Triton Developers.
 * Portions Copyright (c) 2012-2017, The CryptoNote Developers, The Bytecoin Developers.
 *
 * This file is part of Triton.
 *
 * This file is subject to the terms and conditions defined in the
 * file 'LICENSE', which is part of this source code package.
 */

#include "FileLogger.h"

namespace Logging {

FileLogger::FileLogger(Level level) : StreamLogger(level) {
}

void FileLogger::init(const std::string& fileName) {
  fileStream.open(fileName, std::ios::app);
  StreamLogger::attachToStream(fileStream);
}

}
