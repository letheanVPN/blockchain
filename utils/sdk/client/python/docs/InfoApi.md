# lthn.InfoApi

All URIs are relative to *http://127.0.0.1:36943*

Method | HTTP request | Description
------------- | ------------- | -------------
[**get_info**](InfoApi.md#get_info) | **GET** /info | Get detailed information about the blockchain and daemon state
[**version**](InfoApi.md#version) | **GET** /info/version | Get API version


# **get_info**
> InfoModel get_info(flags=flags)

Get detailed information about the blockchain and daemon state

### Example


```python
import lthn
from lthn.models.info_model import InfoModel
from lthn.rest import ApiException
from pprint import pprint

# Defining the host is optional and defaults to http://127.0.0.1:36943
# See configuration.py for a list of all supported configuration parameters.
configuration = lthn.Configuration(
    host = "http://127.0.0.1:36943"
)


# Enter a context with an instance of the API client
with lthn.ApiClient(configuration) as api_client:
    # Create an instance of the API class
    api_instance = lthn.InfoApi(api_client)
    flags = 'flags_example' # str | Possible values: net_time_delta_median, current_network_hashrate_50, current_network_hashrate_350, seconds_for_10_blocks, seconds_for_30_blocks, transactions_daily_stat, last_pos_timestamp, last_pow_timestamp, total_coins, last_block_size, tx_count_in_last_block, pos_sequence_factor, pow_sequence_factor, pos_difficulty, performance, outs_stat, expirations_median. (optional)

    try:
        # Get detailed information about the blockchain and daemon state
        api_response = api_instance.get_info(flags=flags)
        print("The response of InfoApi->get_info:\n")
        pprint(api_response)
    except Exception as e:
        print("Exception when calling InfoApi->get_info: %s\n" % e)
```



### Parameters


Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **flags** | **str**| Possible values: net_time_delta_median, current_network_hashrate_50, current_network_hashrate_350, seconds_for_10_blocks, seconds_for_30_blocks, transactions_daily_stat, last_pos_timestamp, last_pow_timestamp, total_coins, last_block_size, tx_count_in_last_block, pos_sequence_factor, pow_sequence_factor, pos_difficulty, performance, outs_stat, expirations_median. | [optional] 

### Return type

[**InfoModel**](InfoModel.md)

### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: Not defined
 - **Accept**: application/json

### HTTP response details

| Status code | Description | Response headers |
|-------------|-------------|------------------|
**200** | OK |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **version**
> VersionModel version()

Get API version

Returns the current version of the API.

### Example


```python
import lthn
from lthn.models.version_model import VersionModel
from lthn.rest import ApiException
from pprint import pprint

# Defining the host is optional and defaults to http://127.0.0.1:36943
# See configuration.py for a list of all supported configuration parameters.
configuration = lthn.Configuration(
    host = "http://127.0.0.1:36943"
)


# Enter a context with an instance of the API client
with lthn.ApiClient(configuration) as api_client:
    # Create an instance of the API class
    api_instance = lthn.InfoApi(api_client)

    try:
        # Get API version
        api_response = api_instance.version()
        print("The response of InfoApi->version:\n")
        pprint(api_response)
    except Exception as e:
        print("Exception when calling InfoApi->version: %s\n" % e)
```



### Parameters

This endpoint does not need any parameter.

### Return type

[**VersionModel**](VersionModel.md)

### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: Not defined
 - **Accept**: application/json

### HTTP response details

| Status code | Description | Response headers |
|-------------|-------------|------------------|
**200** | OK |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

