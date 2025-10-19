# TransactionInputModel

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**Amount** | Pointer to **int32** |  | [optional] 
**GlobalIndexes** | Pointer to **[]int32** |  | [optional] 
**HtlcOrigin** | Pointer to **string** |  | [optional] 
**KimageOrMsId** | Pointer to **string** |  | [optional] 
**MultisigCount** | Pointer to **int32** |  | [optional] 

## Methods

### NewTransactionInputModel

`func NewTransactionInputModel() *TransactionInputModel`

NewTransactionInputModel instantiates a new TransactionInputModel object
This constructor will assign default values to properties that have it defined,
and makes sure properties required by API are set, but the set of arguments
will change when the set of required properties is changed

### NewTransactionInputModelWithDefaults

`func NewTransactionInputModelWithDefaults() *TransactionInputModel`

NewTransactionInputModelWithDefaults instantiates a new TransactionInputModel object
This constructor will only assign default values to properties that have it defined,
but it doesn't guarantee that properties required by API are set

### GetAmount

`func (o *TransactionInputModel) GetAmount() int32`

GetAmount returns the Amount field if non-nil, zero value otherwise.

### GetAmountOk

`func (o *TransactionInputModel) GetAmountOk() (*int32, bool)`

GetAmountOk returns a tuple with the Amount field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetAmount

`func (o *TransactionInputModel) SetAmount(v int32)`

SetAmount sets Amount field to given value.

### HasAmount

`func (o *TransactionInputModel) HasAmount() bool`

HasAmount returns a boolean if a field has been set.

### GetGlobalIndexes

`func (o *TransactionInputModel) GetGlobalIndexes() []int32`

GetGlobalIndexes returns the GlobalIndexes field if non-nil, zero value otherwise.

### GetGlobalIndexesOk

`func (o *TransactionInputModel) GetGlobalIndexesOk() (*[]int32, bool)`

GetGlobalIndexesOk returns a tuple with the GlobalIndexes field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetGlobalIndexes

`func (o *TransactionInputModel) SetGlobalIndexes(v []int32)`

SetGlobalIndexes sets GlobalIndexes field to given value.

### HasGlobalIndexes

`func (o *TransactionInputModel) HasGlobalIndexes() bool`

HasGlobalIndexes returns a boolean if a field has been set.

### GetHtlcOrigin

`func (o *TransactionInputModel) GetHtlcOrigin() string`

GetHtlcOrigin returns the HtlcOrigin field if non-nil, zero value otherwise.

### GetHtlcOriginOk

`func (o *TransactionInputModel) GetHtlcOriginOk() (*string, bool)`

GetHtlcOriginOk returns a tuple with the HtlcOrigin field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetHtlcOrigin

`func (o *TransactionInputModel) SetHtlcOrigin(v string)`

SetHtlcOrigin sets HtlcOrigin field to given value.

### HasHtlcOrigin

`func (o *TransactionInputModel) HasHtlcOrigin() bool`

HasHtlcOrigin returns a boolean if a field has been set.

### GetKimageOrMsId

`func (o *TransactionInputModel) GetKimageOrMsId() string`

GetKimageOrMsId returns the KimageOrMsId field if non-nil, zero value otherwise.

### GetKimageOrMsIdOk

`func (o *TransactionInputModel) GetKimageOrMsIdOk() (*string, bool)`

GetKimageOrMsIdOk returns a tuple with the KimageOrMsId field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetKimageOrMsId

`func (o *TransactionInputModel) SetKimageOrMsId(v string)`

SetKimageOrMsId sets KimageOrMsId field to given value.

### HasKimageOrMsId

`func (o *TransactionInputModel) HasKimageOrMsId() bool`

HasKimageOrMsId returns a boolean if a field has been set.

### GetMultisigCount

`func (o *TransactionInputModel) GetMultisigCount() int32`

GetMultisigCount returns the MultisigCount field if non-nil, zero value otherwise.

### GetMultisigCountOk

`func (o *TransactionInputModel) GetMultisigCountOk() (*int32, bool)`

GetMultisigCountOk returns a tuple with the MultisigCount field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetMultisigCount

`func (o *TransactionInputModel) SetMultisigCount(v int32)`

SetMultisigCount sets MultisigCount field to given value.

### HasMultisigCount

`func (o *TransactionInputModel) HasMultisigCount() bool`

HasMultisigCount returns a boolean if a field has been set.


[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


