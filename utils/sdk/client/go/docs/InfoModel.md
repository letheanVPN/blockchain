# InfoModel

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**Height** | Pointer to **int32** |  | [optional] 
**TxCount** | Pointer to **int32** |  | [optional] 
**TxPoolSize** | Pointer to **int32** |  | [optional] 
**AltBlocksCount** | Pointer to **int32** |  | [optional] 
**OutgoingConnectionsCount** | Pointer to **int32** |  | [optional] 
**IncomingConnectionsCount** | Pointer to **int32** |  | [optional] 
**SynchronizedConnectionsCount** | Pointer to **int32** |  | [optional] 
**WhitePeerlistSize** | Pointer to **int32** |  | [optional] 
**GreyPeerlistSize** | Pointer to **int32** |  | [optional] 
**CurrentBlocksMedian** | Pointer to **int32** |  | [optional] 
**AliasCount** | Pointer to **int32** |  | [optional] 
**CurrentMaxAllowedBlockSize** | Pointer to **int32** |  | [optional] 
**DaemonNetworkState** | Pointer to **string** |  | [optional] 
**SynchronizationStartHeight** | Pointer to **int32** |  | [optional] 
**MaxNetSeenHeight** | Pointer to **int32** |  | [optional] 
**Mi** | Pointer to [**MaintainersInfoModel**](MaintainersInfoModel.md) |  | [optional] 
**PosAllowed** | Pointer to **bool** |  | [optional] 
**PosDifficulty** | Pointer to **string** |  | [optional] 
**PowDifficulty** | Pointer to **int32** |  | [optional] 
**DefaultFee** | Pointer to **int32** |  | [optional] 
**MinimumFee** | Pointer to **int32** |  | [optional] 
**IsHardforkActive** | Pointer to **[]bool** |  | [optional] 
**NetTimeDeltaMedian** | Pointer to **int64** |  | [optional] 
**CurrentNetworkHashrate50** | Pointer to **int32** |  | [optional] 
**CurrentNetworkHashrate350** | Pointer to **int32** |  | [optional] 
**SecondsFor10Blocks** | Pointer to **int32** |  | [optional] 
**SecondsFor30Blocks** | Pointer to **int32** |  | [optional] 
**TransactionsCntPerDay** | Pointer to **[]int32** |  | [optional] 
**TransactionsVolumePerDay** | Pointer to **[]int32** |  | [optional] 
**LastPosTimestamp** | Pointer to **int32** |  | [optional] 
**LastPowTimestamp** | Pointer to **int32** |  | [optional] 
**TotalCoins** | Pointer to **string** |  | [optional] 
**LastBlockSize** | Pointer to **int32** |  | [optional] 
**TxCountInLastBlock** | Pointer to **int32** |  | [optional] 
**PosSequenceFactor** | Pointer to **float64** |  | [optional] 
**PowSequenceFactor** | Pointer to **float64** |  | [optional] 
**BlockReward** | Pointer to **int32** |  | [optional] 
**LastBlockTotalReward** | Pointer to **int32** |  | [optional] 
**PosDiffTotalCoinsRate** | Pointer to **int32** |  | [optional] 
**LastBlockTimestamp** | Pointer to **int32** |  | [optional] 
**LastBlockHash** | Pointer to **string** |  | [optional] 
**PosBlockTsShiftVsActual** | Pointer to **int64** |  | [optional] 
**OutsStat** | Pointer to **map[string]int32** |  | [optional] 
**PerformanceData** | Pointer to [**PerformanceModel**](PerformanceModel.md) |  | [optional] 
**OffersCount** | Pointer to **int32** |  | [optional] 
**ExpirationMedianTimestamp** | Pointer to **int32** |  | [optional] 

## Methods

### NewInfoModel

`func NewInfoModel() *InfoModel`

NewInfoModel instantiates a new InfoModel object
This constructor will assign default values to properties that have it defined,
and makes sure properties required by API are set, but the set of arguments
will change when the set of required properties is changed

### NewInfoModelWithDefaults

`func NewInfoModelWithDefaults() *InfoModel`

NewInfoModelWithDefaults instantiates a new InfoModel object
This constructor will only assign default values to properties that have it defined,
but it doesn't guarantee that properties required by API are set

### GetHeight

`func (o *InfoModel) GetHeight() int32`

GetHeight returns the Height field if non-nil, zero value otherwise.

### GetHeightOk

`func (o *InfoModel) GetHeightOk() (*int32, bool)`

GetHeightOk returns a tuple with the Height field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetHeight

`func (o *InfoModel) SetHeight(v int32)`

SetHeight sets Height field to given value.

### HasHeight

`func (o *InfoModel) HasHeight() bool`

HasHeight returns a boolean if a field has been set.

### GetTxCount

`func (o *InfoModel) GetTxCount() int32`

