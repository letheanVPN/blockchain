# PerformanceModel

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**BlockProcessing** | Pointer to [**BlockProcessingPerformanceModel**](BlockProcessingPerformanceModel.md) |  | [optional] 
**TxProcessing** | Pointer to [**TxProcessingPerformanceModel**](TxProcessingPerformanceModel.md) |  | [optional] 
**TxPool** | Pointer to [**TxPoolPerformanceModel**](TxPoolPerformanceModel.md) |  | [optional] 
**DbStatInfo** | Pointer to [**DbStatInfoModel**](DbStatInfoModel.md) |  | [optional] 

## Methods

### NewPerformanceModel

`func NewPerformanceModel() *PerformanceModel`

NewPerformanceModel instantiates a new PerformanceModel object
This constructor will assign default values to properties that have it defined,
and makes sure properties required by API are set, but the set of arguments
will change when the set of required properties is changed

### NewPerformanceModelWithDefaults

`func NewPerformanceModelWithDefaults() *PerformanceModel`

NewPerformanceModelWithDefaults instantiates a new PerformanceModel object
This constructor will only assign default values to properties that have it defined,
but it doesn't guarantee that properties required by API are set

### GetBlockProcessing

`func (o *PerformanceModel) GetBlockProcessing() BlockProcessingPerformanceModel`

GetBlockProcessing returns the BlockProcessing field if non-nil, zero value otherwise.

### GetBlockProcessingOk

`func (o *PerformanceModel) GetBlockProcessingOk() (*BlockProcessingPerformanceModel, bool)`

GetBlockProcessingOk returns a tuple with the BlockProcessing field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetBlockProcessing

`func (o *PerformanceModel) SetBlockProcessing(v BlockProcessingPerformanceModel)`

SetBlockProcessing sets BlockProcessing field to given value.

### HasBlockProcessing

`func (o *PerformanceModel) HasBlockProcessing() bool`

HasBlockProcessing returns a boolean if a field has been set.

### GetTxProcessing

`func (o *PerformanceModel) GetTxProcessing() TxProcessingPerformanceModel`

GetTxProcessing returns the TxProcessing field if non-nil, zero value otherwise.

### GetTxProcessingOk

`func (o *PerformanceModel) GetTxProcessingOk() (*TxProcessingPerformanceModel, bool)`

GetTxProcessingOk returns a tuple with the TxProcessing field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTxProcessing

`func (o *PerformanceModel) SetTxProcessing(v TxProcessingPerformanceModel)`

SetTxProcessing sets TxProcessing field to given value.

### HasTxProcessing

`func (o *PerformanceModel) HasTxProcessing() bool`

HasTxProcessing returns a boolean if a field has been set.

### GetTxPool

`func (o *PerformanceModel) GetTxPool() TxPoolPerformanceModel`

GetTxPool returns the TxPool field if non-nil, zero value otherwise.

### GetTxPoolOk

`func (o *PerformanceModel) GetTxPoolOk() (*TxPoolPerformanceModel, bool)`

GetTxPoolOk returns a tuple with the TxPool field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTxPool

`func (o *PerformanceModel) SetTxPool(v TxPoolPerformanceModel)`

SetTxPool sets TxPool field to given value.

### HasTxPool

`func (o *PerformanceModel) HasTxPool() bool`

HasTxPool returns a boolean if a field has been set.

### GetDbStatInfo

`func (o *PerformanceModel) GetDbStatInfo() DbStatInfoModel`

GetDbStatInfo returns the DbStatInfo field if non-nil, zero value otherwise.

### GetDbStatInfoOk

`func (o *PerformanceModel) GetDbStatInfoOk() (*DbStatInfoModel, bool)`

GetDbStatInfoOk returns a tuple with the DbStatInfo field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetDbStatInfo

`func (o *PerformanceModel) SetDbStatInfo(v DbStatInfoModel)`

SetDbStatInfo sets DbStatInfo field to given value.

### HasDbStatInfo

`func (o *PerformanceModel) HasDbStatInfo() bool`

HasDbStatInfo returns a boolean if a field has been set.


[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


