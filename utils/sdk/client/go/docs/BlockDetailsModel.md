# BlockDetailsModel

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**ActualTimestamp** | Pointer to **int32** |  | [optional] 
**AlreadyGeneratedCoins** | Pointer to **string** |  | [optional] 
**BaseReward** | Pointer to **int32** |  | [optional] 
**Blob** | Pointer to **string** |  | [optional] 
**BlockCumulativeSize** | Pointer to **int32** |  | [optional] 
**BlockTselfSize** | Pointer to **int32** |  | [optional] 
**CumulativeDiffAdjusted** | Pointer to **string** |  | [optional] 
**CumulativeDiffPrecise** | Pointer to **string** |  | [optional] 
**Difficulty** | Pointer to **string** |  | [optional] 
**EffectiveFeeMedian** | Pointer to **int32** |  | [optional] 
**Height** | Pointer to **int32** |  | [optional] 
**Id** | Pointer to **string** |  | [optional] 
**IsOrphan** | Pointer to **bool** |  | [optional] 
**MinerTextInfo** | Pointer to **string** |  | [optional] 
**ObjectInJson** | Pointer to **string** |  | [optional] 
**Penalty** | Pointer to **int32** |  | [optional] 
**PowSeed** | Pointer to **string** |  | [optional] 
**PrevId** | Pointer to **string** |  | [optional] 
**SummaryReward** | Pointer to **int32** |  | [optional] 
**ThisBlockFeeMedian** | Pointer to **int32** |  | [optional] 
**Timestamp** | Pointer to **int32** |  | [optional] 
**TotalFee** | Pointer to **int32** |  | [optional] 
**TotalTxsSize** | Pointer to **int32** |  | [optional] 
**TransactionsDetails** | Pointer to [**[]TransactionDetailsModel**](TransactionDetailsModel.md) |  | [optional] 
**Type** | Pointer to **int32** |  | [optional] 

## Methods

### NewBlockDetailsModel

`func NewBlockDetailsModel() *BlockDetailsModel`

NewBlockDetailsModel instantiates a new BlockDetailsModel object
This constructor will assign default values to properties that have it defined,
and makes sure properties required by API are set, but the set of arguments
will change when the set of required properties is changed

### NewBlockDetailsModelWithDefaults

`func NewBlockDetailsModelWithDefaults() *BlockDetailsModel`

NewBlockDetailsModelWithDefaults instantiates a new BlockDetailsModel object
This constructor will only assign default values to properties that have it defined,
but it doesn't guarantee that properties required by API are set

### GetActualTimestamp

`func (o *BlockDetailsModel) GetActualTimestamp() int32`

GetActualTimestamp returns the ActualTimestamp field if non-nil, zero value otherwise.

### GetActualTimestampOk

`func (o *BlockDetailsModel) GetActualTimestampOk() (*int32, bool)`

GetActualTimestampOk returns a tuple with the ActualTimestamp field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetActualTimestamp

`func (o *BlockDetailsModel) SetActualTimestamp(v int32)`

SetActualTimestamp sets ActualTimestamp field to given value.

### HasActualTimestamp

`func (o *BlockDetailsModel) HasActualTimestamp() bool`

HasActualTimestamp returns a boolean if a field has been set.

### GetAlreadyGeneratedCoins

`func (o *BlockDetailsModel) GetAlreadyGeneratedCoins() string`

GetAlreadyGeneratedCoins returns the AlreadyGeneratedCoins field if non-nil, zero value otherwise.

### GetAlreadyGeneratedCoinsOk

`func (o *BlockDetailsModel) GetAlreadyGeneratedCoinsOk() (*string, bool)`

GetAlreadyGeneratedCoinsOk returns a tuple with the AlreadyGeneratedCoins field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetAlreadyGeneratedCoins

`func (o *BlockDetailsModel) SetAlreadyGeneratedCoins(v string)`

SetAlreadyGeneratedCoins sets AlreadyGeneratedCoins field to given value.

### HasAlreadyGeneratedCoins