GetTxCount returns the TxCount field if non-nil, zero value otherwise.

### GetTxCountOk

`func (o *InfoModel) GetTxCountOk() (*int32, bool)`

GetTxCountOk returns a tuple with the TxCount field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTxCount

`func (o *InfoModel) SetTxCount(v int32)`

SetTxCount sets TxCount field to given value.

### HasTxCount

`func (o *InfoModel) HasTxCount() bool`

HasTxCount returns a boolean if a field has been set.

### GetTxPoolSize

`func (o *InfoModel) GetTxPoolSize() int32`

GetTxPoolSize returns the TxPoolSize field if non-nil, zero value otherwise.

### GetTxPoolSizeOk

`func (o *InfoModel) GetTxPoolSizeOk() (*int32, bool)`

GetTxPoolSizeOk returns a tuple with the TxPoolSize field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTxPoolSize

`func (o *InfoModel) SetTxPoolSize(v int32)`

SetTxPoolSize sets TxPoolSize field to given value.

### HasTxPoolSize

`func (o *InfoModel) HasTxPoolSize() bool`

HasTxPoolSize returns a boolean if a field has been set.

### GetAltBlocksCount

`func (o *InfoModel) GetAltBlocksCount() int32`

GetAltBlocksCount returns the AltBlocksCount field if non-nil, zero value otherwise.

### GetAltBlocksCountOk

`func (o *InfoModel) GetAltBlocksCountOk() (*int32, bool)`

GetAltBlocksCountOk returns a tuple with the AltBlocksCount field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetAltBlocksCount

`func (o *InfoModel) SetAltBlocksCount(v int32)`

SetAltBlocksCount sets AltBlocksCount field to given value.

### HasAltBlocksCount

`func (o *InfoModel) HasAltBlocksCount() bool`

HasAltBlocksCount returns a boolean if a field has been set.

### GetOutgoingConnectionsCount

`func (o *InfoModel) GetOutgoingConnectionsCount() int32`

GetOutgoingConnectionsCount returns the OutgoingConnectionsCount field if non-nil, zero value otherwise.

### GetOutgoingConnectionsCountOk

`func (o *InfoModel) GetOutgoingConnectionsCountOk() (*int32, bool)`

GetOutgoingConnectionsCountOk returns a tuple with the OutgoingConnectionsCount field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetOutgoingConnectionsCount

`func (o *InfoModel) SetOutgoingConnectionsCount(v int32)`

SetOutgoingConnectionsCount sets OutgoingConnectionsCount field to given value.

### HasOutgoingConnectionsCount

`func (o *InfoModel) HasOutgoingConnectionsCount() bool`

HasOutgoingConnectionsCount returns a boolean if a field has been set.

### GetIncomingConnectionsCount

`func (o *InfoModel) GetIncomingConnectionsCount() int32`

GetIncomingConnectionsCount returns the IncomingConnectionsCount field if non-nil, zero value otherwise.

### GetIncomingConnectionsCountOk

`func (o *InfoModel) GetIncomingConnectionsCountOk() (*int32, bool)`

GetIncomingConnectionsCountOk returns a tuple with the IncomingConnectionsCount field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetIncomingConnectionsCount

`func (o *InfoModel) SetIncomingConnectionsCount(v int32)`

SetIncomingConnectionsCount sets IncomingConnectionsCount field to given value.

### HasIncomingConnectionsCount

`func (o *InfoModel) HasIncomingConnectionsCount() bool`

HasIncomingConnectionsCount returns a boolean if a field has been set.

### GetSynchronizedConnectionsCount

`func (o *InfoModel) GetSynchronizedConnectionsCount() int32`

GetSynchronizedConnectionsCount returns the SynchronizedConnectionsCount field if non-nil, zero value otherwise.

### GetSynchronizedConnectionsCountOk

`func (o *InfoModel) GetSynchronizedConnectionsCountOk() (*int32, bool)`

GetSynchronizedConnectionsCountOk returns a tuple with the SynchronizedConnectionsCount field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetSynchronizedConnectionsCount

`func (o *InfoModel) SetSynchronizedConnectionsCount(v int32)`

SetSynchronizedConnectionsCount sets SynchronizedConnectionsCount field to given value.

### HasSynchronizedConnectionsCount

`func (o *InfoModel) HasSynchronizedConnectionsCount() bool`

HasSynchronizedConnectionsCount returns a boolean if a field has been set.

### GetWhitePeerlistSize

`func (o *InfoModel) GetWhitePeerlistSize() int32`

GetWhitePeerlistSize returns the WhitePeerlistSize field if non-nil, zero value otherwise.

### GetWhitePeerlistSizeOk

`func (o *InfoModel) GetWhitePeerlistSizeOk() (*int32, bool)`

