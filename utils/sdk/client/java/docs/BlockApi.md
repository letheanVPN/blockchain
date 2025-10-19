# BlockApi

All URIs are relative to *http://127.0.0.1:36943*

| Method | HTTP request | Description |
|------------- | ------------- | -------------|
| [**createBlockTemplate**](BlockApi.md#createBlockTemplate) | **POST** /block/template | Create a block template for mining |
| [**getBlock**](BlockApi.md#getBlock) | **GET** /block/{identifier} | Get a block by its hash or height (ID) |
| [**getBlocks**](BlockApi.md#getBlocks) | **GET** /block | Get one or more blocks, with optional pagination. |
| [**getHeight**](BlockApi.md#getHeight) | **GET** /block/height | Get the current blockchain height |
| [**submitBlock**](BlockApi.md#submitBlock) | **POST** /block/submit | Submit a new block to the network |


<a id="createBlockTemplate"></a>
# **createBlockTemplate**
> BlockTemplateModel createBlockTemplate(blockTemplateRequestModel)

Create a block template for mining

### Example
```java
// Import classes:
import invalidPackageName.ApiClient;
import invalidPackageName.ApiException;
import invalidPackageName.Configuration;
import invalidPackageName.models.*;
import lthn.BlockApi;

public class Example {
  public static void main(String[] args) {
    ApiClient defaultClient = Configuration.getDefaultApiClient();
    defaultClient.setBasePath("http://127.0.0.1:36943");

    BlockApi apiInstance = new BlockApi(defaultClient);
    BlockTemplateRequestModel blockTemplateRequestModel = new BlockTemplateRequestModel(); // BlockTemplateRequestModel | 
    try {
      BlockTemplateModel result = apiInstance.createBlockTemplate(blockTemplateRequestModel);
      System.out.println(result);
    } catch (ApiException e) {
      System.err.println("Exception when calling BlockApi#createBlockTemplate");
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
| **blockTemplateRequestModel** | [**BlockTemplateRequestModel**](BlockTemplateRequestModel.md)|  | |

### Return type

[**BlockTemplateModel**](BlockTemplateModel.md)

### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: application/json
 - **Accept**: application/json

### HTTP response details
| Status code | Description | Response headers |
|-------------|-------------|------------------|
| **500** | text/plain |  -  |
| **400** | text/plain |  -  |
| **200** | OK |  -  |

<a id="getBlock"></a>
# **getBlock**
> BlockDetailsModel getBlock(identifier)

Get a block by its hash or height (ID)

### Example
```java
// Import classes:
import invalidPackageName.ApiClient;
import invalidPackageName.ApiException;
import invalidPackageName.Configuration;
import invalidPackageName.models.*;
import lthn.BlockApi;

public class Example {
  public static void main(String[] args) {
    ApiClient defaultClient = Configuration.getDefaultApiClient();
    defaultClient.setBasePath("http://127.0.0.1:36943");

    BlockApi apiInstance = new BlockApi(defaultClient);
    String identifier = "identifier_example"; // String | The hash (hex string) or height (integer) of the block to retrieve.
    try {
      BlockDetailsModel result = apiInstance.getBlock(identifier);
      System.out.println(result);
    } catch (ApiException e) {
      System.err.println("Exception when calling BlockApi#getBlock");
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
| **identifier** | **String**| The hash (hex string) or height (integer) of the block to retrieve. | |

### Return type

[**BlockDetailsModel**](BlockDetailsModel.md)

### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: Not defined
 - **Accept**: application/json

### HTTP response details
| Status code | Description | Response headers |
|-------------|-------------|------------------|
| **404** | text/plain |  -  |
| **400** | text/plain |  -  |
| **200** | OK |  -  |

<a id="getBlocks"></a>
# **getBlocks**
> List&lt;BlockDetailsModel&gt; getBlocks()

Get one or more blocks, with optional pagination.

### Example
```java
// Import classes:
import invalidPackageName.ApiClient;
import invalidPackageName.ApiException;
import invalidPackageName.Configuration;
import invalidPackageName.models.*;
import lthn.BlockApi;

public class Example {
  public static void main(String[] args) {
    ApiClient defaultClient = Configuration.getDefaultApiClient();
    defaultClient.setBasePath("http://127.0.0.1:36943");

    BlockApi apiInstance = new BlockApi(defaultClient);
    try {
      List<BlockDetailsModel> result = apiInstance.getBlocks();
      System.out.println(result);
    } catch (ApiException e) {
      System.err.println("Exception when calling BlockApi#getBlocks");
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

[**List&lt;BlockDetailsModel&gt;**](BlockDetailsModel.md)

### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: Not defined
 - **Accept**: application/json

### HTTP response details
| Status code | Description | Response headers |
|-------------|-------------|------------------|
| **404** | text/plain |  -  |
| **400** | text/plain |  -  |
| **200** | A list of block objects. |  -  |

<a id="getHeight"></a>
# **getHeight**
> HeightModel getHeight()

Get the current blockchain height

### Example
```java
// Import classes:
import invalidPackageName.ApiClient;
import invalidPackageName.ApiException;
import invalidPackageName.Configuration;
import invalidPackageName.models.*;
import lthn.BlockApi;

public class Example {
  public static void main(String[] args) {
    ApiClient defaultClient = Configuration.getDefaultApiClient();
    defaultClient.setBasePath("http://127.0.0.1:36943");

    BlockApi apiInstance = new BlockApi(defaultClient);
    try {
      HeightModel result = apiInstance.getHeight();
      System.out.println(result);
    } catch (ApiException e) {
      System.err.println("Exception when calling BlockApi#getHeight");
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

[**HeightModel**](HeightModel.md)

### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: Not defined
 - **Accept**: application/json

### HTTP response details
| Status code | Description | Response headers |
|-------------|-------------|------------------|
| **200** | OK |  -  |

<a id="submitBlock"></a>
# **submitBlock**
> SubmitBlockResponseModel submitBlock(submitBlockRequestModel)

Submit a new block to the network

### Example
```java
// Import classes:
import invalidPackageName.ApiClient;
import invalidPackageName.ApiException;
import invalidPackageName.Configuration;
import invalidPackageName.models.*;
import lthn.BlockApi;

public class Example {
  public static void main(String[] args) {
    ApiClient defaultClient = Configuration.getDefaultApiClient();
    defaultClient.setBasePath("http://127.0.0.1:36943");

    BlockApi apiInstance = new BlockApi(defaultClient);
    SubmitBlockRequestModel submitBlockRequestModel = new SubmitBlockRequestModel(); // SubmitBlockRequestModel | 
    try {
      SubmitBlockResponseModel result = apiInstance.submitBlock(submitBlockRequestModel);
      System.out.println(result);
    } catch (ApiException e) {
      System.err.println("Exception when calling BlockApi#submitBlock");
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
| **submitBlockRequestModel** | [**SubmitBlockRequestModel**](SubmitBlockRequestModel.md)|  | |

### Return type

[**SubmitBlockResponseModel**](SubmitBlockResponseModel.md)

### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: application/json
 - **Accept**: application/json

### HTTP response details
| Status code | Description | Response headers |
|-------------|-------------|------------------|
| **406** | text/plain |  -  |
| **400** | text/plain |  -  |
| **200** | OK |  -  |

