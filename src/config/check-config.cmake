
macro(check_defined_vars)
	foreach(var ${ARGN})
		if(NOT DEFINED ${var})
			message(FATAL_ERROR "${var} not set")
		endif()
	endforeach()
endmacro()

check_defined_vars(
		currency_display_decimal_point
		coin
		base_reward_dust_threshold
		default_dust_threshold
		tx_default_fee
		tx_minimum_fee
		difficulty_pow_starter
		difficulty_pos_target
		difficulty_pow_target
		difficulty_window
		difficulty_lag
		difficulty_cut
		p2p_default_port
		rpc_default_port
		stratum_default_port
		p2p_maintainers_pub_key
		currency_name_abr
		currency_name_base
		currency_name_short_base
		address_prefix_integrated
		address_prefix_auditable
		address_prefix_auditable_integrated
)