GetWhitePeerlistSizeOk returns a tuple with the WhitePeerlistSize field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetWhitePeerlistSize

`func (o *InfoModel) SetWhitePeerlistSize(v int32)`

SetWhitePeerlistSize sets WhitePeerlistSize field to given value.

### HasWhitePeerlistSize

`func (o *InfoModel) HasWhitePeerlistSize() bool`

HasWhitePeerlistSize returns a boolean if a field has been set.

### GetGreyPeerlistSize

`func (o *InfoModel) GetGreyPeerlistSize() int32`

GetGreyPeerlistSize returns the GreyPeerlistSize field if non-nil, zero value otherwise.

### GetGreyPeerlistSizeOk

`func (o *InfoModel) GetGreyPeerlistSizeOk() (*int32, bool)`

GetGreyPeerlistSizeOk returns a tuple with the GreyPeerlistSize field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetGreyPeerlistSize

`func (o *InfoModel) SetGreyPeerlistSize(v int32)`

SetGreyPeerlistSize sets GreyPeerlistSize field to given value.

### HasGreyPeerlistSize

`func (o *InfoModel) HasGreyPeerlistSize() bool`

HasGreyPeerlistSize returns a boolean if a field has been set.

### GetCurrentBlocksMedian

`func (o *InfoModel) GetCurrentBlocksMedian() int32`

GetCurrentBlocksMedian returns the CurrentBlocksMedian field if non-nil, zero value otherwise.

### GetCurrentBlocksMedianOk

`func (o *InfoModel) GetCurrentBlocksMedianOk() (*int32, bool)`

GetCurrentBlocksMedianOk returns a tuple with the CurrentBlocksMedian field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetCurrentBlocksMedian

`func (o *InfoModel) SetCurrentBlocksMedian(v int32)`

SetCurrentBlocksMedian sets CurrentBlocksMedian field to given value.

### HasCurrentBlocksMedian

`func (o *InfoModel) HasCurrentBlocksMedian() bool`

HasCurrentBlocksMedian returns a boolean if a field has been set.

### GetAliasCount

`func (o *InfoModel) GetAliasCount() int32`

GetAliasCount returns the AliasCount field if non-nil, zero value otherwise.

### GetAliasCountOk

`func (o *InfoModel) GetAliasCountOk() (*int32, bool)`

GetAliasCountOk returns a tuple with the AliasCount field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetAliasCount

`func (o *InfoModel) SetAliasCount(v int32)`

SetAliasCount sets AliasCount field to given value.

### HasAliasCount

`func (o *InfoModel) HasAliasCount() bool`

HasAliasCount returns a boolean if a field has been set.

### GetCurrentMaxAllowedBlockSize

`func (o *InfoModel) GetCurrentMaxAllowedBlockSize() int32`

GetCurrentMaxAllowedBlockSize returns the CurrentMaxAllowedBlockSize field if non-nil, zero value otherwise.

### GetCurrentMaxAllowedBlockSizeOk

`func (o *InfoModel) GetCurrentMaxAllowedBlockSizeOk() (*int32, bool)`

GetCurrentMaxAllowedBlockSizeOk returns a tuple with the CurrentMaxAllowedBlockSize field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetCurrentMaxAllowedBlockSize

`func (o *InfoModel) SetCurrentMaxAllowedBlockSize(v int32)`

SetCurrentMaxAllowedBlockSize sets CurrentMaxAllowedBlockSize field to given value.

### HasCurrentMaxAllowedBlockSize

`func (o *InfoModel) HasCurrentMaxAllowedBlockSize() bool`

HasCurrentMaxAllowedBlockSize returns a boolean if a field has been set.

### GetDaemonNetworkState

`func (o *InfoModel) GetDaemonNetworkState() string`

GetDaemonNetworkState returns the DaemonNetworkState field if non-nil, zero value otherwise.

### GetDaemonNetworkStateOk

`func (o *InfoModel) GetDaemonNetworkStateOk() (*string, bool)`

GetDaemonNetworkStateOk returns a tuple with the DaemonNetworkState field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetDaemonNetworkState

`func (o *InfoModel) SetDaemonNetworkState(v string)`

SetDaemonNetworkState sets DaemonNetworkState field to given value.

### HasDaemonNetworkState

`func (o *InfoModel) HasDaemonNetworkState() bool`

HasDaemonNetworkState returns a boolean if a field has been set.

### GetSynchronizationStartHeight

`func (o *InfoModel) GetSynchronizationStartHeight() int32`

GetSynchronizationStartHeight returns the SynchronizationStartHeight field if non-nil, zero value otherwise.

### GetSynchronizationStartHeightOk

`func (o *InfoModel) GetSynchronizationStartHeightOk() (*int32, bool)`

GetSynchronizationStartHeightOk returns a tuple with the SynchronizationStartHeight field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetSynchronizationStartHeight

