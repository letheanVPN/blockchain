# lthn\InfoApi

All URIs are relative to http://127.0.0.1:36943, except if the operation defines another base path.

| Method | HTTP request | Description |
| ------------- | ------------- | ------------- |
| [**getInfo()**](InfoApi.md#getInfo) | **GET** /info | Get detailed information about the blockchain and daemon state |
| [**version()**](InfoApi.md#version) | **GET** /info/version | Get API version |


## `getInfo()`

```php
getInfo($flags): \lthn\lthn\InfoModel
```

Get detailed information about the blockchain and daemon state

### Example

```php
<?php
require_once(__DIR__ . '/vendor/autoload.php');



$apiInstance = new lthn\Api\InfoApi(
    // If you want use custom http client, pass your client which implements `GuzzleHttp\ClientInterface`.
    // This is optional, `GuzzleHttp\Client` will be used as default.
    new GuzzleHttp\Client()
);
$flags = 'flags_example'; // string | Possible values: net_time_delta_median, current_network_hashrate_50, current_network_hashrate_350, seconds_for_10_blocks, seconds_for_30_blocks, transactions_daily_stat, last_pos_timestamp, last_pow_timestamp, total_coins, last_block_size, tx_count_in_last_block, pos_sequence_factor, pow_sequence_factor, pos_difficulty, performance, outs_stat, expirations_median.

try {
    $result = $apiInstance->getInfo($flags);
    print_r($result);
} catch (Exception $e) {
    echo 'Exception when calling InfoApi->getInfo: ', $e->getMessage(), PHP_EOL;
}
```

### Parameters

| Name | Type | Description  | Notes |
| ------------- | ------------- | ------------- | ------------- |
| **flags** | **string**| Possible values: net_time_delta_median, current_network_hashrate_50, current_network_hashrate_350, seconds_for_10_blocks, seconds_for_30_blocks, transactions_daily_stat, last_pos_timestamp, last_pow_timestamp, total_coins, last_block_size, tx_count_in_last_block, pos_sequence_factor, pow_sequence_factor, pos_difficulty, performance, outs_stat, expirations_median. | [optional] |

### Return type

[**\lthn\lthn\InfoModel**](../Model/InfoModel.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: Not defined
- **Accept**: `application/json`

[[Back to top]](#) [[Back to API list]](../../README.md#endpoints)
[[Back to Model list]](../../README.md#models)
[[Back to README]](../../README.md)

## `version()`

```php
version(): \lthn\lthn\VersionModel
```

Get API version

Returns the current version of the API.

### Example

```php
<?php
require_once(__DIR__ . '/vendor/autoload.php');



$apiInstance = new lthn\Api\InfoApi(
    // If you want use custom http client, pass your client which implements `GuzzleHttp\ClientInterface`.
    // This is optional, `GuzzleHttp\Client` will be used as default.
    new GuzzleHttp\Client()
);

try {
    $result = $apiInstance->version();
    print_r($result);
} catch (Exception $e) {
    echo 'Exception when calling InfoApi->version: ', $e->getMessage(), PHP_EOL;
}
```

### Parameters

This endpoint does not need any parameter.

### Return type

[**\lthn\lthn\VersionModel**](../Model/VersionModel.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: Not defined
- **Accept**: `application/json`

[[Back to top]](#) [[Back to API list]](../../README.md#endpoints)
[[Back to Model list]](../../README.md#models)
[[Back to README]](../../README.md)