`func (o *BlockDetailsModel) HasAlreadyGeneratedCoins() bool`

HasAlreadyGeneratedCoins returns a boolean if a field has been set.

### GetBaseReward

`func (o *BlockDetailsModel) GetBaseReward() int32`

GetBaseReward returns the BaseReward field if non-nil, zero value otherwise.

### GetBaseRewardOk

`func (o *BlockDetailsModel) GetBaseRewardOk() (*int32, bool)`

GetBaseRewardOk returns a tuple with the BaseReward field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetBaseReward

`func (o *BlockDetailsModel) SetBaseReward(v int32)`

SetBaseReward sets BaseReward field to given value.

### HasBaseReward

`func (o *BlockDetailsModel) HasBaseReward() bool`

HasBaseReward returns a boolean if a field has been set.

### GetBlob

`func (o *BlockDetailsModel) GetBlob() string`

GetBlob returns the Blob field if non-nil, zero value otherwise.

### GetBlobOk

`func (o *BlockDetailsModel) GetBlobOk() (*string, bool)`

GetBlobOk returns a tuple with the Blob field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetBlob

`func (o *BlockDetailsModel) SetBlob(v string)`

SetBlob sets Blob field to given value.

### HasBlob

`func (o *BlockDetailsModel) HasBlob() bool`

HasBlob returns a boolean if a field has been set.

### GetBlockCumulativeSize

`func (o *BlockDetailsModel) GetBlockCumulativeSize() int32`

GetBlockCumulativeSize returns the BlockCumulativeSize field if non-nil, zero value otherwise.

### GetBlockCumulativeSizeOk

`func (o *BlockDetailsModel) GetBlockCumulativeSizeOk() (*int32, bool)`

GetBlockCumulativeSizeOk returns a tuple with the BlockCumulativeSize field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetBlockCumulativeSize

`func (o *BlockDetailsModel) SetBlockCumulativeSize(v int32)`

SetBlockCumulativeSize sets BlockCumulativeSize field to given value.

### HasBlockCumulativeSize

`func (o *BlockDetailsModel) HasBlockCumulativeSize() bool`

HasBlockCumulativeSize returns a boolean if a field has been set.

### GetBlockTselfSize

`func (o *BlockDetailsModel) GetBlockTselfSize() int32`

GetBlockTselfSize returns the BlockTselfSize field if non-nil, zero value otherwise.

### GetBlockTselfSizeOk

`func (o *BlockDetailsModel) GetBlockTselfSizeOk() (*int32, bool)`

GetBlockTselfSizeOk returns a tuple with the BlockTselfSize field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetBlockTselfSize

`func (o *BlockDetailsModel) SetBlockTselfSize(v int32)`

SetBlockTselfSize sets BlockTselfSize field to given value.

### HasBlockTselfSize

`func (o *BlockDetailsModel) HasBlockTselfSize() bool`

HasBlockTselfSize returns a boolean if a field has been set.

### GetCumulativeDiffAdjusted

`func (o *BlockDetailsModel) GetCumulativeDiffAdjusted() string`

GetCumulativeDiffAdjusted returns the CumulativeDiffAdjusted field if non-nil, zero value otherwise.

### GetCumulativeDiffAdjustedOk

`func (o *BlockDetailsModel) GetCumulativeDiffAdjustedOk() (*string, bool)`

GetCumulativeDiffAdjustedOk returns a tuple with the CumulativeDiffAdjusted field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetCumulativeDiffAdjusted

`func (o *BlockDetailsModel) SetCumulativeDiffAdjusted(v string)`

SetCumulativeDiffAdjusted sets CumulativeDiffAdjusted field to given value.

### HasCumulativeDiffAdjusted

`func (o *BlockDetailsModel) HasCumulativeDiffAdjusted() bool`

HasCumulativeDiffAdjusted returns a boolean if a field has been set.

### GetCumulativeDiffPrecise

`func (o *BlockDetailsModel) GetCumulativeDiffPrecise() string`

