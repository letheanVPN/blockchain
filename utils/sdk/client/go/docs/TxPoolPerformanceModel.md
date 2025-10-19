# TxPoolPerformanceModel

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**TxProcessingTime** | Pointer to **int32** |  | [optional] 
**CheckInputsTypesSupportedTime** | Pointer to **int32** |  | [optional] 
**ExpirationValidateTime** | Pointer to **int32** |  | [optional] 
**ValidateAmountTime** | Pointer to **int32** |  | [optional] 
**ValidateAliasTime** | Pointer to **int32** |  | [optional] 
**CheckKeyimagesWsMsTime** | Pointer to **int32** |  | [optional] 
**CheckInputsTime** | Pointer to **int32** |  | [optional] 
**BeginTxTime** | Pointer to **int32** |  | [optional] 
**UpdateDbTime** | Pointer to **int32** |  | [optional] 
**DbCommitTime** | Pointer to **int32** |  | [optional] 
**CheckPostHf4Balance** | Pointer to **int32** |  | [optional] 

## Methods

### NewTxPoolPerformanceModel

`func NewTxPoolPerformanceModel() *TxPoolPerformanceModel`

NewTxPoolPerformanceModel instantiates a new TxPoolPerformanceModel object
This constructor will assign default values to properties that have it defined,
and makes sure properties required by API are set, but the set of arguments
will change when the set of required properties is changed

### NewTxPoolPerformanceModelWithDefaults

`func NewTxPoolPerformanceModelWithDefaults() *TxPoolPerformanceModel`

NewTxPoolPerformanceModelWithDefaults instantiates a new TxPoolPerformanceModel object
This constructor will only assign default values to properties that have it defined,
but it doesn't guarantee that properties required by API are set

### GetTxProcessingTime

`func (o *TxPoolPerformanceModel) GetTxProcessingTime() int32`

GetTxProcessingTime returns the TxProcessingTime field if non-nil, zero value otherwise.

### GetTxProcessingTimeOk

`func (o *TxPoolPerformanceModel) GetTxProcessingTimeOk() (*int32, bool)`

GetTxProcessingTimeOk returns a tuple with the TxProcessingTime field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTxProcessingTime

`func (o *TxPoolPerformanceModel) SetTxProcessingTime(v int32)`

SetTxProcessingTime sets TxProcessingTime field to given value.

### HasTxProcessingTime

`func (o *TxPoolPerformanceModel) HasTxProcessingTime() bool`

HasTxProcessingTime returns a boolean if a field has been set.

### GetCheckInputsTypesSupportedTime

`func (o *TxPoolPerformanceModel) GetCheckInputsTypesSupportedTime() int32`

GetCheckInputsTypesSupportedTime returns the CheckInputsTypesSupportedTime field if non-nil, zero value otherwise.

### GetCheckInputsTypesSupportedTimeOk

`func (o *TxPoolPerformanceModel) GetCheckInputsTypesSupportedTimeOk() (*int32, bool)`

GetCheckInputsTypesSupportedTimeOk returns a tuple with the CheckInputsTypesSupportedTime field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetCheckInputsTypesSupportedTime

`func (o *TxPoolPerformanceModel) SetCheckInputsTypesSupportedTime(v int32)`

SetCheckInputsTypesSupportedTime sets CheckInputsTypesSupportedTime field to given value.

### HasCheckInputsTypesSupportedTime

`func (o *TxPoolPerformanceModel) HasCheckInputsTypesSupportedTime() bool`

HasCheckInputsTypesSupportedTime returns a boolean if a field has been set.

### GetExpirationValidateTime

`func (o *TxPoolPerformanceModel) GetExpirationValidateTime() int32`

GetExpirationValidateTime returns the ExpirationValidateTime field if non-nil, zero value otherwise.

### GetExpirationValidateTimeOk

`func (o *TxPoolPerformanceModel) GetExpirationValidateTimeOk() (*int32, bool)`

GetExpirationValidateTimeOk returns a tuple with the ExpirationValidateTime field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetExpirationValidateTime

`func (o *TxPoolPerformanceModel) SetExpirationValidateTime(v int32)`

SetExpirationValidateTime sets ExpirationValidateTime field to given value.

### HasExpirationValidateTime

`func (o *TxPoolPerformanceModel) HasExpirationValidateTime() bool`

HasExpirationValidateTime returns a boolean if a field has been set.

### GetValidateAmountTime

`func (o *TxPoolPerformanceModel) GetValidateAmountTime() int32`

GetValidateAmountTime returns the ValidateAmountTime field if non-nil, zero value otherwise.

### GetValidateAmountTimeOk

`func (o *TxPoolPerformanceModel) GetValidateAmountTimeOk() (*int32, bool)`

GetValidateAmountTimeOk returns a tuple with the ValidateAmountTime field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetValidateAmountTime

`func (o *TxPoolPerformanceModel) SetValidateAmountTime(v int32)`

SetValidateAmountTime sets ValidateAmountTime field to given value.

### HasValidateAmountTime

`func (o *TxPoolPerformanceModel) HasValidateAmountTime() bool`

HasValidateAmountTime returns a boolean if a field has been set.

### GetValidateAliasTime

`func (o *TxPoolPerformanceModel) GetValidateAliasTime() int32`

GetValidateAliasTime returns the ValidateAliasTime field if non-nil, zero value otherwise.

### GetValidateAliasTimeOk

`func (o *TxPoolPerformanceModel) GetValidateAliasTimeOk() (*int32, bool)`

