# TransactionDetailsModel

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**Amount** | Pointer to **int32** |  | [optional] 
**Attachments** | Pointer to [**[]TransactionAttachmentModel**](TransactionAttachmentModel.md) |  | [optional] 
**Blob** | Pointer to **string** |  | [optional] 
**BlobSize** | Pointer to **int32** |  | [optional] 
**Extra** | Pointer to [**[]TransactionExtraModel**](TransactionExtraModel.md) |  | [optional] 
**Fee** | Pointer to **int32** |  | [optional] 
**Id** | Pointer to **string** |  | [optional] 
**Ins** | Pointer to [**[]TransactionInputModel**](TransactionInputModel.md) |  | [optional] 
**KeeperBlock** | Pointer to **int64** |  | [optional] 
**ObjectInJson** | Pointer to **string** |  | [optional] 
**Outs** | Pointer to [**[]TransactionOutputModel**](TransactionOutputModel.md) |  | [optional] 
**PubKey** | Pointer to **string** |  | [optional] 
**Timestamp** | Pointer to **int32** |  | [optional] 

## Methods

### NewTransactionDetailsModel

`func NewTransactionDetailsModel() *TransactionDetailsModel`

NewTransactionDetailsModel instantiates a new TransactionDetailsModel object
This constructor will assign default values to properties that have it defined,
and makes sure properties required by API are set, but the set of arguments
will change when the set of required properties is changed

### NewTransactionDetailsModelWithDefaults

`func NewTransactionDetailsModelWithDefaults() *TransactionDetailsModel`

NewTransactionDetailsModelWithDefaults instantiates a new TransactionDetailsModel object
This constructor will only assign default values to properties that have it defined,
but it doesn't guarantee that properties required by API are set

### GetAmount

`func (o *TransactionDetailsModel) GetAmount() int32`

GetAmount returns the Amount field if non-nil, zero value otherwise.

### GetAmountOk

`func (o *TransactionDetailsModel) GetAmountOk() (*int32, bool)`

GetAmountOk returns a tuple with the Amount field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetAmount

`func (o *TransactionDetailsModel) SetAmount(v int32)`

SetAmount sets Amount field to given value.

### HasAmount

`func (o *TransactionDetailsModel) HasAmount() bool`

HasAmount returns a boolean if a field has been set.

### GetAttachments

`func (o *TransactionDetailsModel) GetAttachments() []TransactionAttachmentModel`

GetAttachments returns the Attachments field if non-nil, zero value otherwise.

### GetAttachmentsOk

`func (o *TransactionDetailsModel) GetAttachmentsOk() (*[]TransactionAttachmentModel, bool)`

GetAttachmentsOk returns a tuple with the Attachments field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetAttachments

`func (o *TransactionDetailsModel) SetAttachments(v []TransactionAttachmentModel)`

SetAttachments sets Attachments field to given value.

### HasAttachments

`func (o *TransactionDetailsModel) HasAttachments() bool`

HasAttachments returns a boolean if a field has been set.

### GetBlob

`func (o *TransactionDetailsModel) GetBlob() string`

GetBlob returns the Blob field if non-nil, zero value otherwise.

### GetBlobOk

`func (o *TransactionDetailsModel) GetBlobOk() (*string, bool)`

GetBlobOk returns a tuple with the Blob field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetBlob

`func (o *TransactionDetailsModel) SetBlob(v string)`

SetBlob sets Blob field to given value.

### HasBlob

`func (o *TransactionDetailsModel) HasBlob() bool`

HasBlob returns a boolean if a field has been set.

### GetBlobSize

`func (o *TransactionDetailsModel) GetBlobSize() int32`

GetBlobSize returns the BlobSize field if non-nil, zero value otherwise.

### GetBlobSizeOk

`func (o *TransactionDetailsModel) GetBlobSizeOk() (*int32, bool)`

GetBlobSizeOk returns a tuple with the BlobSize field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetBlobSize

`func (o *TransactionDetailsModel) SetBlobSize(v int32)`

SetBlobSize sets BlobSize field to given value.

### HasBlobSize

`func (o *TransactionDetailsModel) HasBlobSize() bool`

HasBlobSize returns a boolean if a field has been set.

### GetExtra

`func (o *TransactionDetailsModel) GetExtra() []TransactionExtraModel`

GetExtra returns the Extra field if non-nil, zero value otherwise.

### GetExtraOk

`func (o *TransactionDetailsModel) GetExtraOk() (*[]TransactionExtraModel, bool)`

GetExtraOk returns a tuple with the Extra field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetExtra

`func (o *TransactionDetailsModel) SetExtra(v []TransactionExtraModel)`

SetExtra sets Extra field to given value.

### HasExtra

`func (o *TransactionDetailsModel) HasExtra() bool`

HasExtra returns a boolean if a field has been set.

### GetFee