GetCumulativeDiffPrecise returns the CumulativeDiffPrecise field if non-nil, zero value otherwise.

### GetCumulativeDiffPreciseOk

`func (o *BlockDetailsModel) GetCumulativeDiffPreciseOk() (*string, bool)`

GetCumulativeDiffPreciseOk returns a tuple with the CumulativeDiffPrecise field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetCumulativeDiffPrecise

`func (o *BlockDetailsModel) SetCumulativeDiffPrecise(v string)`

SetCumulativeDiffPrecise sets CumulativeDiffPrecise field to given value.

### HasCumulativeDiffPrecise

`func (o *BlockDetailsModel) HasCumulativeDiffPrecise() bool`

HasCumulativeDiffPrecise returns a boolean if a field has been set.

### GetDifficulty

`func (o *BlockDetailsModel) GetDifficulty() string`

GetDifficulty returns the Difficulty field if non-nil, zero value otherwise.

### GetDifficultyOk

`func (o *BlockDetailsModel) GetDifficultyOk() (*string, bool)`

GetDifficultyOk returns a tuple with the Difficulty field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetDifficulty

`func (o *BlockDetailsModel) SetDifficulty(v string)`

SetDifficulty sets Difficulty field to given value.

### HasDifficulty

`func (o *BlockDetailsModel) HasDifficulty() bool`

HasDifficulty returns a boolean if a field has been set.

### GetEffectiveFeeMedian

`func (o *BlockDetailsModel) GetEffectiveFeeMedian() int32`

GetEffectiveFeeMedian returns the EffectiveFeeMedian field if non-nil, zero value otherwise.

### GetEffectiveFeeMedianOk

`func (o *BlockDetailsModel) GetEffectiveFeeMedianOk() (*int32, bool)`

GetEffectiveFeeMedianOk returns a tuple with the EffectiveFeeMedian field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetEffectiveFeeMedian

`func (o *BlockDetailsModel) SetEffectiveFeeMedian(v int32)`

SetEffectiveFeeMedian sets EffectiveFeeMedian field to given value.

### HasEffectiveFeeMedian

`func (o *BlockDetailsModel) HasEffectiveFeeMedian() bool`

HasEffectiveFeeMedian returns a boolean if a field has been set.

### GetHeight

`func (o *BlockDetailsModel) GetHeight() int32`

GetHeight returns the Height field if non-nil, zero value otherwise.

### GetHeightOk

`func (o *BlockDetailsModel) GetHeightOk() (*int32, bool)`

GetHeightOk returns a tuple with the Height field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetHeight

`func (o *BlockDetailsModel) SetHeight(v int32)`

SetHeight sets Height field to given value.

### HasHeight

`func (o *BlockDetailsModel) HasHeight() bool`

HasHeight returns a boolean if a field has been set.

### GetId

`func (o *BlockDetailsModel) GetId() string`

GetId returns the Id field if non-nil, zero value otherwise.

### GetIdOk

`func (o *BlockDetailsModel) GetIdOk() (*string, bool)`

GetIdOk returns a tuple with the Id field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetId

`func (o *BlockDetailsModel) SetId(v string)`

SetId sets Id field to given value.

### HasId

`func (o *BlockDetailsModel) HasId() bool`

HasId returns a boolean if a field has been set.

### GetIsOrphan

`func (o *BlockDetailsModel) GetIsOrphan() bool`

GetIsOrphan returns the IsOrphan field if non-nil, zero value otherwise.

### GetIsOrphanOk

`func (o *BlockDetailsModel) GetIsOrphanOk() (*bool, bool)`

GetIsOrphanOk returns a tuple with the IsOrphan field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetIsOrphan

`func (o *BlockDetailsModel) SetIsOrphan(v bool)`

SetIsOrphan sets IsOrphan field to given value.

### HasIsOrphan

`func (o *BlockDetailsModel) HasIsOrphan() bool`

HasIsOrphan returns a boolean if a field has been set.

### GetMinerTextInfo

`func (o *BlockDetailsModel) GetMinerTextInfo() string`

