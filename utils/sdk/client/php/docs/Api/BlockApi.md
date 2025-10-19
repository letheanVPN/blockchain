# lthn\BlockApi

All URIs are relative to http://127.0.0.1:36943, except if the operation defines another base path.

| Method | HTTP request | Description |
| ------------- | ------------- | ------------- |
| [**createBlockTemplate()**](BlockApi.md#createBlockTemplate) | **POST** /block/template | Create a block template for mining |
| [**getBlock()**](BlockApi.md#getBlock) | **GET** /block/{identifier} | Get a block by its hash or height (ID) |
| [**getBlocks()**](BlockApi.md#getBlocks) | **GET** /block | Get one or more blocks, with optional pagination. |
| [**getHeight()**](BlockApi.md#getHeight) | **GET** /block/height | Get the current blockchain height |
| [**submitBlock()**](BlockApi.md#submitBlock) | **POST** /block/submit | Submit a new block to the network |


## `createBlockTemplate()`

```php
createBlockTemplate($block_template_request_model): \lthn\lthn\BlockTemplateModel
```

Create a block template for mining

### Example

```php
<?php
require_once(__DIR__ . '/vendor/autoload.php');



$apiInstance = new lthn\Api\BlockApi(
    // If you want use custom http client, pass your client which implements `GuzzleHttp\ClientInterface`.
    // This is optional, `GuzzleHttp\Client` will be used as default.
    new GuzzleHttp\Client()
);
$block_template_request_model = new \lthn\lthn\BlockTemplateRequestModel(); // \lthn\lthn\BlockTemplateRequestModel

try {
    $result = $apiInstance->createBlockTemplate($block_template_request_model);
    print_r($result);
} catch (Exception $e) {
    echo 'Exception when calling BlockApi->createBlockTemplate: ', $e->getMessage(), PHP_EOL;
}
```

### Parameters

| Name | Type | Description  | Notes |
| ------------- | ------------- | ------------- | ------------- |
| **block_template_request_model** | [**\lthn\lthn\BlockTemplateRequestModel**](../Model/BlockTemplateRequestModel.md)|  | |

### Return type

[**\lthn\lthn\BlockTemplateModel**](../Model/BlockTemplateModel.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: `application/json`
- **Accept**: `application/json`

[[Back to top]](#) [[Back to API list]](../../README.md#endpoints)
[[Back to Model list]](../../README.md#models)
[[Back to README]](../../README.md)

## `getBlock()`

```php
getBlock($identifier): \lthn\lthn\BlockDetailsModel
```

Get a block by its hash or height (ID)

### Example

```php
<?php
require_once(__DIR__ . '/vendor/autoload.php');



$apiInstance = new lthn\Api\BlockApi(
    // If you want use custom http client, pass your client which implements `GuzzleHttp\ClientInterface`.
    // This is optional, `GuzzleHttp\Client` will be used as default.
    new GuzzleHttp\Client()
);
$identifier = 'identifier_example'; // string | The hash (hex string) or height (integer) of the block to retrieve.

try {
    $result = $apiInstance->getBlock($identifier);
    print_r($result);
} catch (Exception $e) {
    echo 'Exception when calling BlockApi->getBlock: ', $e->getMessage(), PHP_EOL;
}
```

### Parameters

| Name | Type | Description  | Notes |
| ------------- | ------------- | ------------- | ------------- |
| **identifier** | **string**| The hash (hex string) or height (integer) of the block to retrieve. | |

### Return type

[**\lthn\lthn\BlockDetailsModel**](../Model/BlockDetailsModel.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: Not defined
- **Accept**: `application/json`

[[Back to top]](#) [[Back to API list]](../../README.md#endpoints)
[[Back to Model list]](../../README.md#models)
[[Back to README]](../../README.md)

## `getBlocks()`

```php
getBlocks(): \lthn\lthn\BlockDetailsModel[]
```

Get one or more blocks, with optional pagination.

### Example

```php
<?php
require_once(__DIR__ . '/vendor/autoload.php');



$apiInstance = new lthn\Api\BlockApi(
    // If you want use custom http client, pass your client which implements `GuzzleHttp\ClientInterface`.
    // This is optional, `GuzzleHttp\Client` will be used as default.
    new GuzzleHttp\Client()
);

try {
    $result = $apiInstance->getBlocks();
    print_r($result);
} catch (Exception $e) {
    echo 'Exception when calling BlockApi->getBlocks: ', $e->getMessage(), PHP_EOL;
}
```

### Parameters

This endpoint does not need any parameter.

### Return type

[**\lthn\lthn\BlockDetailsModel[]**](../Model/BlockDetailsModel.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: Not defined
- **Accept**: `application/json`

[[Back to top]](#) [[Back to API list]](../../README.md#endpoints)
[[Back to Model list]](../../README.md#models)
[[Back to README]](../../README.md)

## `getHeight()`

```php
getHeight(): \lthn\lthn\HeightModel
```

Get the current blockchain height

### Example

```php
<?php
require_once(__DIR__ . '/vendor/autoload.php');



$apiInstance = new lthn\Api\BlockApi(
    // If you want use custom http client, pass your client which implements `GuzzleHttp\ClientInterface`.
    // This is optional, `GuzzleHttp\Client` will be used as default.
    new GuzzleHttp\Client()
);

try {
    $result = $apiInstance->getHeight();
    print_r($result);
} catch (Exception $e) {
    echo 'Exception when calling BlockApi->getHeight: ', $e->getMessage(), PHP_EOL;
}
```

### Parameters

This endpoint does not need any parameter.

### Return type

[**\lthn\lthn\HeightModel**](../Model/HeightModel.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: Not defined
- **Accept**: `application/json`

[[Back to top]](#) [[Back to API list]](../../README.md#endpoints)
[[Back to Model list]](../../README.md#models)
[[Back to README]](../../README.md)

## `submitBlock()`

```php
submitBlock($submit_block_request_model): \lthn\lthn\SubmitBlockResponseModel
```

Submit a new block to the network

### Example

```php
<?php
require_once(__DIR__ . '/vendor/autoload.php');



$apiInstance = new lthn\Api\BlockApi(
    // If you want use custom http client, pass your client which implements `GuzzleHttp\ClientInterface`.
    // This is optional, `GuzzleHttp\Client` will be used as default.
    new GuzzleHttp\Client()
);
$submit_block_request_model = new \lthn\lthn\SubmitBlockRequestModel(); // \lthn\lthn\SubmitBlockRequestModel

try {
    $result = $apiInstance->submitBlock($submit_block_request_model);
    print_r($result);
} catch (Exception $e) {
    echo 'Exception when calling BlockApi->submitBlock: ', $e->getMessage(), PHP_EOL;
}
```

### Parameters

| Name | Type | Description  | Notes |
| ------------- | ------------- | ------------- | ------------- |
| **submit_block_request_model** | [**\lthn\lthn\SubmitBlockRequestModel**](../Model/SubmitBlockRequestModel.md)|  | |

### Return type

[**\lthn\lthn\SubmitBlockResponseModel**](../Model/SubmitBlockResponseModel.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: `application/json`
- **Accept**: `application/json`

[[Back to top]](#) [[Back to API list]](../../README.md#endpoints)
[[Back to Model list]](../../README.md#models)
[[Back to README]](../../README.md)
