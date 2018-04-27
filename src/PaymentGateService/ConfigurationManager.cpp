/*
 * Copyright (c) 2017-2018, The Triton Developers.
 * Portions Copyright (c) 2012-2017, The CryptoNote Developers, The Bytecoin Developers.
 *
 * This file is part of Triton.
 *
 * This file is subject to the terms and conditions defined in the
 * file 'LICENSE', which is part of this source code package.
 */

#include "ConfigurationManager.h"

#include <fstream>
#include <boost/program_options.hpp>

#include "Common/CommandLine.h"
#include "Common/Util.h"
#include "version.h"

namespace PaymentService {

namespace po = boost::program_options;

ConfigurationManager::ConfigurationManager() {
  startInprocess = false;
}

bool ConfigurationManager::init(int argc, char** argv) {
  po::options_description cmdGeneralOptions("Common Options");

  cmdGeneralOptions.add_options()
      ("config,c", po::value<std::string>(), "configuration file");

  po::options_description confGeneralOptions;
  confGeneralOptions.add(cmdGeneralOptions).add_options()
      ("testnet", po::bool_switch(), "")
      ("local", po::bool_switch(), "");

  cmdGeneralOptions.add_options()
      ("help,h", "produce this help message and exit")
      ("local", po::bool_switch(), "start with local node (remote is default)")
      ("testnet", po::bool_switch(), "testnet mode")
      ("version", "Output version information");

  command_line::add_arg(cmdGeneralOptions, command_line::arg_data_dir, Tools::getDefaultDataDirectory());
  command_line::add_arg(confGeneralOptions, command_line::arg_data_dir, Tools::getDefaultDataDirectory());

  Configuration::initOptions(cmdGeneralOptions);
  Configuration::initOptions(confGeneralOptions);

  po::options_description netNodeOptions("Local Node Options");
  CryptoNote::NetNodeConfig::initOptions(netNodeOptions);
  
  po::options_description remoteNodeOptions("Remote Node Options");
  RpcNodeConfiguration::initOptions(remoteNodeOptions);

  po::options_description cmdOptionsDesc;
  cmdOptionsDesc.add(cmdGeneralOptions).add(remoteNodeOptions).add(netNodeOptions);

  po::options_description confOptionsDesc;
  confOptionsDesc.add(confGeneralOptions).add(remoteNodeOptions).add(netNodeOptions);

  po::variables_map cmdOptions;
  po::store(po::parse_command_line(argc, argv, cmdOptionsDesc), cmdOptions);
  po::notify(cmdOptions);

  if (cmdOptions.count("help")) {
    std::cout << cmdOptionsDesc << std::endl;
    return false;
  }

  if (cmdOptions.count("version") > 0) {
    std::cout << "walletd v" << PROJECT_VERSION_LONG;
    return false;
  }

  if (cmdOptions.count("config")) {
    std::ifstream confStream(cmdOptions["config"].as<std::string>(), std::ifstream::in);
    if (!confStream.good()) {
      throw ConfigurationError("Cannot open configuration file");
    }

    po::variables_map confOptions;
    po::store(po::parse_config_file(confStream, confOptionsDesc), confOptions);
    po::notify(confOptions);

    gateConfiguration.init(confOptions);
    netNodeConfig.init(confOptions);
    remoteNodeConfig.init(confOptions);

    netNodeConfig.setTestnet(confOptions["testnet"].as<bool>());
    startInprocess = confOptions["local"].as<bool>();
  }

  //command line options should override options from config file
  gateConfiguration.init(cmdOptions);
  netNodeConfig.init(cmdOptions);
  remoteNodeConfig.init(cmdOptions);
  dataDir = command_line::get_arg(cmdOptions, command_line::arg_data_dir);

  if (cmdOptions["testnet"].as<bool>()) {
    netNodeConfig.setTestnet(true);
  }

  if (cmdOptions["local"].as<bool>()) {
    startInprocess = true;
  }

  return true;
}

} //namespace PaymentService