`func (o *InfoModel) SetSynchronizationStartHeight(v int32)`

SetSynchronizationStartHeight sets SynchronizationStartHeight field to given value.

### HasSynchronizationStartHeight

`func (o *InfoModel) HasSynchronizationStartHeight() bool`

HasSynchronizationStartHeight returns a boolean if a field has been set.

### GetMaxNetSeenHeight

`func (o *InfoModel) GetMaxNetSeenHeight() int32`

GetMaxNetSeenHeight returns the MaxNetSeenHeight field if non-nil, zero value otherwise.

### GetMaxNetSeenHeightOk

`func (o *InfoModel) GetMaxNetSeenHeightOk() (*int32, bool)`

GetMaxNetSeenHeightOk returns a tuple with the MaxNetSeenHeight field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetMaxNetSeenHeight

`func (o *InfoModel) SetMaxNetSeenHeight(v int32)`

SetMaxNetSeenHeight sets MaxNetSeenHeight field to given value.

### HasMaxNetSeenHeight

`func (o *InfoModel) HasMaxNetSeenHeight() bool`

HasMaxNetSeenHeight returns a boolean if a field has been set.

### GetMi

`func (o *InfoModel) GetMi() MaintainersInfoModel`

GetMi returns the Mi field if non-nil, zero value otherwise.

### GetMiOk

`func (o *InfoModel) GetMiOk() (*MaintainersInfoModel, bool)`

GetMiOk returns a tuple with the Mi field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetMi

`func (o *InfoModel) SetMi(v MaintainersInfoModel)`

SetMi sets Mi field to given value.

### HasMi

`func (o *InfoModel) HasMi() bool`

HasMi returns a boolean if a field has been set.

### GetPosAllowed

`func (o *InfoModel) GetPosAllowed() bool`

GetPosAllowed returns the PosAllowed field if non-nil, zero value otherwise.

### GetPosAllowedOk

`func (o *InfoModel) GetPosAllowedOk() (*bool, bool)`

GetPosAllowedOk returns a tuple with the PosAllowed field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetPosAllowed

`func (o *InfoModel) SetPosAllowed(v bool)`

SetPosAllowed sets PosAllowed field to given value.

### HasPosAllowed

`func (o *InfoModel) HasPosAllowed() bool`

HasPosAllowed returns a boolean if a field has been set.

### GetPosDifficulty

`func (o *InfoModel) GetPosDifficulty() string`

GetPosDifficulty returns the PosDifficulty field if non-nil, zero value otherwise.

### GetPosDifficultyOk

`func (o *InfoModel) GetPosDifficultyOk() (*string, bool)`

GetPosDifficultyOk returns a tuple with the PosDifficulty field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetPosDifficulty

`func (o *InfoModel) SetPosDifficulty(v string)`

SetPosDifficulty sets PosDifficulty field to given value.

### HasPosDifficulty

`func (o *InfoModel) HasPosDifficulty() bool`

HasPosDifficulty returns a boolean if a field has been set.

### GetPowDifficulty

`func (o *InfoModel) GetPowDifficulty() int32`

GetPowDifficulty returns the PowDifficulty field if non-nil, zero value otherwise.

### GetPowDifficultyOk

`func (o *InfoModel) GetPowDifficultyOk() (*int32, bool)`

GetPowDifficultyOk returns a tuple with the PowDifficulty field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetPowDifficulty

`func (o *InfoModel) SetPowDifficulty(v int32)`

SetPowDifficulty sets PowDifficulty field to given value.

### HasPowDifficulty

`func (o *InfoModel) HasPowDifficulty() bool`

HasPowDifficulty returns a boolean if a field has been set.

### GetDefaultFee

`func (o *InfoModel) GetDefaultFee() int32`

GetDefaultFee returns the DefaultFee field if non-nil, zero value otherwise.

### GetDefaultFeeOk

`func (o *InfoModel) GetDefaultFeeOk() (*int32, bool)`

GetDefaultFeeOk returns a tuple with the DefaultFee field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetDefaultFee

`func (o *InfoModel) SetDefaultFee(v int32)`

SetDefaultFee sets DefaultFee field to given value.

### HasDefaultFee

`func (o *InfoModel) HasDefaultFee() bool`

HasDefaultFee returns a boolean if a field has been set.

### GetMinimumFee

`func (o *InfoModel) GetMinimumFee() int32`

GetMinimumFee returns the MinimumFee field if non-nil, zero value otherwise.

### GetMinimumFeeOk

`func (o *InfoModel) GetMinimumFeeOk() (*int32, bool)`

GetMinimumFeeOk returns a tuple with the MinimumFee field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetMinimumFee

`func (o *InfoModel) SetMinimumFee(v int32)`

SetMinimumFee sets MinimumFee field to given value.

### HasMinimumFee

