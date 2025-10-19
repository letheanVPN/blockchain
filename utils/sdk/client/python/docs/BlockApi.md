# lthn.BlockApi

All URIs are relative to *http://127.0.0.1:36943*

Method | HTTP request | Description
------------- | ------------- | -------------
[**create_block_template**](BlockApi.md#create_block_template) | **POST** /block/template | Create a block template for mining
[**get_block**](BlockApi.md#get_block) | **GET** /block/{identifier} | Get a block by its hash or height (ID)
[**get_blocks**](BlockApi.md#get_blocks) | **GET** /block | Get one or more blocks, with optional pagination.
[**get_height**](BlockApi.md#get_height) | **GET** /block/height | Get the current blockchain height
[**submit_block**](BlockApi.md#submit_block) | **POST** /block/submit | Submit a new block to the network


# **create_block_template**
> BlockTemplateModel create_block_template(block_template_request_model)

Create a block template for mining

### Example


```python
import lthn
from lthn.models.block_template_model import BlockTemplateModel
from lthn.models.block_template_request_model import BlockTemplateRequestModel
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
    api_instance = lthn.BlockApi(api_client)
    block_template_request_model = lthn.BlockTemplateRequestModel() # BlockTemplateRequestModel | 

    try:
        # Create a block template for mining
        api_response = api_instance.create_block_template(block_template_request_model)
        print("The response of BlockApi->create_block_template:\n")
        pprint(api_response)
    except Exception as e:
        print("Exception when calling BlockApi->create_block_template: %s\n" % e)
```



### Parameters


Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **block_template_request_model** | [**BlockTemplateRequestModel**](BlockTemplateRequestModel.md)|  | 

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
**500** | text/plain |  -  |
**400** | text/plain |  -  |
**200** | OK |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **get_block**
> BlockDetailsModel get_block(identifier)

Get a block by its hash or height (ID)

### Example


```python
import lthn
from lthn.models.block_details_model import BlockDetailsModel
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
    api_instance = lthn.BlockApi(api_client)
    identifier = 'identifier_example' # str | The hash (hex string) or height (integer) of the block to retrieve.

    try:
        # Get a block by its hash or height (ID)
        api_response = api_instance.get_block(identifier)
        print("The response of BlockApi->get_block:\n")
        pprint(api_response)
    except Exception as e:
        print("Exception when calling BlockApi->get_block: %s\n" % e)
```



### Parameters


Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **identifier** | **str**| The hash (hex string) or height (integer) of the block to retrieve. | 

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
**404** | text/plain |  -  |
**400** | text/plain |  -  |
**200** | OK |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **get_blocks**
> List[BlockDetailsModel] get_blocks()

Get one or more blocks, with optional pagination.

### Example


```python
import lthn
from lthn.models.block_details_model import BlockDetailsModel
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
    api_instance = lthn.BlockApi(api_client)

    try:
        # Get one or more blocks, with optional pagination.
        api_response = api_instance.get_blocks()
        print("The response of BlockApi->get_blocks:\n")
        pprint(api_response)
    except Exception as e:
        print("Exception when calling BlockApi->get_blocks: %s\n" % e)
```



### Parameters

This endpoint does not need any parameter.

### Return type

[**List[BlockDetailsModel]**](BlockDetailsModel.md)

### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: Not defined
 - **Accept**: application/json

### HTTP response details

| Status code | Description | Response headers |
|-------------|-------------|------------------|
**404** | text/plain |  -  |
**400** | text/plain |  -  |
**200** | A list of block objects. |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **get_height**
> HeightModel get_height()

Get the current blockchain height

### Example


```python
import lthn
from lthn.models.height_model import HeightModel
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
    api_instance = lthn.BlockApi(api_client)

    try:
        # Get the current blockchain height
        api_response = api_instance.get_height()
        print("The response of BlockApi->get_height:\n")
        pprint(api_response)
    except Exception as e:
        print("Exception when calling BlockApi->get_height: %s\n" % e)
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
**200** | OK |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **submit_block**
> SubmitBlockResponseModel submit_block(submit_block_request_model)

Submit a new block to the network

### Example


```python
import lthn
from lthn.models.submit_block_request_model import SubmitBlockRequestModel
from lthn.models.submit_block_response_model import SubmitBlockResponseModel
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
    api_instance = lthn.BlockApi(api_client)
    submit_block_request_model = lthn.SubmitBlockRequestModel() # SubmitBlockRequestModel | 

    try:
        # Submit a new block to the network
        api_response = api_instance.submit_block(submit_block_request_model)
        print("The response of BlockApi->submit_block:\n")
        pprint(api_response)
    except Exception as e:
        print("Exception when calling BlockApi->submit_block: %s\n" % e)
```



### Parameters


Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **submit_block_request_model** | [**SubmitBlockRequestModel**](SubmitBlockRequestModel.md)|  | 

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
**406** | text/plain |  -  |
**400** | text/plain |  -  |
**200** | OK |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