`func (o *TransactionDetailsModel) GetFee() int32`

GetFee returns the Fee field if non-nil, zero value otherwise.

### GetFeeOk

`func (o *TransactionDetailsModel) GetFeeOk() (*int32, bool)`

GetFeeOk returns a tuple with the Fee field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetFee

`func (o *TransactionDetailsModel) SetFee(v int32)`

SetFee sets Fee field to given value.

### HasFee

`func (o *TransactionDetailsModel) HasFee() bool`

HasFee returns a boolean if a field has been set.

### GetId

`func (o *TransactionDetailsModel) GetId() string`

GetId returns the Id field if non-nil, zero value otherwise.

### GetIdOk

`func (o *TransactionDetailsModel) GetIdOk() (*string, bool)`

GetIdOk returns a tuple with the Id field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetId

`func (o *TransactionDetailsModel) SetId(v string)`

SetId sets Id field to given value.

### HasId

`func (o *TransactionDetailsModel) HasId() bool`

HasId returns a boolean if a field has been set.

### GetIns

`func (o *TransactionDetailsModel) GetIns() []TransactionInputModel`

GetIns returns the Ins field if non-nil, zero value otherwise.

### GetInsOk

`func (o *TransactionDetailsModel) GetInsOk() (*[]TransactionInputModel, bool)`

GetInsOk returns a tuple with the Ins field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetIns

`func (o *TransactionDetailsModel) SetIns(v []TransactionInputModel)`

SetIns sets Ins field to given value.

### HasIns

`func (o *TransactionDetailsModel) HasIns() bool`

HasIns returns a boolean if a field has been set.

### GetKeeperBlock

`func (o *TransactionDetailsModel) GetKeeperBlock() int64`

GetKeeperBlock returns the KeeperBlock field if non-nil, zero value otherwise.

### GetKeeperBlockOk

`func (o *TransactionDetailsModel) GetKeeperBlockOk() (*int64, bool)`

GetKeeperBlockOk returns a tuple with the KeeperBlock field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetKeeperBlock

`func (o *TransactionDetailsModel) SetKeeperBlock(v int64)`

SetKeeperBlock sets KeeperBlock field to given value.

### HasKeeperBlock

`func (o *TransactionDetailsModel) HasKeeperBlock() bool`

HasKeeperBlock returns a boolean if a field has been set.

### GetObjectInJson

`func (o *TransactionDetailsModel) GetObjectInJson() string`

GetObjectInJson returns the ObjectInJson field if non-nil, zero value otherwise.

### GetObjectInJsonOk

`func (o *TransactionDetailsModel) GetObjectInJsonOk() (*string, bool)`

GetObjectInJsonOk returns a tuple with the ObjectInJson field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetObjectInJson

`func (o *TransactionDetailsModel) SetObjectInJson(v string)`

SetObjectInJson sets ObjectInJson field to given value.

### HasObjectInJson

`func (o *TransactionDetailsModel) HasObjectInJson() bool`

HasObjectInJson returns a boolean if a field has been set.

### GetOuts

`func (o *TransactionDetailsModel) GetOuts() []TransactionOutputModel`

GetOuts returns the Outs field if non-nil, zero value otherwise.

### GetOutsOk

`func (o *TransactionDetailsModel) GetOutsOk() (*[]TransactionOutputModel, bool)`

GetOutsOk returns a tuple with the Outs field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetOuts

`func (o *TransactionDetailsModel) SetOuts(v []TransactionOutputModel)`

SetOuts sets Outs field to given value.

### HasOuts

`func (o *TransactionDetailsModel) HasOuts() bool`

HasOuts returns a boolean if a field has been set.

### GetPubKey

`func (o *TransactionDetailsModel) GetPubKey() string`

GetPubKey returns the PubKey field if non-nil, zero value otherwise.

### GetPubKeyOk

`func (o *TransactionDetailsModel) GetPubKeyOk() (*string, bool)`

GetPubKeyOk returns a tuple with the PubKey field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetPubKey

`func (o *TransactionDetailsModel) SetPubKey(v string)`

SetPubKey sets PubKey field to given value.

### HasPubKey

`func (o *TransactionDetailsModel) HasPubKey() bool`

HasPubKey returns a boolean if a field has been set.

### GetTimestamp

`func (o *TransactionDetailsModel) GetTimestamp() int32`

GetTimestamp returns the Timestamp field if non-nil, zero value otherwise.

### GetTimestampOk

`func (o *TransactionDetailsModel) GetTimestampOk() (*int32, bool)`

GetTimestampOk returns a tuple with the Timestamp field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTimestamp

`func (o *TransactionDetailsModel) SetTimestamp(v int32)`

SetTimestamp sets Timestamp field to given value.

### HasTimestamp

`func (o *TransactionDetailsModel) HasTimestamp() bool`

HasTimestamp returns a boolean if a field has been set.


[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