`func (o *InfoModel) HasMinimumFee() bool`

HasMinimumFee returns a boolean if a field has been set.

### GetIsHardforkActive

`func (o *InfoModel) GetIsHardforkActive() []bool`

GetIsHardforkActive returns the IsHardforkActive field if non-nil, zero value otherwise.

### GetIsHardforkActiveOk

`func (o *InfoModel) GetIsHardforkActiveOk() (*[]bool, bool)`

GetIsHardforkActiveOk returns a tuple with the IsHardforkActive field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetIsHardforkActive

`func (o *InfoModel) SetIsHardforkActive(v []bool)`

SetIsHardforkActive sets IsHardforkActive field to given value.

### HasIsHardforkActive

`func (o *InfoModel) HasIsHardforkActive() bool`

HasIsHardforkActive returns a boolean if a field has been set.

### GetNetTimeDeltaMedian

`func (o *InfoModel) GetNetTimeDeltaMedian() int64`

GetNetTimeDeltaMedian returns the NetTimeDeltaMedian field if non-nil, zero value otherwise.

### GetNetTimeDeltaMedianOk

`func (o *InfoModel) GetNetTimeDeltaMedianOk() (*int64, bool)`

GetNetTimeDeltaMedianOk returns a tuple with the NetTimeDeltaMedian field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetNetTimeDeltaMedian

`func (o *InfoModel) SetNetTimeDeltaMedian(v int64)`

SetNetTimeDeltaMedian sets NetTimeDeltaMedian field to given value.

### HasNetTimeDeltaMedian

`func (o *InfoModel) HasNetTimeDeltaMedian() bool`

HasNetTimeDeltaMedian returns a boolean if a field has been set.

### GetCurrentNetworkHashrate50

`func (o *InfoModel) GetCurrentNetworkHashrate50() int32`

GetCurrentNetworkHashrate50 returns the CurrentNetworkHashrate50 field if non-nil, zero value otherwise.

### GetCurrentNetworkHashrate50Ok

`func (o *InfoModel) GetCurrentNetworkHashrate50Ok() (*int32, bool)`

GetCurrentNetworkHashrate50Ok returns a tuple with the CurrentNetworkHashrate50 field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetCurrentNetworkHashrate50

`func (o *InfoModel) SetCurrentNetworkHashrate50(v int32)`

SetCurrentNetworkHashrate50 sets CurrentNetworkHashrate50 field to given value.

### HasCurrentNetworkHashrate50

`func (o *InfoModel) HasCurrentNetworkHashrate50() bool`

HasCurrentNetworkHashrate50 returns a boolean if a field has been set.

### GetCurrentNetworkHashrate350

`func (o *InfoModel) GetCurrentNetworkHashrate350() int32`

GetCurrentNetworkHashrate350 returns the CurrentNetworkHashrate350 field if non-nil, zero value otherwise.

### GetCurrentNetworkHashrate350Ok

`func (o *InfoModel) GetCurrentNetworkHashrate350Ok() (*int32, bool)`

GetCurrentNetworkHashrate350Ok returns a tuple with the CurrentNetworkHashrate350 field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetCurrentNetworkHashrate350

`func (o *InfoModel) SetCurrentNetworkHashrate350(v int32)`

SetCurrentNetworkHashrate350 sets CurrentNetworkHashrate350 field to given value.

### HasCurrentNetworkHashrate350

`func (o *InfoModel) HasCurrentNetworkHashrate350() bool`

HasCurrentNetworkHashrate350 returns a boolean if a field has been set.

### GetSecondsFor10Blocks

`func (o *InfoModel) GetSecondsFor10Blocks() int32`

GetSecondsFor10Blocks returns the SecondsFor10Blocks field if non-nil, zero value otherwise.

### GetSecondsFor10BlocksOk

`func (o *InfoModel) GetSecondsFor10BlocksOk() (*int32, bool)`

GetSecondsFor10BlocksOk returns a tuple with the SecondsFor10Blocks field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetSecondsFor10Blocks

`func (o *InfoModel) SetSecondsFor10Blocks(v int32)`

SetSecondsFor10Blocks sets SecondsFor10Blocks field to given value.

### HasSecondsFor10Blocks

`func (o *InfoModel) HasSecondsFor10Blocks() bool`

HasSecondsFor10Blocks returns a boolean if a field has been set.

### GetSecondsFor30Blocks

`func (o *InfoModel) GetSecondsFor30Blocks() int32`

GetSecondsFor30Blocks returns the SecondsFor30Blocks field if non-nil, zero value otherwise.

### GetSecondsFor30BlocksOk

`func (o *InfoModel) GetSecondsFor30BlocksOk() (*int32, bool)`

GetSecondsFor30BlocksOk returns a tuple with the SecondsFor30Blocks field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetSecondsFor30Blocks

