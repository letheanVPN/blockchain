# InfoApi

All URIs are relative to *http://127.0.0.1:36943*

| Method | HTTP request | Description |
|------------- | ------------- | -------------|
| [**getInfo**](InfoApi.md#getInfo) | **GET** /info | Get detailed information about the blockchain and daemon state |
| [**version**](InfoApi.md#version) | **GET** /info/version | Get API version |


<a id="getInfo"></a>
# **getInfo**
> InfoModel getInfo(flags)

Get detailed information about the blockchain and daemon state

### Example
```java
// Import classes:
import invalidPackageName.ApiClient;
import invalidPackageName.ApiException;
import invalidPackageName.Configuration;
import invalidPackageName.models.*;
import lthn.InfoApi;

public class Example {
  public static void main(String[] args) {
    ApiClient defaultClient = Configuration.getDefaultApiClient();
    defaultClient.setBasePath("http://127.0.0.1:36943");

    InfoApi apiInstance = new InfoApi(defaultClient);
    String flags = "flags_example"; // String | Possible values: net_time_delta_median, current_network_hashrate_50, current_network_hashrate_350, seconds_for_10_blocks, seconds_for_30_blocks, transactions_daily_stat, last_pos_timestamp, last_pow_timestamp, total_coins, last_block_size, tx_count_in_last_block, pos_sequence_factor, pow_sequence_factor, pos_difficulty, performance, outs_stat, expirations_median.
    try {
      InfoModel result = apiInstance.getInfo(flags);
      System.out.println(result);
    } catch (ApiException e) {
      System.err.println("Exception when calling InfoApi#getInfo");
      System.err.println("Status code: " + e.getCode());
      System.err.println("Reason: " + e.getResponseBody());
      System.err.println("Response headers: " + e.getResponseHeaders());
      e.printStackTrace();
    }
  }
}
```

### Parameters

| Name | Type | Description  | Notes |
|------------- | ------------- | ------------- | -------------|
| **flags** | **String**| Possible values: net_time_delta_median, current_network_hashrate_50, current_network_hashrate_350, seconds_for_10_blocks, seconds_for_30_blocks, transactions_daily_stat, last_pos_timestamp, last_pow_timestamp, total_coins, last_block_size, tx_count_in_last_block, pos_sequence_factor, pow_sequence_factor, pos_difficulty, performance, outs_stat, expirations_median. | [optional] |

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
| **200** | OK |  -  |

<a id="version"></a>
# **version**
> VersionModel version()

Get API version

Returns the current version of the API.

### Example
```java
// Import classes:
import invalidPackageName.ApiClient;
import invalidPackageName.ApiException;
import invalidPackageName.Configuration;
import invalidPackageName.models.*;
import lthn.InfoApi;

public class Example {
  public static void main(String[] args) {
    ApiClient defaultClient = Configuration.getDefaultApiClient();
    defaultClient.setBasePath("http://127.0.0.1:36943");

    InfoApi apiInstance = new InfoApi(defaultClient);
    try {
      VersionModel result = apiInstance.version();
      System.out.println(result);
    } catch (ApiException e) {
      System.err.println("Exception when calling InfoApi#version");
      System.err.println("Status code: " + e.getCode());
      System.err.println("Reason: " + e.getResponseBody());
      System.err.println("Response headers: " + e.getResponseHeaders());
      e.printStackTrace();
    }
  }
}
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
| **200** | OK |  -  |

