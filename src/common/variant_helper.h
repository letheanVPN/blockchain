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

#define VARIANT_SWITCH_BEGIN(v_type_obj) {auto & local_reference_eokcmeokmeokcm ATTRIBUTE_UNUSED = v_type_obj; if(false) {;
#define VARIANT_CASE_CONST(v_type, typed_name) } else if(local_reference_eokcmeokmeokcm.type() == typeid(v_type)) {  const v_type& typed_name ATTRIBUTE_UNUSED = boost::get<v_type>(local_reference_eokcmeokmeokcm);
#define VARIANT_CASE(v_type, typed_name) } else if(local_reference_eokcmeokmeokcm.type() == typeid(v_type)) {  v_type& typed_name ATTRIBUTE_UNUSED = boost::get<v_type>(local_reference_eokcmeokmeokcm);
#define VARIANT_CASE_TV(v_type) VARIANT_CASE(v_type, tv) 
#define VARIANT_CASE_OTHER() } else { 
#define VARIANT_CASE_THROW_ON_OTHER() } else { ASSERT_MES_AND_THROW("Unknown type in switch statement: " << local_reference_eokcmeokmeokcm.type().name());
#define VARIANT_CASE_THROW_ON_OTHER_MSG(err_msg) } else { ASSERT_MES_AND_THROW(err_msg << local_reference_eokcmeokmeokcm.type().name());

#define VARIANT_SWITCH_END() } }

#define VARIANT_OBJ_TYPENAME local_reference_eokcmeokmeokcm.type().name()

/*

usage: 


      VARIANT_SWITCH_BEGIN(o);
      VARIANT_CASE(tx_out_bare, o);
        
      VARIANT_CASE_TV(tx_out_zarcanum);
        //@#@      
      VARIANT_SWITCH_END();

      VARIANT_SWITCH_BEGIN(o);
      VARIANT_CASE_CONST(txout_to_key, o);
      VARIANT_CASE_CONST(txout_multisig, ms);
      VARIANT_CASE_CONST(txout_htlc, htlc);
      VARIANT_CASE_THROW_ON_OTHER();
      VARIANT_SWITCH_END();

 

      VARIANT_SWITCH_BEGIN(s);
      VARIANT_CASE(void_sig, v);
      VARIANT_CASE(NLSAG_sig, signatures);
      VARIANT_CASE(zarcanum_sig, s);
      //@#@
      VARIANT_CASE_THROW_ON_OTHER();
      VARIANT_SWITCH_END();


      VARIANT_SWITCH_BEGIN(o);
      VARIANT_CASE(tx_out_bare, o)
        
      VARIANT_CASE_TV(tx_out_zarcanum)
        //@#@
      VARIANT_CASE_THROW_ON_OTHER();        
      VARIANT_SWITCH_END();


*/