GetMinerTextInfo returns the MinerTextInfo field if non-nil, zero value otherwise.

### GetMinerTextInfoOk

`func (o *BlockDetailsModel) GetMinerTextInfoOk() (*string, bool)`

GetMinerTextInfoOk returns a tuple with the MinerTextInfo field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetMinerTextInfo

`func (o *BlockDetailsModel) SetMinerTextInfo(v string)`

SetMinerTextInfo sets MinerTextInfo field to given value.

### HasMinerTextInfo

`func (o *BlockDetailsModel) HasMinerTextInfo() bool`

HasMinerTextInfo returns a boolean if a field has been set.

### GetObjectInJson

`func (o *BlockDetailsModel) GetObjectInJson() string`

GetObjectInJson returns the ObjectInJson field if non-nil, zero value otherwise.

### GetObjectInJsonOk

`func (o *BlockDetailsModel) GetObjectInJsonOk() (*string, bool)`

GetObjectInJsonOk returns a tuple with the ObjectInJson field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetObjectInJson

`func (o *BlockDetailsModel) SetObjectInJson(v string)`

SetObjectInJson sets ObjectInJson field to given value.

### HasObjectInJson

`func (o *BlockDetailsModel) HasObjectInJson() bool`

HasObjectInJson returns a boolean if a field has been set.

### GetPenalty

`func (o *BlockDetailsModel) GetPenalty() int32`

GetPenalty returns the Penalty field if non-nil, zero value otherwise.

### GetPenaltyOk

`func (o *BlockDetailsModel) GetPenaltyOk() (*int32, bool)`

GetPenaltyOk returns a tuple with the Penalty field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetPenalty

`func (o *BlockDetailsModel) SetPenalty(v int32)`

SetPenalty sets Penalty field to given value.

### HasPenalty

`func (o *BlockDetailsModel) HasPenalty() bool`

HasPenalty returns a boolean if a field has been set.

### GetPowSeed

`func (o *BlockDetailsModel) GetPowSeed() string`

GetPowSeed returns the PowSeed field if non-nil, zero value otherwise.

### GetPowSeedOk

`func (o *BlockDetailsModel) GetPowSeedOk() (*string, bool)`

GetPowSeedOk returns a tuple with the PowSeed field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetPowSeed

`func (o *BlockDetailsModel) SetPowSeed(v string)`

SetPowSeed sets PowSeed field to given value.

### HasPowSeed

`func (o *BlockDetailsModel) HasPowSeed() bool`

HasPowSeed returns a boolean if a field has been set.

### GetPrevId

`func (o *BlockDetailsModel) GetPrevId() string`

GetPrevId returns the PrevId field if non-nil, zero value otherwise.

### GetPrevIdOk

`func (o *BlockDetailsModel) GetPrevIdOk() (*string, bool)`

GetPrevIdOk returns a tuple with the PrevId field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetPrevId

`func (o *BlockDetailsModel) SetPrevId(v string)`

SetPrevId sets PrevId field to given value.

### HasPrevId

`func (o *BlockDetailsModel) HasPrevId() bool`

HasPrevId returns a boolean if a field has been set.

### GetSummaryReward

`func (o *BlockDetailsModel) GetSummaryReward() int32`

GetSummaryReward returns the SummaryReward field if non-nil, zero value otherwise.

### GetSummaryRewardOk

`func (o *BlockDetailsModel) GetSummaryRewardOk() (*int32, bool)`

GetSummaryRewardOk returns a tuple with the SummaryReward field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetSummaryReward

`func (o *BlockDetailsModel) SetSummaryReward(v int32)`

SetSummaryReward sets SummaryReward field to given value.

### HasSummaryReward

`func (o *BlockDetailsModel) HasSummaryReward() bool`

HasSummaryReward returns a boolean if a field has been set.

### GetThisBlockFeeMedian

`func (o *BlockDetailsModel) GetThisBlockFeeMedian() int32`

GetThisBlockFeeMedian returns the ThisBlockFeeMedian field if non-nil, zero value otherwise.

