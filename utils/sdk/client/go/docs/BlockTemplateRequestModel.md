# BlockTemplateRequestModel

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**MinerAddress** | Pointer to **string** |  | [optional] 
**StakeholderAddress** | Pointer to **string** |  | [optional] 
**ExNonce** | Pointer to **string** |  | [optional] 
**PosBlock** | Pointer to **bool** |  | [optional] 
**IgnorePowTsCheck** | Pointer to **bool** |  | [optional] 
**Pe** | Pointer to [**PosEntryModel**](PosEntryModel.md) |  | [optional] 
**ExplicitTxs** | Pointer to **[]string** |  | [optional] 

## Methods

### NewBlockTemplateRequestModel

`func NewBlockTemplateRequestModel() *BlockTemplateRequestModel`

NewBlockTemplateRequestModel instantiates a new BlockTemplateRequestModel object
This constructor will assign default values to properties that have it defined,
and makes sure properties required by API are set, but the set of arguments
will change when the set of required properties is changed

### NewBlockTemplateRequestModelWithDefaults

`func NewBlockTemplateRequestModelWithDefaults() *BlockTemplateRequestModel`

NewBlockTemplateRequestModelWithDefaults instantiates a new BlockTemplateRequestModel object
This constructor will only assign default values to properties that have it defined,
but it doesn't guarantee that properties required by API are set

### GetMinerAddress

`func (o *BlockTemplateRequestModel) GetMinerAddress() string`

GetMinerAddress returns the MinerAddress field if non-nil, zero value otherwise.

### GetMinerAddressOk

`func (o *BlockTemplateRequestModel) GetMinerAddressOk() (*string, bool)`

GetMinerAddressOk returns a tuple with the MinerAddress field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetMinerAddress

`func (o *BlockTemplateRequestModel) SetMinerAddress(v string)`

SetMinerAddress sets MinerAddress field to given value.

### HasMinerAddress

`func (o *BlockTemplateRequestModel) HasMinerAddress() bool`

HasMinerAddress returns a boolean if a field has been set.

### GetStakeholderAddress

`func (o *BlockTemplateRequestModel) GetStakeholderAddress() string`

GetStakeholderAddress returns the StakeholderAddress field if non-nil, zero value otherwise.

### GetStakeholderAddressOk

`func (o *BlockTemplateRequestModel) GetStakeholderAddressOk() (*string, bool)`

GetStakeholderAddressOk returns a tuple with the StakeholderAddress field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetStakeholderAddress

`func (o *BlockTemplateRequestModel) SetStakeholderAddress(v string)`

SetStakeholderAddress sets StakeholderAddress field to given value.

### HasStakeholderAddress

`func (o *BlockTemplateRequestModel) HasStakeholderAddress() bool`

HasStakeholderAddress returns a boolean if a field has been set.

### GetExNonce

`func (o *BlockTemplateRequestModel) GetExNonce() string`

GetExNonce returns the ExNonce field if non-nil, zero value otherwise.

### GetExNonceOk

`func (o *BlockTemplateRequestModel) GetExNonceOk() (*string, bool)`

GetExNonceOk returns a tuple with the ExNonce field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetExNonce

`func (o *BlockTemplateRequestModel) SetExNonce(v string)`

SetExNonce sets ExNonce field to given value.

### HasExNonce

`func (o *BlockTemplateRequestModel) HasExNonce() bool`

HasExNonce returns a boolean if a field has been set.

### GetPosBlock

`func (o *BlockTemplateRequestModel) GetPosBlock() bool`

GetPosBlock returns the PosBlock field if non-nil, zero value otherwise.

### GetPosBlockOk

`func (o *BlockTemplateRequestModel) GetPosBlockOk() (*bool, bool)`

GetPosBlockOk returns a tuple with the PosBlock field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetPosBlock

`func (o *BlockTemplateRequestModel) SetPosBlock(v bool)`

SetPosBlock sets PosBlock field to given value.

### HasPosBlock

`func (o *BlockTemplateRequestModel) HasPosBlock() bool`

HasPosBlock returns a boolean if a field has been set.

### GetIgnorePowTsCheck

`func (o *BlockTemplateRequestModel) GetIgnorePowTsCheck() bool`

GetIgnorePowTsCheck returns the IgnorePowTsCheck field if non-nil, zero value otherwise.

### GetIgnorePowTsCheckOk

`func (o *BlockTemplateRequestModel) GetIgnorePowTsCheckOk() (*bool, bool)`

GetIgnorePowTsCheckOk returns a tuple with the IgnorePowTsCheck field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetIgnorePowTsCheck

`func (o *BlockTemplateRequestModel) SetIgnorePowTsCheck(v bool)`

SetIgnorePowTsCheck sets IgnorePowTsCheck field to given value.

### HasIgnorePowTsCheck

`func (o *BlockTemplateRequestModel) HasIgnorePowTsCheck() bool`

HasIgnorePowTsCheck returns a boolean if a field has been set.

### GetPe

`func (o *BlockTemplateRequestModel) GetPe() PosEntryModel`

GetPe returns the Pe field if non-nil, zero value otherwise.

### GetPeOk

`func (o *BlockTemplateRequestModel) GetPeOk() (*PosEntryModel, bool)`

GetPeOk returns a tuple with the Pe field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetPe

`func (o *BlockTemplateRequestModel) SetPe(v PosEntryModel)`

SetPe sets Pe field to given value.

### HasPe

`func (o *BlockTemplateRequestModel) HasPe() bool`

HasPe returns a boolean if a field has been set.

### GetExplicitTxs

`func (o *BlockTemplateRequestModel) GetExplicitTxs() []string`

GetExplicitTxs returns the ExplicitTxs field if non-nil, zero value otherwise.

### GetExplicitTxsOk

`func (o *BlockTemplateRequestModel) GetExplicitTxsOk() (*[]string, bool)`

GetExplicitTxsOk returns a tuple with the ExplicitTxs field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetExplicitTxs

`func (o *BlockTemplateRequestModel) SetExplicitTxs(v []string)`

SetExplicitTxs sets ExplicitTxs field to given value.

### HasExplicitTxs

`func (o *BlockTemplateRequestModel) HasExplicitTxs() bool`

HasExplicitTxs returns a boolean if a field has been set.


[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


