# \InfoUtilsSdkClientGo

All URIs are relative to *http://127.0.0.1:36943*

Method | HTTP request | Description
------------- | ------------- | -------------
[**GetInfo**](InfoUtilsSdkClientGo.md#GetInfo) | **Get** /info | Get detailed information about the blockchain and daemon state
[**Version**](InfoUtilsSdkClientGo.md#Version) | **Get** /info/version | Get API version



## GetInfo

> InfoModel GetInfo(ctx).Flags(flags).Execute()

Get detailed information about the blockchain and daemon state

### Example

```go
package main

import (
	"context"
	"fmt"
	"os"
	openapiclient "github.com/letheanVPN/blockchain/utils/sdk/client/go"
)

func main() {
	flags := "flags_example" // string | Possible values: net_time_delta_median, current_network_hashrate_50, current_network_hashrate_350, seconds_for_10_blocks, seconds_for_30_blocks, transactions_daily_stat, last_pos_timestamp, last_pow_timestamp, total_coins, last_block_size, tx_count_in_last_block, pos_sequence_factor, pow_sequence_factor, pos_difficulty, performance, outs_stat, expirations_median. (optional)

	configuration := openapiclient.NewConfiguration()
	apiClient := openapiclient.NewAPIClient(configuration)
	resp, r, err := apiClient.InfoUtilsSdkClientGo.GetInfo(context.Background()).Flags(flags).Execute()
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error when calling `InfoUtilsSdkClientGo.GetInfo``: %v\n", err)
		fmt.Fprintf(os.Stderr, "Full HTTP response: %v\n", r)
	}
	// response from `GetInfo`: InfoModel
	fmt.Fprintf(os.Stdout, "Response from `InfoUtilsSdkClientGo.GetInfo`: %v\n", resp)
}
```

### Path Parameters



### Other Parameters

Other parameters are passed through a pointer to a apiGetInfoRequest struct via the builder pattern


Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **flags** | **string** | Possible values: net_time_delta_median, current_network_hashrate_50, current_network_hashrate_350, seconds_for_10_blocks, seconds_for_30_blocks, transactions_daily_stat, last_pos_timestamp, last_pow_timestamp, total_coins, last_block_size, tx_count_in_last_block, pos_sequence_factor, pow_sequence_factor, pos_difficulty, performance, outs_stat, expirations_median. | 

### Return type

[**InfoModel**](InfoModel.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: Not defined
- **Accept**: application/json

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints)
[[Back to Model list]](../README.md#documentation-for-models)
[[Back to README]](../README.md)


## Version

> VersionModel Version(ctx).Execute()

Get API version



### Example

```go
package main

import (
	"context"
	"fmt"
	"os"
	openapiclient "github.com/letheanVPN/blockchain/utils/sdk/client/go"
)

func main() {

	configuration := openapiclient.NewConfiguration()
	apiClient := openapiclient.NewAPIClient(configuration)
	resp, r, err := apiClient.InfoUtilsSdkClientGo.Version(context.Background()).Execute()
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error when calling `InfoUtilsSdkClientGo.Version``: %v\n", err)
		fmt.Fprintf(os.Stderr, "Full HTTP response: %v\n", r)
	}
	// response from `Version`: VersionModel
	fmt.Fprintf(os.Stdout, "Response from `InfoUtilsSdkClientGo.Version`: %v\n", resp)
}
```

### Path Parameters

This endpoint does not need any parameter.

### Other Parameters

Other parameters are passed through a pointer to a apiVersionRequest struct via the builder pattern


### Return type

[**VersionModel**](VersionModel.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: Not defined
- **Accept**: application/json

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints)
[[Back to Model list]](../README.md#documentation-for-models)
[[Back to README]](../README.md)