`func (o *InfoModel) SetSecondsFor30Blocks(v int32)`

SetSecondsFor30Blocks sets SecondsFor30Blocks field to given value.

### HasSecondsFor30Blocks

`func (o *InfoModel) HasSecondsFor30Blocks() bool`

HasSecondsFor30Blocks returns a boolean if a field has been set.

### GetTransactionsCntPerDay

`func (o *InfoModel) GetTransactionsCntPerDay() []int32`

GetTransactionsCntPerDay returns the TransactionsCntPerDay field if non-nil, zero value otherwise.

### GetTransactionsCntPerDayOk

`func (o *InfoModel) GetTransactionsCntPerDayOk() (*[]int32, bool)`

GetTransactionsCntPerDayOk returns a tuple with the TransactionsCntPerDay field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTransactionsCntPerDay

`func (o *InfoModel) SetTransactionsCntPerDay(v []int32)`

SetTransactionsCntPerDay sets TransactionsCntPerDay field to given value.

### HasTransactionsCntPerDay

`func (o *InfoModel) HasTransactionsCntPerDay() bool`

HasTransactionsCntPerDay returns a boolean if a field has been set.

### GetTransactionsVolumePerDay

`func (o *InfoModel) GetTransactionsVolumePerDay() []int32`

GetTransactionsVolumePerDay returns the TransactionsVolumePerDay field if non-nil, zero value otherwise.

### GetTransactionsVolumePerDayOk

`func (o *InfoModel) GetTransactionsVolumePerDayOk() (*[]int32, bool)`

GetTransactionsVolumePerDayOk returns a tuple with the TransactionsVolumePerDay field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTransactionsVolumePerDay

`func (o *InfoModel) SetTransactionsVolumePerDay(v []int32)`

SetTransactionsVolumePerDay sets TransactionsVolumePerDay field to given value.

### HasTransactionsVolumePerDay

`func (o *InfoModel) HasTransactionsVolumePerDay() bool`

HasTransactionsVolumePerDay returns a boolean if a field has been set.

### GetLastPosTimestamp

`func (o *InfoModel) GetLastPosTimestamp() int32`

GetLastPosTimestamp returns the LastPosTimestamp field if non-nil, zero value otherwise.

### GetLastPosTimestampOk

`func (o *InfoModel) GetLastPosTimestampOk() (*int32, bool)`

GetLastPosTimestampOk returns a tuple with the LastPosTimestamp field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetLastPosTimestamp

`func (o *InfoModel) SetLastPosTimestamp(v int32)`

SetLastPosTimestamp sets LastPosTimestamp field to given value.

### HasLastPosTimestamp

`func (o *InfoModel) HasLastPosTimestamp() bool`

HasLastPosTimestamp returns a boolean if a field has been set.

### GetLastPowTimestamp

`func (o *InfoModel) GetLastPowTimestamp() int32`

GetLastPowTimestamp returns the LastPowTimestamp field if non-nil, zero value otherwise.

### GetLastPowTimestampOk

`func (o *InfoModel) GetLastPowTimestampOk() (*int32, bool)`

GetLastPowTimestampOk returns a tuple with the LastPowTimestamp field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetLastPowTimestamp

`func (o *InfoModel) SetLastPowTimestamp(v int32)`

SetLastPowTimestamp sets LastPowTimestamp field to given value.

### HasLastPowTimestamp

`func (o *InfoModel) HasLastPowTimestamp() bool`

HasLastPowTimestamp returns a boolean if a field has been set.

### GetTotalCoins

`func (o *InfoModel) GetTotalCoins() string`

GetTotalCoins returns the TotalCoins field if non-nil, zero value otherwise.

### GetTotalCoinsOk

`func (o *InfoModel) GetTotalCoinsOk() (*string, bool)`

GetTotalCoinsOk returns a tuple with the TotalCoins field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTotalCoins

`func (o *InfoModel) SetTotalCoins(v string)`

SetTotalCoins sets TotalCoins field to given value.

### HasTotalCoins

`func (o *InfoModel) HasTotalCoins() bool`

HasTotalCoins returns a boolean if a field has been set.

### GetLastBlockSize

`func (o *InfoModel) GetLastBlockSize() int32`

GetLastBlockSize returns the LastBlockSize field if non-nil, zero value otherwise.

### GetLastBlockSizeOk

`func (o *InfoModel) GetLastBlockSizeOk() (*int32, bool)`

GetLastBlockSizeOk returns a tuple with the LastBlockSize field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetLastBlockSize

`func (o *InfoModel) SetLastBlockSize(v int32)`

SetLastBlockSize sets LastBlockSize field to given value.

### HasLastBlockSize

`func (o *InfoModel) HasLastBlockSize() bool`

HasLastBlockSize returns a boolean if a field has been set.

### GetTxCountInLastBlock

