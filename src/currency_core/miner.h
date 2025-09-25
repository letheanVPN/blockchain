// Copyright (c) 2014-2018 Zano Project
// Copyright (c) 2014-2018 The Louisdor Project
// Copyright (c) 2012-2013 The Boolberry developers
// Copyright (c) 2017-2025 Lethean (https://lt.hn)
//
// Licensed under the European Union Public Licence (EUPL) version 1.2.
// You may obtain a copy of the licence at:
//
//     https://joinup.ec.europa.eu/software/page/eupl/licence-eupl
//
// The EUPL is a copyleft licence that is compatible with the MIT/X11
// licence used by the original projects; the MIT terms are therefore
// considered “grandfathered” under the EUPL for this code.
//
// SPDX‑License‑Identifier: EUPL-1.2
//

#pragma once 

#ifdef TESTNET
#define CPU_MINING_ENABLED // disable CPU mining capabilities in mainnet
#endif // #ifndef TESTNET

#include <boost/atomic.hpp>
#include <boost/program_options.hpp>
#include <atomic>
#include "currency_basic.h"
#include "difficulty.h"
#include "math_helper.h"
#include "blockchain_storage.h"
#include "basic_pow_helpers.h"



namespace currency
{

  struct i_miner_handler
  {
    virtual bool handle_block_found(const block& b, block_verification_context* p_verification_result = nullptr) = 0;
    virtual bool get_block_template(const create_block_template_params& params, create_block_template_response& resp) = 0;
    virtual bool get_block_template(block& b, const account_public_address& adr, const account_public_address& stakeholder_address, wide_difficulty_type& diffic, uint64_t& height, const blobdata& ex_nonce, bool pos = false, const pos_entry& pe = pos_entry()) = 0;
  protected:
    ~i_miner_handler(){};
  };

  inline
  static bool find_nonce_for_given_block(block& bl, const wide_difficulty_type& diffic, uint64_t height)
  {      
    bl.nonce = 0;
    blobdata bd = get_block_hashing_blob(bl);
    crypto::hash bd_hash = crypto::cn_fast_hash(bd.data(), bd.size());
    //uint64_t& nonce_ref = access_nonce_in_block_blob(bd);
    //nonce_ref = 0;

    for(; bl.nonce != std::numeric_limits<uint64_t>::max(); bl.nonce++)
    {
      crypto::hash h = get_block_longhash(height, bd_hash, bl.nonce);
      if(check_hash(h, diffic))
      {
        LOG_PRINT_L1("Found nonce for block: " << get_block_hash(bl) << "[" << height << "]: PoW:" << h << " (diff:" << diffic << "), ts: " << bl.timestamp);
        return true;
      }
    }
    return false;
  }

#ifdef CPU_MINING_ENABLED

  /************************************************************************/
  /*                                                                      */
  /************************************************************************/
  class miner
  {
  public: 
    miner(i_miner_handler* phandler, blockchain_storage& bc);
    ~miner();
    bool init(const boost::program_options::variables_map& vm);
    bool deinit();
    static void init_options(boost::program_options::options_description& desc);
    bool on_block_chain_update();
    bool start(const account_public_address& adr, size_t threads_count);
    uint64_t get_speed();
    void send_stop_signal();
    bool stop();
    bool is_mining();
    bool on_idle();
    void on_synchronized();
    //synchronous analog (for fast calls)
    void pause();
    void resume();
    void do_print_hashrate(bool do_hr);

  private:
    bool set_block_template(const block& bl, const wide_difficulty_type& diffic, uint64_t height);
    bool worker_thread();
    bool request_block_template();
    void  merge_hr();
    
    struct miner_config
    {
      uint64_t current_extra_message_index;

      BEGIN_KV_SERIALIZE_MAP()
        KV_SERIALIZE(current_extra_message_index)
      END_KV_SERIALIZE_MAP()
    };


    volatile uint32_t m_stop;
    epee::critical_section m_template_lock;
    block m_template;
    std::atomic<uint32_t> m_template_no;
    std::atomic<uint32_t> m_starter_nonce;
    wide_difficulty_type m_diffic;
    std::atomic<uint64_t> m_height;
    volatile uint32_t m_thread_index; 
    volatile uint32_t m_threads_total;
    std::atomic<int32_t> m_pausers_count;
    std::atomic<bool> m_block_template_ready;
    epee::critical_section m_miners_count_lock;    

    std::list<boost::thread> m_threads;
    epee::critical_section m_threads_lock;
    i_miner_handler* m_phandler;
    //blockchain_storage& m_bc;
    account_public_address m_mine_address;
    epee::math_helper::once_a_time_seconds<5> m_update_block_template_interval;
    epee::math_helper::once_a_time_seconds<2> m_update_merge_hr_interval;
    std::vector<blobdata> m_extra_messages;
    miner_config m_config;
    std::string m_config_folder;  
    std::string m_template_extra_text;
    std::atomic<uint64_t> m_current_hash_rate;
    std::atomic<uint64_t> m_last_hr_merge_time;
    std::atomic<uint64_t> m_hashes;
    bool m_do_print_hashrate;
    bool m_do_mining;
    
  };

#endif // #ifdef CPU_MINING_ENABLED

} // namespace currency
