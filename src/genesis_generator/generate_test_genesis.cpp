// Copyright (c) 2014-2018 Zano Project
// Copyright (c) 2014-2018 The Louisdor Project
// Copyright (c) 2012-2013 The Boolberry developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "misc_log_ex.h"
#include "currency_core/currency_format_utils.h"
#include "common/command_line.h"
#include <boost/multiprecision/integer.hpp>

namespace po = boost::program_options;

bool generate_test_genesis(std::string address, std::string proof, std::string out_dir)
{
  using namespace std;
  currency::block bl = boost::value_initialized<currency::block>();

#ifndef TESTNET
  constexpr auto posfix = "";
#else
  constexpr auto posfix = "_tn";
#endif

  vector<currency::tx_destination_entry> destinations;
  currency::tx_destination_entry de = AUTO_VAL_INIT(de);
  de.addr.resize(1);

  bool r = get_account_address_from_str(de.addr.back(), address);
  CHECK_AND_ASSERT_MES(r, false, "wrong address string: " << address);
  
  de.amount = PREMINE_AMOUNT;
  destinations.push_back(de);

  //make sure it initialized with zeros 
  uint64_t summary_premine_coins = de.amount;

  const currency::account_public_address dummy_address = AUTO_VAL_INIT(dummy_address);
  uint64_t block_reward_without_fee = 0;
  uint64_t block_reward = 0;
  construct_miner_tx(0, 0, 0, 0, 0,
        	  dummy_address, dummy_address, bl.miner_tx, block_reward_without_fee, block_reward,
        	  TRANSACTION_VERSION_PRE_HF4, 0, proof, CURRENCY_MINER_TX_MAX_OUTS, false, currency::pos_entry(),
        	  nullptr, nullptr, destinations);

  currency::blobdata txb = tx_to_blob(bl.miner_tx);

  //self validate block
  if (currency::get_outs_money_amount(bl.miner_tx) !=  summary_premine_coins )
  {
    LOG_ERROR("Internal error: total_this = " << summary_premine_coins << " didn't match with miner_tx total = " << currency::get_outs_money_amount(bl.miner_tx));
  }

  string hex_tx_represent = epee::string_tools::buff_to_hex_nodelimer(txb);

  auto ret = epee::file_io_utils::save_string_to_file(out_dir + ".genesis.txt", hex_tx_represent);
  CHECK_AND_ASSERT_MES_NO_RET(ret, "failed to create " << out_dir << ".genesis.txt");

  uint64_t* parray = (uint64_t*)txb.data();
  size_t count = txb.size() / sizeof(uint64_t);
  size_t rest_bytes = txb.size() - count * sizeof(uint64_t);

  basic_stringstream<char> genesis_h_stream;
  basic_stringstream<char> genesis_cpp_stream;
  genesis_h_stream << "struct genesis_tx_raw_data" << ENDL
    << "{" << ENDL
    << "  uint64_t const v[" << count << "];" << ENDL
    << "  uint8_t const r[" << rest_bytes << "];" << ENDL
    << "};" << ENDL;

  genesis_cpp_stream << "const genesis_tx_raw_data ggenesis_tx_raw = {{" << ENDL;

  for (size_t i = 0; i != count; i++)
  {
    genesis_cpp_stream << (i == 0 ? "0x":",0x")<< hex << setw(16) << setfill('0') << parray[i];
  }
  genesis_cpp_stream << "}," << ENDL << "{";
  uint8_t* ptail_array = (uint8_t*)&parray[count];
  for (size_t i = 0; i != rest_bytes; i++)
  {
    genesis_cpp_stream << (i == 0 ? "0x":",0x") << hex << setw(2) << setfill('0') << +ptail_array[i];
  }
  genesis_cpp_stream << "}};" << ENDL;

  // Generate _genesis.cpp.gen
  // Generate _genesis.h.gen
  ret = epee::file_io_utils::save_string_to_file(out_dir + "_genesis" + posfix + ".h.gen", genesis_h_stream.str());
  CHECK_AND_ASSERT_MES_NO_RET(ret, "failed to create " << out_dir << "_genesis.h.gen");

  ret = epee::file_io_utils::save_string_to_file(out_dir + "_genesis" + posfix + ".cpp.gen", genesis_cpp_stream.str());
  CHECK_AND_ASSERT_MES_NO_RET(ret, "failed to create " << out_dir << "_genesis.cpp.gen");

  // Single address for now
  uint64_t key = currency::get_string_uint64_hash(address);
  
  // Generate _genesis_acc.cpp.gen
  basic_stringstream<char> genesis_acc_stream;
  genesis_acc_stream << "const std::string ggenesis_tx_pub_key_str = \"" <<
    epee::string_tools::pod_to_hex(get_tx_pub_key_from_extra(bl.miner_tx)) << "\";" << ENDL;
  genesis_acc_stream << "const crypto::public_key ggenesis_tx_pub_key = epee::string_tools::parse_tpod_from_hex_string<crypto::public_key>(ggenesis_tx_pub_key_str);" << ENDL
    << "extern const genesis_tx_dictionary_entry ggenesis_dict[" << 1 <<  "];" << ENDL
    << "const genesis_tx_dictionary_entry ggenesis_dict[" << 1 << "] = {";
  genesis_acc_stream << "" << ENDL << "{" << key << "ULL," << 0 << "}";
  genesis_acc_stream << ENDL << "};" << ENDL;

  ret = epee::file_io_utils::save_string_to_file(out_dir + "_genesis_acc" + posfix + ".cpp.gen", genesis_acc_stream.str());
  CHECK_AND_ASSERT_MES_NO_RET(ret, "failed to create " << out_dir << ".genesis.dictionary.txt");
  return ret;
}


const command_line::arg_descriptor<std::string> arg_target_address("address", "Premine wallet address");
const command_line::arg_descriptor<std::string> arg_proof("proof", "Genesis proof string");
const command_line::arg_descriptor<std::string> arg_dir("output", "Direcory output for generated files");
po::options_description desc_cmd("Command line options");

int main(int argc, char** argv) {
	command_line::add_arg(desc_cmd, arg_target_address);
	command_line::add_arg(desc_cmd, arg_proof);
	command_line::add_arg(desc_cmd, arg_dir);

	epee::log_space::log_singletone::add_logger(LOGGER_CONSOLE, NULL, NULL);
	po::variables_map vm;
	bool r = command_line::handle_error_helper(desc_cmd, [&]()
	{
		po::store(po::parse_command_line(argc, argv, desc_cmd), vm);
		po::notify(vm);
		return true;
	});
	if (!r) {
		LOG_ERROR("Param parsing failed!");
		return 1;
	}

	std::string premine_address = command_line::get_arg(vm, arg_target_address);
	std::string proof = command_line::get_arg(vm, arg_proof);
	std::string dir = command_line::get_arg(vm, arg_dir);

	LOG_PRINT_L0("addr:" << premine_address << " proof:" << proof << " amount:" << PREMINE_AMOUNT);
	generate_test_genesis(premine_address, proof, dir);
	return 0;
}
