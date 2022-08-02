/**
 * @file core/util/log.hpp
 * @author Matthew Amidon
 *
 * Definition of the Log class.
 *
 * mlpack is free software; you may redistribute it and/or modify it under the
 * terms of the 3-clause BSD license.  You should have received a copy of the
 * 3-clause BSD license along with mlpack.  If not, see
 * http://www.opensource.org/licenses/BSD-3-Clause for more information.
 */
#ifndef MLPACK_CORE_UTIL_LOG_HPP
#define MLPACK_CORE_UTIL_LOG_HPP

#include <string>
#include <mlpack/mlpack_export.hpp>

#include "prefixedoutstream.hpp"
#include "nulloutstream.hpp"

namespace mlpack {

/**
 * Provides a convenient way to give formatted output.
 *
 * The Log class has four members which can be used in the same way ostreams can
 * be used:
 *
 *  - Log::Debug
 *  - Log::Info
 *  - Log::Warn
 *  - Log::Fatal
 *
 * Each of these will prefix a tag to the output (for easy filtering), and the
 * fatal output will terminate the program when a newline is encountered.  An
 * example is given below.
 *
 * @code
 * Log::Info << "Checking a condition." << std::endl;
 * if (!someCondition())
 *   Log::Warn << "someCondition() is not satisfied!" << std::endl;
 * Log::Info << "Checking an important condition." << std::endl;
 * if (!someImportantCondition())
 * {
 *   Log::Fatal << "someImportantCondition() is not satisfied! Terminating.";
 *   Log::Fatal << std::endl;
 * }
 * @endcode
 *
 * Any messages sent to Log::Debug will not be shown when compiling in non-debug
 * mode.  Messages to Log::Info will only be shown when the --verbose flag is
 * given to the program (or rather, the IO class).
 *
 * @see PrefixedOutStream, NullOutStream, IO
 */
namespace Log {

/**
 * Checks if the specified condition is true.
 * If not, halts program execution and prints a custom error message.
 * Does nothing in non-debug mode.
 */
void Assert(bool condition,
            const std::string& message = "Assert Failed.");

/**
 * MLPACK_EXPORT is required for global variables, so that they are properly
 * exported by the Windows compiler.
 */

// Color code escape sequences -- but not on Windows.
#ifndef _WIN32
  #define BASH_RED "\033[0;31m"
  #define BASH_GREEN "\033[0;32m"
  #define BASH_YELLOW "\033[0;33m"
  #define BASH_CYAN "\033[0;36m"
  #define BASH_CLEAR "\033[0m"
#else
  #define BASH_RED ""
  #define BASH_GREEN ""
  #define BASH_YELLOW ""
  #define BASH_CYAN ""
  #define BASH_CLEAR ""
#endif

#ifdef DEBUG
static util::PrefixedOutStream Debug =
    util::PrefixedOutStream(MLPACK_COUT_STREAM,
                            BASH_CYAN "[DEBUG] " BASH_CLEAR);
#else
static util::NullOutStream Debug = util::NullOutStream();
#endif

static util::PrefixedOutStream Info =
    util::PrefixedOutStream(MLPACK_COUT_STREAM,
                            BASH_GREEN "[INFO ] " BASH_CLEAR,
                            true /* unless --verbose */,
                            false);

static util::PrefixedOutStream Warn =
    util::PrefixedOutStream(MLPACK_COUT_STREAM,
                            BASH_YELLOW "[WARN ] " BASH_CLEAR,
                            false,
                            false);

static util::PrefixedOutStream Fatal =
    util::PrefixedOutStream(MLPACK_CERR_STREAM,
                            BASH_RED "[FATAL] " BASH_CLEAR,
                            false,
                            true /* fatal */);

} // namespace Log
} // namespace mlpack

// Include implementation.
#include "log_impl.hpp"

#endif