### GetThisBlockFeeMedianOk

`func (o *BlockDetailsModel) GetThisBlockFeeMedianOk() (*int32, bool)`

GetThisBlockFeeMedianOk returns a tuple with the ThisBlockFeeMedian field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetThisBlockFeeMedian

`func (o *BlockDetailsModel) SetThisBlockFeeMedian(v int32)`

SetThisBlockFeeMedian sets ThisBlockFeeMedian field to given value.

### HasThisBlockFeeMedian

`func (o *BlockDetailsModel) HasThisBlockFeeMedian() bool`

HasThisBlockFeeMedian returns a boolean if a field has been set.

### GetTimestamp

`func (o *BlockDetailsModel) GetTimestamp() int32`

GetTimestamp returns the Timestamp field if non-nil, zero value otherwise.

### GetTimestampOk

`func (o *BlockDetailsModel) GetTimestampOk() (*int32, bool)`

GetTimestampOk returns a tuple with the Timestamp field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTimestamp

`func (o *BlockDetailsModel) SetTimestamp(v int32)`

SetTimestamp sets Timestamp field to given value.

### HasTimestamp

`func (o *BlockDetailsModel) HasTimestamp() bool`

HasTimestamp returns a boolean if a field has been set.

### GetTotalFee

`func (o *BlockDetailsModel) GetTotalFee() int32`

GetTotalFee returns the TotalFee field if non-nil, zero value otherwise.

### GetTotalFeeOk

`func (o *BlockDetailsModel) GetTotalFeeOk() (*int32, bool)`

GetTotalFeeOk returns a tuple with the TotalFee field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTotalFee

`func (o *BlockDetailsModel) SetTotalFee(v int32)`

SetTotalFee sets TotalFee field to given value.

### HasTotalFee

`func (o *BlockDetailsModel) HasTotalFee() bool`

HasTotalFee returns a boolean if a field has been set.

### GetTotalTxsSize

`func (o *BlockDetailsModel) GetTotalTxsSize() int32`

GetTotalTxsSize returns the TotalTxsSize field if non-nil, zero value otherwise.

### GetTotalTxsSizeOk

`func (o *BlockDetailsModel) GetTotalTxsSizeOk() (*int32, bool)`

GetTotalTxsSizeOk returns a tuple with the TotalTxsSize field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTotalTxsSize

`func (o *BlockDetailsModel) SetTotalTxsSize(v int32)`

SetTotalTxsSize sets TotalTxsSize field to given value.

### HasTotalTxsSize

`func (o *BlockDetailsModel) HasTotalTxsSize() bool`

HasTotalTxsSize returns a boolean if a field has been set.

### GetTransactionsDetails

`func (o *BlockDetailsModel) GetTransactionsDetails() []TransactionDetailsModel`

GetTransactionsDetails returns the TransactionsDetails field if non-nil, zero value otherwise.

### GetTransactionsDetailsOk

`func (o *BlockDetailsModel) GetTransactionsDetailsOk() (*[]TransactionDetailsModel, bool)`

GetTransactionsDetailsOk returns a tuple with the TransactionsDetails field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTransactionsDetails

`func (o *BlockDetailsModel) SetTransactionsDetails(v []TransactionDetailsModel)`

SetTransactionsDetails sets TransactionsDetails field to given value.

### HasTransactionsDetails

`func (o *BlockDetailsModel) HasTransactionsDetails() bool`

HasTransactionsDetails returns a boolean if a field has been set.

### GetType

`func (o *BlockDetailsModel) GetType() int32`

GetType returns the Type field if non-nil, zero value otherwise.

### GetTypeOk

`func (o *BlockDetailsModel) GetTypeOk() (*int32, bool)`

GetTypeOk returns a tuple with the Type field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetType

`func (o *BlockDetailsModel) SetType(v int32)`

SetType sets Type field to given value.

### HasType

`func (o *BlockDetailsModel) HasType() bool`

HasType returns a boolean if a field has been set.


[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


