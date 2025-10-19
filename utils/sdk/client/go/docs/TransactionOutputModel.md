# TransactionOutputModel

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**Amount** | Pointer to **int32** |  | [optional] 
**GlobalIndex** | Pointer to **int32** |  | [optional] 
**IsSpent** | Pointer to **bool** |  | [optional] 
**MinimumSigs** | Pointer to **int32** |  | [optional] 
**PubKeys** | Pointer to **[]string** |  | [optional] 

## Methods

### NewTransactionOutputModel

`func NewTransactionOutputModel() *TransactionOutputModel`

NewTransactionOutputModel instantiates a new TransactionOutputModel object
This constructor will assign default values to properties that have it defined,
and makes sure properties required by API are set, but the set of arguments
will change when the set of required properties is changed

### NewTransactionOutputModelWithDefaults

`func NewTransactionOutputModelWithDefaults() *TransactionOutputModel`

NewTransactionOutputModelWithDefaults instantiates a new TransactionOutputModel object
This constructor will only assign default values to properties that have it defined,
but it doesn't guarantee that properties required by API are set

### GetAmount

`func (o *TransactionOutputModel) GetAmount() int32`

GetAmount returns the Amount field if non-nil, zero value otherwise.

### GetAmountOk

`func (o *TransactionOutputModel) GetAmountOk() (*int32, bool)`

GetAmountOk returns a tuple with the Amount field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetAmount

`func (o *TransactionOutputModel) SetAmount(v int32)`

SetAmount sets Amount field to given value.

### HasAmount

`func (o *TransactionOutputModel) HasAmount() bool`

HasAmount returns a boolean if a field has been set.

### GetGlobalIndex

`func (o *TransactionOutputModel) GetGlobalIndex() int32`

GetGlobalIndex returns the GlobalIndex field if non-nil, zero value otherwise.

### GetGlobalIndexOk

`func (o *TransactionOutputModel) GetGlobalIndexOk() (*int32, bool)`

GetGlobalIndexOk returns a tuple with the GlobalIndex field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetGlobalIndex

`func (o *TransactionOutputModel) SetGlobalIndex(v int32)`

SetGlobalIndex sets GlobalIndex field to given value.

### HasGlobalIndex

`func (o *TransactionOutputModel) HasGlobalIndex() bool`

HasGlobalIndex returns a boolean if a field has been set.

### GetIsSpent

`func (o *TransactionOutputModel) GetIsSpent() bool`

GetIsSpent returns the IsSpent field if non-nil, zero value otherwise.

### GetIsSpentOk

`func (o *TransactionOutputModel) GetIsSpentOk() (*bool, bool)`

GetIsSpentOk returns a tuple with the IsSpent field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetIsSpent

`func (o *TransactionOutputModel) SetIsSpent(v bool)`

SetIsSpent sets IsSpent field to given value.

### HasIsSpent

`func (o *TransactionOutputModel) HasIsSpent() bool`

HasIsSpent returns a boolean if a field has been set.

### GetMinimumSigs

`func (o *TransactionOutputModel) GetMinimumSigs() int32`

GetMinimumSigs returns the MinimumSigs field if non-nil, zero value otherwise.

### GetMinimumSigsOk

`func (o *TransactionOutputModel) GetMinimumSigsOk() (*int32, bool)`

GetMinimumSigsOk returns a tuple with the MinimumSigs field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetMinimumSigs

`func (o *TransactionOutputModel) SetMinimumSigs(v int32)`

SetMinimumSigs sets MinimumSigs field to given value.

### HasMinimumSigs

`func (o *TransactionOutputModel) HasMinimumSigs() bool`

HasMinimumSigs returns a boolean if a field has been set.

### GetPubKeys

`func (o *TransactionOutputModel) GetPubKeys() []string`

GetPubKeys returns the PubKeys field if non-nil, zero value otherwise.

### GetPubKeysOk

`func (o *TransactionOutputModel) GetPubKeysOk() (*[]string, bool)`

GetPubKeysOk returns a tuple with the PubKeys field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetPubKeys

`func (o *TransactionOutputModel) SetPubKeys(v []string)`

SetPubKeys sets PubKeys field to given value.

### HasPubKeys

`func (o *TransactionOutputModel) HasPubKeys() bool`

HasPubKeys returns a boolean if a field has been set.


[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