GetValidateAliasTimeOk returns a tuple with the ValidateAliasTime field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetValidateAliasTime

`func (o *TxPoolPerformanceModel) SetValidateAliasTime(v int32)`

SetValidateAliasTime sets ValidateAliasTime field to given value.

### HasValidateAliasTime

`func (o *TxPoolPerformanceModel) HasValidateAliasTime() bool`

HasValidateAliasTime returns a boolean if a field has been set.

### GetCheckKeyimagesWsMsTime

`func (o *TxPoolPerformanceModel) GetCheckKeyimagesWsMsTime() int32`

GetCheckKeyimagesWsMsTime returns the CheckKeyimagesWsMsTime field if non-nil, zero value otherwise.

### GetCheckKeyimagesWsMsTimeOk

`func (o *TxPoolPerformanceModel) GetCheckKeyimagesWsMsTimeOk() (*int32, bool)`

GetCheckKeyimagesWsMsTimeOk returns a tuple with the CheckKeyimagesWsMsTime field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetCheckKeyimagesWsMsTime

`func (o *TxPoolPerformanceModel) SetCheckKeyimagesWsMsTime(v int32)`

SetCheckKeyimagesWsMsTime sets CheckKeyimagesWsMsTime field to given value.

### HasCheckKeyimagesWsMsTime

`func (o *TxPoolPerformanceModel) HasCheckKeyimagesWsMsTime() bool`

HasCheckKeyimagesWsMsTime returns a boolean if a field has been set.

### GetCheckInputsTime

`func (o *TxPoolPerformanceModel) GetCheckInputsTime() int32`

GetCheckInputsTime returns the CheckInputsTime field if non-nil, zero value otherwise.

### GetCheckInputsTimeOk

`func (o *TxPoolPerformanceModel) GetCheckInputsTimeOk() (*int32, bool)`

GetCheckInputsTimeOk returns a tuple with the CheckInputsTime field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetCheckInputsTime

`func (o *TxPoolPerformanceModel) SetCheckInputsTime(v int32)`

SetCheckInputsTime sets CheckInputsTime field to given value.

### HasCheckInputsTime

`func (o *TxPoolPerformanceModel) HasCheckInputsTime() bool`

HasCheckInputsTime returns a boolean if a field has been set.

### GetBeginTxTime

`func (o *TxPoolPerformanceModel) GetBeginTxTime() int32`

GetBeginTxTime returns the BeginTxTime field if non-nil, zero value otherwise.

### GetBeginTxTimeOk

`func (o *TxPoolPerformanceModel) GetBeginTxTimeOk() (*int32, bool)`

GetBeginTxTimeOk returns a tuple with the BeginTxTime field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetBeginTxTime

`func (o *TxPoolPerformanceModel) SetBeginTxTime(v int32)`

SetBeginTxTime sets BeginTxTime field to given value.

### HasBeginTxTime

`func (o *TxPoolPerformanceModel) HasBeginTxTime() bool`

HasBeginTxTime returns a boolean if a field has been set.

### GetUpdateDbTime

`func (o *TxPoolPerformanceModel) GetUpdateDbTime() int32`

GetUpdateDbTime returns the UpdateDbTime field if non-nil, zero value otherwise.

### GetUpdateDbTimeOk

`func (o *TxPoolPerformanceModel) GetUpdateDbTimeOk() (*int32, bool)`

GetUpdateDbTimeOk returns a tuple with the UpdateDbTime field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetUpdateDbTime

`func (o *TxPoolPerformanceModel) SetUpdateDbTime(v int32)`

SetUpdateDbTime sets UpdateDbTime field to given value.

### HasUpdateDbTime

`func (o *TxPoolPerformanceModel) HasUpdateDbTime() bool`

HasUpdateDbTime returns a boolean if a field has been set.

### GetDbCommitTime

`func (o *TxPoolPerformanceModel) GetDbCommitTime() int32`

GetDbCommitTime returns the DbCommitTime field if non-nil, zero value otherwise.

### GetDbCommitTimeOk

`func (o *TxPoolPerformanceModel) GetDbCommitTimeOk() (*int32, bool)`

GetDbCommitTimeOk returns a tuple with the DbCommitTime field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetDbCommitTime

`func (o *TxPoolPerformanceModel) SetDbCommitTime(v int32)`

SetDbCommitTime sets DbCommitTime field to given value.

### HasDbCommitTime

`func (o *TxPoolPerformanceModel) HasDbCommitTime() bool`

HasDbCommitTime returns a boolean if a field has been set.

### GetCheckPostHf4Balance

`func (o *TxPoolPerformanceModel) GetCheckPostHf4Balance() int32`

GetCheckPostHf4Balance returns the CheckPostHf4Balance field if non-nil, zero value otherwise.

### GetCheckPostHf4BalanceOk

`func (o *TxPoolPerformanceModel) GetCheckPostHf4BalanceOk() (*int32, bool)`

GetCheckPostHf4BalanceOk returns a tuple with the CheckPostHf4Balance field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetCheckPostHf4Balance

`func (o *TxPoolPerformanceModel) SetCheckPostHf4Balance(v int32)`

SetCheckPostHf4Balance sets CheckPostHf4Balance field to given value.

### HasCheckPostHf4Balance

`func (o *TxPoolPerformanceModel) HasCheckPostHf4Balance() bool`

HasCheckPostHf4Balance returns a boolean if a field has been set.


[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