`func (o *InfoModel) GetTxCountInLastBlock() int32`

GetTxCountInLastBlock returns the TxCountInLastBlock field if non-nil, zero value otherwise.

### GetTxCountInLastBlockOk

`func (o *InfoModel) GetTxCountInLastBlockOk() (*int32, bool)`

GetTxCountInLastBlockOk returns a tuple with the TxCountInLastBlock field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTxCountInLastBlock

`func (o *InfoModel) SetTxCountInLastBlock(v int32)`

SetTxCountInLastBlock sets TxCountInLastBlock field to given value.

### HasTxCountInLastBlock

`func (o *InfoModel) HasTxCountInLastBlock() bool`

HasTxCountInLastBlock returns a boolean if a field has been set.

### GetPosSequenceFactor

`func (o *InfoModel) GetPosSequenceFactor() float64`

GetPosSequenceFactor returns the PosSequenceFactor field if non-nil, zero value otherwise.

### GetPosSequenceFactorOk

`func (o *InfoModel) GetPosSequenceFactorOk() (*float64, bool)`

GetPosSequenceFactorOk returns a tuple with the PosSequenceFactor field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetPosSequenceFactor

`func (o *InfoModel) SetPosSequenceFactor(v float64)`

SetPosSequenceFactor sets PosSequenceFactor field to given value.

### HasPosSequenceFactor

`func (o *InfoModel) HasPosSequenceFactor() bool`

HasPosSequenceFactor returns a boolean if a field has been set.

### GetPowSequenceFactor

`func (o *InfoModel) GetPowSequenceFactor() float64`

GetPowSequenceFactor returns the PowSequenceFactor field if non-nil, zero value otherwise.

### GetPowSequenceFactorOk

`func (o *InfoModel) GetPowSequenceFactorOk() (*float64, bool)`

GetPowSequenceFactorOk returns a tuple with the PowSequenceFactor field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetPowSequenceFactor

`func (o *InfoModel) SetPowSequenceFactor(v float64)`

SetPowSequenceFactor sets PowSequenceFactor field to given value.

### HasPowSequenceFactor

`func (o *InfoModel) HasPowSequenceFactor() bool`

HasPowSequenceFactor returns a boolean if a field has been set.

### GetBlockReward

`func (o *InfoModel) GetBlockReward() int32`

GetBlockReward returns the BlockReward field if non-nil, zero value otherwise.

### GetBlockRewardOk

`func (o *InfoModel) GetBlockRewardOk() (*int32, bool)`

GetBlockRewardOk returns a tuple with the BlockReward field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetBlockReward

`func (o *InfoModel) SetBlockReward(v int32)`

SetBlockReward sets BlockReward field to given value.

### HasBlockReward

`func (o *InfoModel) HasBlockReward() bool`

HasBlockReward returns a boolean if a field has been set.

### GetLastBlockTotalReward

`func (o *InfoModel) GetLastBlockTotalReward() int32`

GetLastBlockTotalReward returns the LastBlockTotalReward field if non-nil, zero value otherwise.

### GetLastBlockTotalRewardOk

`func (o *InfoModel) GetLastBlockTotalRewardOk() (*int32, bool)`

GetLastBlockTotalRewardOk returns a tuple with the LastBlockTotalReward field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetLastBlockTotalReward

`func (o *InfoModel) SetLastBlockTotalReward(v int32)`

SetLastBlockTotalReward sets LastBlockTotalReward field to given value.

### HasLastBlockTotalReward

`func (o *InfoModel) HasLastBlockTotalReward() bool`

HasLastBlockTotalReward returns a boolean if a field has been set.

### GetPosDiffTotalCoinsRate

`func (o *InfoModel) GetPosDiffTotalCoinsRate() int32`

GetPosDiffTotalCoinsRate returns the PosDiffTotalCoinsRate field if non-nil, zero value otherwise.

### GetPosDiffTotalCoinsRateOk

`func (o *InfoModel) GetPosDiffTotalCoinsRateOk() (*int32, bool)`

GetPosDiffTotalCoinsRateOk returns a tuple with the PosDiffTotalCoinsRate field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetPosDiffTotalCoinsRate

`func (o *InfoModel) SetPosDiffTotalCoinsRate(v int32)`

SetPosDiffTotalCoinsRate sets PosDiffTotalCoinsRate field to given value.

### HasPosDiffTotalCoinsRate

`func (o *InfoModel) HasPosDiffTotalCoinsRate() bool`

HasPosDiffTotalCoinsRate returns a boolean if a field has been set.

### GetLastBlockTimestamp

`func (o *InfoModel) GetLastBlockTimestamp() int32`

GetLastBlockTimestamp returns the LastBlockTimestamp field if non-nil, zero value otherwise.

### GetLastBlockTimestampOk

