# BlockTemplateModel

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**BlocktemplateBlob** | Pointer to **string** |  | [optional] 
**Difficulty** | Pointer to **string** |  | [optional] 
**Height** | Pointer to **int32** |  | [optional] 
**MinerTxTgc** | Pointer to [**TxGenerationContextModel**](TxGenerationContextModel.md) |  | [optional] 
**BlockRewardWithoutFee** | Pointer to **int32** |  | [optional] 
**BlockReward** | Pointer to **int32** |  | [optional] 
**TxsFee** | Pointer to **int32** |  | [optional] 
**PrevHash** | Pointer to **string** |  | [optional] 
**Seed** | Pointer to **string** |  | [optional] 

## Methods

### NewBlockTemplateModel

`func NewBlockTemplateModel() *BlockTemplateModel`

NewBlockTemplateModel instantiates a new BlockTemplateModel object
This constructor will assign default values to properties that have it defined,
and makes sure properties required by API are set, but the set of arguments
will change when the set of required properties is changed

### NewBlockTemplateModelWithDefaults

`func NewBlockTemplateModelWithDefaults() *BlockTemplateModel`

NewBlockTemplateModelWithDefaults instantiates a new BlockTemplateModel object
This constructor will only assign default values to properties that have it defined,
but it doesn't guarantee that properties required by API are set

### GetBlocktemplateBlob

`func (o *BlockTemplateModel) GetBlocktemplateBlob() string`

GetBlocktemplateBlob returns the BlocktemplateBlob field if non-nil, zero value otherwise.

### GetBlocktemplateBlobOk

`func (o *BlockTemplateModel) GetBlocktemplateBlobOk() (*string, bool)`

GetBlocktemplateBlobOk returns a tuple with the BlocktemplateBlob field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetBlocktemplateBlob

`func (o *BlockTemplateModel) SetBlocktemplateBlob(v string)`

SetBlocktemplateBlob sets BlocktemplateBlob field to given value.

### HasBlocktemplateBlob

`func (o *BlockTemplateModel) HasBlocktemplateBlob() bool`

HasBlocktemplateBlob returns a boolean if a field has been set.

### GetDifficulty

`func (o *BlockTemplateModel) GetDifficulty() string`

GetDifficulty returns the Difficulty field if non-nil, zero value otherwise.

### GetDifficultyOk

`func (o *BlockTemplateModel) GetDifficultyOk() (*string, bool)`

GetDifficultyOk returns a tuple with the Difficulty field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetDifficulty

`func (o *BlockTemplateModel) SetDifficulty(v string)`

SetDifficulty sets Difficulty field to given value.

### HasDifficulty

`func (o *BlockTemplateModel) HasDifficulty() bool`

HasDifficulty returns a boolean if a field has been set.

### GetHeight

`func (o *BlockTemplateModel) GetHeight() int32`

GetHeight returns the Height field if non-nil, zero value otherwise.

### GetHeightOk

`func (o *BlockTemplateModel) GetHeightOk() (*int32, bool)`

GetHeightOk returns a tuple with the Height field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetHeight

`func (o *BlockTemplateModel) SetHeight(v int32)`

SetHeight sets Height field to given value.

### HasHeight

`func (o *BlockTemplateModel) HasHeight() bool`

HasHeight returns a boolean if a field has been set.

### GetMinerTxTgc

`func (o *BlockTemplateModel) GetMinerTxTgc() TxGenerationContextModel`

GetMinerTxTgc returns the MinerTxTgc field if non-nil, zero value otherwise.

### GetMinerTxTgcOk

`func (o *BlockTemplateModel) GetMinerTxTgcOk() (*TxGenerationContextModel, bool)`

GetMinerTxTgcOk returns a tuple with the MinerTxTgc field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetMinerTxTgc

`func (o *BlockTemplateModel) SetMinerTxTgc(v TxGenerationContextModel)`

SetMinerTxTgc sets MinerTxTgc field to given value.

### HasMinerTxTgc

`func (o *BlockTemplateModel) HasMinerTxTgc() bool`

HasMinerTxTgc returns a boolean if a field has been set.

### GetBlockRewardWithoutFee

`func (o *BlockTemplateModel) GetBlockRewardWithoutFee() int32`

GetBlockRewardWithoutFee returns the BlockRewardWithoutFee field if non-nil, zero value otherwise.

### GetBlockRewardWithoutFeeOk

`func (o *BlockTemplateModel) GetBlockRewardWithoutFeeOk() (*int32, bool)`

GetBlockRewardWithoutFeeOk returns a tuple with the BlockRewardWithoutFee field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetBlockRewardWithoutFee

`func (o *BlockTemplateModel) SetBlockRewardWithoutFee(v int32)`

SetBlockRewardWithoutFee sets BlockRewardWithoutFee field to given value.

### HasBlockRewardWithoutFee

`func (o *BlockTemplateModel) HasBlockRewardWithoutFee() bool`

HasBlockRewardWithoutFee returns a boolean if a field has been set.

### GetBlockReward

`func (o *BlockTemplateModel) GetBlockReward() int32`

GetBlockReward returns the BlockReward field if non-nil, zero value otherwise.

### GetBlockRewardOk

`func (o *BlockTemplateModel) GetBlockRewardOk() (*int32, bool)`

GetBlockRewardOk returns a tuple with the BlockReward field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetBlockReward

`func (o *BlockTemplateModel) SetBlockReward(v int32)`

SetBlockReward sets BlockReward field to given value.

### HasBlockReward

`func (o *BlockTemplateModel) HasBlockReward() bool`

HasBlockReward returns a boolean if a field has been set.

### GetTxsFee

`func (o *BlockTemplateModel) GetTxsFee() int32`

GetTxsFee returns the TxsFee field if non-nil, zero value otherwise.

### GetTxsFeeOk

`func (o *BlockTemplateModel) GetTxsFeeOk() (*int32, bool)`

GetTxsFeeOk returns a tuple with the TxsFee field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTxsFee

`func (o *BlockTemplateModel) SetTxsFee(v int32)`

SetTxsFee sets TxsFee field to given value.

### HasTxsFee

`func (o *BlockTemplateModel) HasTxsFee() bool`

HasTxsFee returns a boolean if a field has been set.

### GetPrevHash

`func (o *BlockTemplateModel) GetPrevHash() string`

GetPrevHash returns the PrevHash field if non-nil, zero value otherwise.

### GetPrevHashOk

`func (o *BlockTemplateModel) GetPrevHashOk() (*string, bool)`

GetPrevHashOk returns a tuple with the PrevHash field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetPrevHash

`func (o *BlockTemplateModel) SetPrevHash(v string)`

SetPrevHash sets PrevHash field to given value.

### HasPrevHash

`func (o *BlockTemplateModel) HasPrevHash() bool`

HasPrevHash returns a boolean if a field has been set.

### GetSeed

`func (o *BlockTemplateModel) GetSeed() string`

GetSeed returns the Seed field if non-nil, zero value otherwise.

### GetSeedOk

`func (o *BlockTemplateModel) GetSeedOk() (*string, bool)`

GetSeedOk returns a tuple with the Seed field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetSeed

`func (o *BlockTemplateModel) SetSeed(v string)`

SetSeed sets Seed field to given value.

### HasSeed

`func (o *BlockTemplateModel) HasSeed() bool`

HasSeed returns a boolean if a field has been set.


[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


