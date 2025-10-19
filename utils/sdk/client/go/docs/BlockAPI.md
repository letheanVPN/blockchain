# \BlockAPI

All URIs are relative to *http://127.0.0.1:36943*

Method | HTTP request | Description
------------- | ------------- | -------------
[**CreateBlockTemplate**](BlockAPI.md#CreateBlockTemplate) | **Post** /block/template | Create a block template for mining
[**GetBlock**](BlockAPI.md#GetBlock) | **Get** /block/{identifier} | Get a block by its hash or height (ID)
[**GetBlocks**](BlockAPI.md#GetBlocks) | **Get** /block | Get one or more blocks, with optional pagination.
[**GetHeight**](BlockAPI.md#GetHeight) | **Get** /block/height | Get the current blockchain height
[**SubmitBlock**](BlockAPI.md#SubmitBlock) | **Post** /block/submit | Submit a new block to the network



## CreateBlockTemplate

> BlockTemplateModel CreateBlockTemplate(ctx).BlockTemplateRequestModel(blockTemplateRequestModel).Execute()

Create a block template for mining

### Example

```go
package main

import (
	"context"
	"fmt"
	"os"
	openapiclient "github.com/letheanVPN/blockchain/lthn"
)

func main() {
	blockTemplateRequestModel := *openapiclient.NewBlockTemplateRequestModel() // BlockTemplateRequestModel | 

	configuration := openapiclient.NewConfiguration()
	apiClient := openapiclient.NewAPIClient(configuration)
	resp, r, err := apiClient.BlockAPI.CreateBlockTemplate(context.Background()).BlockTemplateRequestModel(blockTemplateRequestModel).Execute()
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error when calling `BlockAPI.CreateBlockTemplate``: %v\n", err)
		fmt.Fprintf(os.Stderr, "Full HTTP response: %v\n", r)
	}
	// response from `CreateBlockTemplate`: BlockTemplateModel
	fmt.Fprintf(os.Stdout, "Response from `BlockAPI.CreateBlockTemplate`: %v\n", resp)
}
```

### Path Parameters



### Other Parameters

Other parameters are passed through a pointer to a apiCreateBlockTemplateRequest struct via the builder pattern


Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **blockTemplateRequestModel** | [**BlockTemplateRequestModel**](BlockTemplateRequestModel.md) |  | 

### Return type

[**BlockTemplateModel**](BlockTemplateModel.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: application/json
- **Accept**: application/json

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints)
[[Back to Model list]](../README.md#documentation-for-models)
[[Back to README]](../README.md)


## GetBlock

> BlockDetailsModel GetBlock(ctx, identifier).Execute()

Get a block by its hash or height (ID)

### Example

```go
package main

import (
	"context"
	"fmt"
	"os"
	openapiclient "github.com/letheanVPN/blockchain/lthn"
)

func main() {
	identifier := "identifier_example" // string | The hash (hex string) or height (integer) of the block to retrieve.

	configuration := openapiclient.NewConfiguration()
	apiClient := openapiclient.NewAPIClient(configuration)
	resp, r, err := apiClient.BlockAPI.GetBlock(context.Background(), identifier).Execute()
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error when calling `BlockAPI.GetBlock``: %v\n", err)
		fmt.Fprintf(os.Stderr, "Full HTTP response: %v\n", r)
	}
	// response from `GetBlock`: BlockDetailsModel
	fmt.Fprintf(os.Stdout, "Response from `BlockAPI.GetBlock`: %v\n", resp)
}
```

### Path Parameters


Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
**ctx** | **context.Context** | context for authentication, logging, cancellation, deadlines, tracing, etc.
**identifier** | **string** | The hash (hex string) or height (integer) of the block to retrieve. | 

### Other Parameters

Other parameters are passed through a pointer to a apiGetBlockRequest struct via the builder pattern


Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------


### Return type

[**BlockDetailsModel**](BlockDetailsModel.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: Not defined
- **Accept**: application/json

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints)
[[Back to Model list]](../README.md#documentation-for-models)
[[Back to README]](../README.md)


## GetBlocks

> []BlockDetailsModel GetBlocks(ctx).Execute()

Get one or more blocks, with optional pagination.

### Example

```go
package main

import (
	"context"
	"fmt"
	"os"
	openapiclient "github.com/letheanVPN/blockchain/lthn"
)

func main() {

	configuration := openapiclient.NewConfiguration()
	apiClient := openapiclient.NewAPIClient(configuration)
	resp, r, err := apiClient.BlockAPI.GetBlocks(context.Background()).Execute()
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error when calling `BlockAPI.GetBlocks``: %v\n", err)
		fmt.Fprintf(os.Stderr, "Full HTTP response: %v\n", r)
	}
	// response from `GetBlocks`: []BlockDetailsModel
	fmt.Fprintf(os.Stdout, "Response from `BlockAPI.GetBlocks`: %v\n", resp)
}
```

### Path Parameters

This endpoint does not need any parameter.

### Other Parameters

Other parameters are passed through a pointer to a apiGetBlocksRequest struct via the builder pattern


### Return type

[**[]BlockDetailsModel**](BlockDetailsModel.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: Not defined
- **Accept**: application/json

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints)
[[Back to Model list]](../README.md#documentation-for-models)
[[Back to README]](../README.md)


## GetHeight

> HeightModel GetHeight(ctx).Execute()

Get the current blockchain height

### Example

```go
package main

import (
	"context"
	"fmt"
	"os"
	openapiclient "github.com/letheanVPN/blockchain/lthn"
)

func main() {

	configuration := openapiclient.NewConfiguration()
	apiClient := openapiclient.NewAPIClient(configuration)
	resp, r, err := apiClient.BlockAPI.GetHeight(context.Background()).Execute()
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error when calling `BlockAPI.GetHeight``: %v\n", err)
		fmt.Fprintf(os.Stderr, "Full HTTP response: %v\n", r)
	}
	// response from `GetHeight`: HeightModel
	fmt.Fprintf(os.Stdout, "Response from `BlockAPI.GetHeight`: %v\n", resp)
}
```

### Path Parameters

This endpoint does not need any parameter.

### Other Parameters

Other parameters are passed through a pointer to a apiGetHeightRequest struct via the builder pattern


### Return type

[**HeightModel**](HeightModel.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: Not defined
- **Accept**: application/json

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints)
[[Back to Model list]](../README.md#documentation-for-models)
[[Back to README]](../README.md)


## SubmitBlock

> SubmitBlockResponseModel SubmitBlock(ctx).SubmitBlockRequestModel(submitBlockRequestModel).Execute()

Submit a new block to the network

### Example

```go
package main

import (
	"context"
	"fmt"
	"os"
	openapiclient "github.com/letheanVPN/blockchain/lthn"
)

func main() {
	submitBlockRequestModel := *openapiclient.NewSubmitBlockRequestModel() // SubmitBlockRequestModel | 

	configuration := openapiclient.NewConfiguration()
	apiClient := openapiclient.NewAPIClient(configuration)
	resp, r, err := apiClient.BlockAPI.SubmitBlock(context.Background()).SubmitBlockRequestModel(submitBlockRequestModel).Execute()
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error when calling `BlockAPI.SubmitBlock``: %v\n", err)
		fmt.Fprintf(os.Stderr, "Full HTTP response: %v\n", r)
	}
	// response from `SubmitBlock`: SubmitBlockResponseModel
	fmt.Fprintf(os.Stdout, "Response from `BlockAPI.SubmitBlock`: %v\n", resp)
}
```

### Path Parameters



### Other Parameters

Other parameters are passed through a pointer to a apiSubmitBlockRequest struct via the builder pattern


Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **submitBlockRequestModel** | [**SubmitBlockRequestModel**](SubmitBlockRequestModel.md) |  | 

### Return type

[**SubmitBlockResponseModel**](SubmitBlockResponseModel.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: application/json
- **Accept**: application/json

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints)
[[Back to Model list]](../README.md#documentation-for-models)
[[Back to README]](../README.md)