`func (o *InfoModel) GetLastBlockTimestampOk() (*int32, bool)`

GetLastBlockTimestampOk returns a tuple with the LastBlockTimestamp field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetLastBlockTimestamp

`func (o *InfoModel) SetLastBlockTimestamp(v int32)`

SetLastBlockTimestamp sets LastBlockTimestamp field to given value.

### HasLastBlockTimestamp

`func (o *InfoModel) HasLastBlockTimestamp() bool`

HasLastBlockTimestamp returns a boolean if a field has been set.

### GetLastBlockHash

`func (o *InfoModel) GetLastBlockHash() string`

GetLastBlockHash returns the LastBlockHash field if non-nil, zero value otherwise.

### GetLastBlockHashOk

`func (o *InfoModel) GetLastBlockHashOk() (*string, bool)`

GetLastBlockHashOk returns a tuple with the LastBlockHash field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetLastBlockHash

`func (o *InfoModel) SetLastBlockHash(v string)`

SetLastBlockHash sets LastBlockHash field to given value.

### HasLastBlockHash

`func (o *InfoModel) HasLastBlockHash() bool`

HasLastBlockHash returns a boolean if a field has been set.

### GetPosBlockTsShiftVsActual

`func (o *InfoModel) GetPosBlockTsShiftVsActual() int64`

GetPosBlockTsShiftVsActual returns the PosBlockTsShiftVsActual field if non-nil, zero value otherwise.

### GetPosBlockTsShiftVsActualOk

`func (o *InfoModel) GetPosBlockTsShiftVsActualOk() (*int64, bool)`

GetPosBlockTsShiftVsActualOk returns a tuple with the PosBlockTsShiftVsActual field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetPosBlockTsShiftVsActual

`func (o *InfoModel) SetPosBlockTsShiftVsActual(v int64)`

SetPosBlockTsShiftVsActual sets PosBlockTsShiftVsActual field to given value.

### HasPosBlockTsShiftVsActual

`func (o *InfoModel) HasPosBlockTsShiftVsActual() bool`

HasPosBlockTsShiftVsActual returns a boolean if a field has been set.

### GetOutsStat

`func (o *InfoModel) GetOutsStat() map[string]int32`

GetOutsStat returns the OutsStat field if non-nil, zero value otherwise.

### GetOutsStatOk

`func (o *InfoModel) GetOutsStatOk() (*map[string]int32, bool)`

GetOutsStatOk returns a tuple with the OutsStat field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetOutsStat

`func (o *InfoModel) SetOutsStat(v map[string]int32)`

SetOutsStat sets OutsStat field to given value.

### HasOutsStat

`func (o *InfoModel) HasOutsStat() bool`

HasOutsStat returns a boolean if a field has been set.

### GetPerformanceData

`func (o *InfoModel) GetPerformanceData() PerformanceModel`

GetPerformanceData returns the PerformanceData field if non-nil, zero value otherwise.

### GetPerformanceDataOk

`func (o *InfoModel) GetPerformanceDataOk() (*PerformanceModel, bool)`

GetPerformanceDataOk returns a tuple with the PerformanceData field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetPerformanceData

`func (o *InfoModel) SetPerformanceData(v PerformanceModel)`

SetPerformanceData sets PerformanceData field to given value.

### HasPerformanceData

`func (o *InfoModel) HasPerformanceData() bool`

HasPerformanceData returns a boolean if a field has been set.

### GetOffersCount

`func (o *InfoModel) GetOffersCount() int32`

GetOffersCount returns the OffersCount field if non-nil, zero value otherwise.

### GetOffersCountOk

`func (o *InfoModel) GetOffersCountOk() (*int32, bool)`

GetOffersCountOk returns a tuple with the OffersCount field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetOffersCount

`func (o *InfoModel) SetOffersCount(v int32)`

SetOffersCount sets OffersCount field to given value.

### HasOffersCount

`func (o *InfoModel) HasOffersCount() bool`

HasOffersCount returns a boolean if a field has been set.

### GetExpirationMedianTimestamp

`func (o *InfoModel) GetExpirationMedianTimestamp() int32`

GetExpirationMedianTimestamp returns the ExpirationMedianTimestamp field if non-nil, zero value otherwise.

### GetExpirationMedianTimestampOk

`func (o *InfoModel) GetExpirationMedianTimestampOk() (*int32, bool)`

GetExpirationMedianTimestampOk returns a tuple with the ExpirationMedianTimestamp field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetExpirationMedianTimestamp

`func (o *InfoModel) SetExpirationMedianTimestamp(v int32)`

SetExpirationMedianTimestamp sets ExpirationMedianTimestamp field to given value.

### HasExpirationMedianTimestamp

`func (o *InfoModel) HasExpirationMedianTimestamp() bool`

HasExpirationMedianTimestamp returns a boolean if a field has been set.


[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


