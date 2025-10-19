# TxGenerationContextModel

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**AssetIds** | Pointer to **[]string** |  | [optional] 
**BlindedAssetIds** | Pointer to **[]string** |  | [optional] 
**AmountCommitments** | Pointer to **[]string** |  | [optional] 
**AssetIdBlindingMasks** | Pointer to **[]string** |  | [optional] 
**Amounts** | Pointer to **[]string** |  | [optional] 
**AmountBlindingMasks** | Pointer to **[]string** |  | [optional] 
**PseudoOutsBlindedAssetIds** | Pointer to **[]string** |  | [optional] 
**PseudoOutsPlusRealOutBlindingMasks** | Pointer to **[]string** |  | [optional] 
**RealZcInsAssetIds** | Pointer to **[]string** |  | [optional] 
**ZcInputAmounts** | Pointer to **[]int32** |  | [optional] 
**PseudoOutAmountCommitmentsSum** | Pointer to **string** |  | [optional] 
**PseudoOutAmountBlindingMasksSum** | Pointer to **string** |  | [optional] 
**RealInAssetIdBlindingMaskXAmountSum** | Pointer to **string** |  | [optional] 
**AmountCommitmentsSum** | Pointer to **string** |  | [optional] 
**AmountBlindingMasksSum** | Pointer to **string** |  | [optional] 
**AssetIdBlindingMaskXAmountSum** | Pointer to **string** |  | [optional] 
**AoAssetId** | Pointer to **string** |  | [optional] 
**AoAssetIdPt** | Pointer to **string** |  | [optional] 
**AoAmountCommitment** | Pointer to **string** |  | [optional] 
**AoAmountBlindingMask** | Pointer to **string** |  | [optional] 
**AoCommitmentInOutputs** | Pointer to **bool** |  | [optional] 
**TxKeyPub** | Pointer to **string** |  | [optional] 
**TxKeySec** | Pointer to **string** |  | [optional] 
**TxPubKeyP** | Pointer to **string** |  | [optional] 

## Methods

### NewTxGenerationContextModel

`func NewTxGenerationContextModel() *TxGenerationContextModel`

NewTxGenerationContextModel instantiates a new TxGenerationContextModel object
This constructor will assign default values to properties that have it defined,
and makes sure properties required by API are set, but the set of arguments
will change when the set of required properties is changed

### NewTxGenerationContextModelWithDefaults

`func NewTxGenerationContextModelWithDefaults() *TxGenerationContextModel`

NewTxGenerationContextModelWithDefaults instantiates a new TxGenerationContextModel object
This constructor will only assign default values to properties that have it defined,
but it doesn't guarantee that properties required by API are set

### GetAssetIds

`func (o *TxGenerationContextModel) GetAssetIds() []string`

GetAssetIds returns the AssetIds field if non-nil, zero value otherwise.

### GetAssetIdsOk

`func (o *TxGenerationContextModel) GetAssetIdsOk() (*[]string, bool)`

GetAssetIdsOk returns a tuple with the AssetIds field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetAssetIds

`func (o *TxGenerationContextModel) SetAssetIds(v []string)`

SetAssetIds sets AssetIds field to given value.

### HasAssetIds

`func (o *TxGenerationContextModel) HasAssetIds() bool`

HasAssetIds returns a boolean if a field has been set.

### GetBlindedAssetIds

`func (o *TxGenerationContextModel) GetBlindedAssetIds() []string`

GetBlindedAssetIds returns the BlindedAssetIds field if non-nil, zero value otherwise.

### GetBlindedAssetIdsOk

`func (o *TxGenerationContextModel) GetBlindedAssetIdsOk() (*[]string, bool)`

GetBlindedAssetIdsOk returns a tuple with the BlindedAssetIds field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetBlindedAssetIds

`func (o *TxGenerationContextModel) SetBlindedAssetIds(v []string)`

SetBlindedAssetIds sets BlindedAssetIds field to given value.

### HasBlindedAssetIds

`func (o *TxGenerationContextModel) HasBlindedAssetIds() bool`

HasBlindedAssetIds returns a boolean if a field has been set.

### GetAmountCommitments

`func (o *TxGenerationContextModel) GetAmountCommitments() []string`

GetAmountCommitments returns the AmountCommitments field if non-nil, zero value otherwise.

### GetAmountCommitmentsOk

`func (o *TxGenerationContextModel) GetAmountCommitmentsOk() (*[]string, bool)`

GetAmountCommitmentsOk returns a tuple with the AmountCommitments field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetAmountCommitments

`func (o *TxGenerationContextModel) SetAmountCommitments(v []string)`

SetAmountCommitments sets AmountCommitments field to given value.

### HasAmountCommitments

`func (o *TxGenerationContextModel) HasAmountCommitments() bool`

HasAmountCommitments returns a boolean if a field has been set.

### GetAssetIdBlindingMasks

`func (o *TxGenerationContextModel) GetAssetIdBlindingMasks() []string`

GetAssetIdBlindingMasks returns the AssetIdBlindingMasks field if non-nil, zero value otherwise.

### GetAssetIdBlindingMasksOk

`func (o *TxGenerationContextModel) GetAssetIdBlindingMasksOk() (*[]string, bool)`

GetAssetIdBlindingMasksOk returns a tuple with the AssetIdBlindingMasks field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetAssetIdBlindingMasks

`func (o *TxGenerationContextModel) SetAssetIdBlindingMasks(v []string)`

SetAssetIdBlindingMasks sets AssetIdBlindingMasks field to given value.

### HasAssetIdBlindingMasks

`func (o *TxGenerationContextModel) HasAssetIdBlindingMasks() bool`

HasAssetIdBlindingMasks returns a boolean if a field has been set.

### GetAmounts

`func (o *TxGenerationContextModel) GetAmounts() []string`

GetAmounts returns the Amounts field if non-nil, zero value otherwise.

### GetAmountsOk

`func (o *TxGenerationContextModel) GetAmountsOk() (*[]string, bool)`

GetAmountsOk returns a tuple with the Amounts field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetAmounts

`func (o *TxGenerationContextModel) SetAmounts(v []string)`

SetAmounts sets Amounts field to given value.

### HasAmounts

`func (o *TxGenerationContextModel) HasAmounts() bool`

HasAmounts returns a boolean if a field has been set.

### GetAmountBlindingMasks

`func (o *TxGenerationContextModel) GetAmountBlindingMasks() []string`

GetAmountBlindingMasks returns the AmountBlindingMasks field if non-nil, zero value otherwise.

### GetAmountBlindingMasksOk

`func (o *TxGenerationContextModel) GetAmountBlindingMasksOk() (*[]string, bool)`

GetAmountBlindingMasksOk returns a tuple with the AmountBlindingMasks field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetAmountBlindingMasks

`func (o *TxGenerationContextModel) SetAmountBlindingMasks(v []string)`

SetAmountBlindingMasks sets AmountBlindingMasks field to given value.

### HasAmountBlindingMasks

`func (o *TxGenerationContextModel) HasAmountBlindingMasks() bool`

HasAmountBlindingMasks returns a boolean if a field has been set.

### GetPseudoOutsBlindedAssetIds

`func (o *TxGenerationContextModel) GetPseudoOutsBlindedAssetIds() []string`

GetPseudoOutsBlindedAssetIds returns the PseudoOutsBlindedAssetIds field if non-nil, zero value otherwise.

### GetPseudoOutsBlindedAssetIdsOk

`func (o *TxGenerationContextModel) GetPseudoOutsBlindedAssetIdsOk() (*[]string, bool)`

GetPseudoOutsBlindedAssetIdsOk returns a tuple with the PseudoOutsBlindedAssetIds field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetPseudoOutsBlindedAssetIds

`func (o *TxGenerationContextModel) SetPseudoOutsBlindedAssetIds(v []string)`

SetPseudoOutsBlindedAssetIds sets PseudoOutsBlindedAssetIds field to given value.

### HasPseudoOutsBlindedAssetIds

`func (o *TxGenerationContextModel) HasPseudoOutsBlindedAssetIds() bool`

HasPseudoOutsBlindedAssetIds returns a boolean if a field has been set.

### GetPseudoOutsPlusRealOutBlindingMasks

`func (o *TxGenerationContextModel) GetPseudoOutsPlusRealOutBlindingMasks() []string`

GetPseudoOutsPlusRealOutBlindingMasks returns the PseudoOutsPlusRealOutBlindingMasks field if non-nil, zero value otherwise.

### GetPseudoOutsPlusRealOutBlindingMasksOk

`func (o *TxGenerationContextModel) GetPseudoOutsPlusRealOutBlindingMasksOk() (*[]string, bool)`

GetPseudoOutsPlusRealOutBlindingMasksOk returns a tuple with the PseudoOutsPlusRealOutBlindingMasks field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetPseudoOutsPlusRealOutBlindingMasks

`func (o *TxGenerationContextModel) SetPseudoOutsPlusRealOutBlindingMasks(v []string)`

SetPseudoOutsPlusRealOutBlindingMasks sets PseudoOutsPlusRealOutBlindingMasks field to given value.

### HasPseudoOutsPlusRealOutBlindingMasks

`func (o *TxGenerationContextModel) HasPseudoOutsPlusRealOutBlindingMasks() bool`

HasPseudoOutsPlusRealOutBlindingMasks returns a boolean if a field has been set.

### GetRealZcInsAssetIds

`func (o *TxGenerationContextModel) GetRealZcInsAssetIds() []string`

GetRealZcInsAssetIds returns the RealZcInsAssetIds field if non-nil, zero value otherwise.

### GetRealZcInsAssetIdsOk

`func (o *TxGenerationContextModel) GetRealZcInsAssetIdsOk() (*[]string, bool)`

GetRealZcInsAssetIdsOk returns a tuple with the RealZcInsAssetIds field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetRealZcInsAssetIds

`func (o *TxGenerationContextModel) SetRealZcInsAssetIds(v []string)`

SetRealZcInsAssetIds sets RealZcInsAssetIds field to given value.

### HasRealZcInsAssetIds

`func (o *TxGenerationContextModel) HasRealZcInsAssetIds() bool`

HasRealZcInsAssetIds returns a boolean if a field has been set.

### GetZcInputAmounts

`func (o *TxGenerationContextModel) GetZcInputAmounts() []int32`

GetZcInputAmounts returns the ZcInputAmounts field if non-nil, zero value otherwise.

### GetZcInputAmountsOk

`func (o *TxGenerationContextModel) GetZcInputAmountsOk() (*[]int32, bool)`

GetZcInputAmountsOk returns a tuple with the ZcInputAmounts field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetZcInputAmounts

`func (o *TxGenerationContextModel) SetZcInputAmounts(v []int32)`

SetZcInputAmounts sets ZcInputAmounts field to given value.

### HasZcInputAmounts

`func (o *TxGenerationContextModel) HasZcInputAmounts() bool`

HasZcInputAmounts returns a boolean if a field has been set.

### GetPseudoOutAmountCommitmentsSum

`func (o *TxGenerationContextModel) GetPseudoOutAmountCommitmentsSum() string`

GetPseudoOutAmountCommitmentsSum returns the PseudoOutAmountCommitmentsSum field if non-nil, zero value otherwise.

### GetPseudoOutAmountCommitmentsSumOk

`func (o *TxGenerationContextModel) GetPseudoOutAmountCommitmentsSumOk() (*string, bool)`

GetPseudoOutAmountCommitmentsSumOk returns a tuple with the PseudoOutAmountCommitmentsSum field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetPseudoOutAmountCommitmentsSum

`func (o *TxGenerationContextModel) SetPseudoOutAmountCommitmentsSum(v string)`

SetPseudoOutAmountCommitmentsSum sets PseudoOutAmountCommitmentsSum field to given value.

### HasPseudoOutAmountCommitmentsSum

`func (o *TxGenerationContextModel) HasPseudoOutAmountCommitmentsSum() bool`

HasPseudoOutAmountCommitmentsSum returns a boolean if a field has been set.

### GetPseudoOutAmountBlindingMasksSum

`func (o *TxGenerationContextModel) GetPseudoOutAmountBlindingMasksSum() string`

GetPseudoOutAmountBlindingMasksSum returns the PseudoOutAmountBlindingMasksSum field if non-nil, zero value otherwise.

### GetPseudoOutAmountBlindingMasksSumOk

`func (o *TxGenerationContextModel) GetPseudoOutAmountBlindingMasksSumOk() (*string, bool)`

GetPseudoOutAmountBlindingMasksSumOk returns a tuple with the PseudoOutAmountBlindingMasksSum field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetPseudoOutAmountBlindingMasksSum

`func (o *TxGenerationContextModel) SetPseudoOutAmountBlindingMasksSum(v string)`

SetPseudoOutAmountBlindingMasksSum sets PseudoOutAmountBlindingMasksSum field to given value.

### HasPseudoOutAmountBlindingMasksSum

`func (o *TxGenerationContextModel) HasPseudoOutAmountBlindingMasksSum() bool`

HasPseudoOutAmountBlindingMasksSum returns a boolean if a field has been set.

### GetRealInAssetIdBlindingMaskXAmountSum

`func (o *TxGenerationContextModel) GetRealInAssetIdBlindingMaskXAmountSum() string`

GetRealInAssetIdBlindingMaskXAmountSum returns the RealInAssetIdBlindingMaskXAmountSum field if non-nil, zero value otherwise.

### GetRealInAssetIdBlindingMaskXAmountSumOk

`func (o *TxGenerationContextModel) GetRealInAssetIdBlindingMaskXAmountSumOk() (*string, bool)`

GetRealInAssetIdBlindingMaskXAmountSumOk returns a tuple with the RealInAssetIdBlindingMaskXAmountSum field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetRealInAssetIdBlindingMaskXAmountSum

`func (o *TxGenerationContextModel) SetRealInAssetIdBlindingMaskXAmountSum(v string)`

SetRealInAssetIdBlindingMaskXAmountSum sets RealInAssetIdBlindingMaskXAmountSum field to given value.

### HasRealInAssetIdBlindingMaskXAmountSum

`func (o *TxGenerationContextModel) HasRealInAssetIdBlindingMaskXAmountSum() bool`

HasRealInAssetIdBlindingMaskXAmountSum returns a boolean if a field has been set.

### GetAmountCommitmentsSum

`func (o *TxGenerationContextModel) GetAmountCommitmentsSum() string`

GetAmountCommitmentsSum returns the AmountCommitmentsSum field if non-nil, zero value otherwise.

### GetAmountCommitmentsSumOk

`func (o *TxGenerationContextModel) GetAmountCommitmentsSumOk() (*string, bool)`

GetAmountCommitmentsSumOk returns a tuple with the AmountCommitmentsSum field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetAmountCommitmentsSum

`func (o *TxGenerationContextModel) SetAmountCommitmentsSum(v string)`

SetAmountCommitmentsSum sets AmountCommitmentsSum field to given value.

### HasAmountCommitmentsSum

`func (o *TxGenerationContextModel) HasAmountCommitmentsSum() bool`

HasAmountCommitmentsSum returns a boolean if a field has been set.

### GetAmountBlindingMasksSum

`func (o *TxGenerationContextModel) GetAmountBlindingMasksSum() string`

GetAmountBlindingMasksSum returns the AmountBlindingMasksSum field if non-nil, zero value otherwise.

### GetAmountBlindingMasksSumOk

`func (o *TxGenerationContextModel) GetAmountBlindingMasksSumOk() (*string, bool)`

GetAmountBlindingMasksSumOk returns a tuple with the AmountBlindingMasksSum field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetAmountBlindingMasksSum

`func (o *TxGenerationContextModel) SetAmountBlindingMasksSum(v string)`

SetAmountBlindingMasksSum sets AmountBlindingMasksSum field to given value.

### HasAmountBlindingMasksSum

`func (o *TxGenerationContextModel) HasAmountBlindingMasksSum() bool`

HasAmountBlindingMasksSum returns a boolean if a field has been set.

### GetAssetIdBlindingMaskXAmountSum

`func (o *TxGenerationContextModel) GetAssetIdBlindingMaskXAmountSum() string`

GetAssetIdBlindingMaskXAmountSum returns the AssetIdBlindingMaskXAmountSum field if non-nil, zero value otherwise.

### GetAssetIdBlindingMaskXAmountSumOk

`func (o *TxGenerationContextModel) GetAssetIdBlindingMaskXAmountSumOk() (*string, bool)`

GetAssetIdBlindingMaskXAmountSumOk returns a tuple with the AssetIdBlindingMaskXAmountSum field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetAssetIdBlindingMaskXAmountSum

`func (o *TxGenerationContextModel) SetAssetIdBlindingMaskXAmountSum(v string)`

SetAssetIdBlindingMaskXAmountSum sets AssetIdBlindingMaskXAmountSum field to given value.

### HasAssetIdBlindingMaskXAmountSum

`func (o *TxGenerationContextModel) HasAssetIdBlindingMaskXAmountSum() bool`

HasAssetIdBlindingMaskXAmountSum returns a boolean if a field has been set.

### GetAoAssetId

`func (o *TxGenerationContextModel) GetAoAssetId() string`

GetAoAssetId returns the AoAssetId field if non-nil, zero value otherwise.

### GetAoAssetIdOk

`func (o *TxGenerationContextModel) GetAoAssetIdOk() (*string, bool)`

GetAoAssetIdOk returns a tuple with the AoAssetId field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetAoAssetId

`func (o *TxGenerationContextModel) SetAoAssetId(v string)`

SetAoAssetId sets AoAssetId field to given value.

### HasAoAssetId

`func (o *TxGenerationContextModel) HasAoAssetId() bool`

HasAoAssetId returns a boolean if a field has been set.

### GetAoAssetIdPt

`func (o *TxGenerationContextModel) GetAoAssetIdPt() string`

GetAoAssetIdPt returns the AoAssetIdPt field if non-nil, zero value otherwise.

### GetAoAssetIdPtOk

`func (o *TxGenerationContextModel) GetAoAssetIdPtOk() (*string, bool)`

GetAoAssetIdPtOk returns a tuple with the AoAssetIdPt field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetAoAssetIdPt

`func (o *TxGenerationContextModel) SetAoAssetIdPt(v string)`

SetAoAssetIdPt sets AoAssetIdPt field to given value.

### HasAoAssetIdPt

`func (o *TxGenerationContextModel) HasAoAssetIdPt() bool`

HasAoAssetIdPt returns a boolean if a field has been set.

### GetAoAmountCommitment

`func (o *TxGenerationContextModel) GetAoAmountCommitment() string`

GetAoAmountCommitment returns the AoAmountCommitment field if non-nil, zero value otherwise.

### GetAoAmountCommitmentOk

`func (o *TxGenerationContextModel) GetAoAmountCommitmentOk() (*string, bool)`

GetAoAmountCommitmentOk returns a tuple with the AoAmountCommitment field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetAoAmountCommitment

`func (o *TxGenerationContextModel) SetAoAmountCommitment(v string)`

SetAoAmountCommitment sets AoAmountCommitment field to given value.

### HasAoAmountCommitment

`func (o *TxGenerationContextModel) HasAoAmountCommitment() bool`

HasAoAmountCommitment returns a boolean if a field has been set.

### GetAoAmountBlindingMask

`func (o *TxGenerationContextModel) GetAoAmountBlindingMask() string`

GetAoAmountBlindingMask returns the AoAmountBlindingMask field if non-nil, zero value otherwise.

### GetAoAmountBlindingMaskOk

`func (o *TxGenerationContextModel) GetAoAmountBlindingMaskOk() (*string, bool)`

GetAoAmountBlindingMaskOk returns a tuple with the AoAmountBlindingMask field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetAoAmountBlindingMask

`func (o *TxGenerationContextModel) SetAoAmountBlindingMask(v string)`

SetAoAmountBlindingMask sets AoAmountBlindingMask field to given value.

### HasAoAmountBlindingMask

`func (o *TxGenerationContextModel) HasAoAmountBlindingMask() bool`

HasAoAmountBlindingMask returns a boolean if a field has been set.

### GetAoCommitmentInOutputs

`func (o *TxGenerationContextModel) GetAoCommitmentInOutputs() bool`

GetAoCommitmentInOutputs returns the AoCommitmentInOutputs field if non-nil, zero value otherwise.

### GetAoCommitmentInOutputsOk

`func (o *TxGenerationContextModel) GetAoCommitmentInOutputsOk() (*bool, bool)`

GetAoCommitmentInOutputsOk returns a tuple with the AoCommitmentInOutputs field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetAoCommitmentInOutputs

`func (o *TxGenerationContextModel) SetAoCommitmentInOutputs(v bool)`

SetAoCommitmentInOutputs sets AoCommitmentInOutputs field to given value.

### HasAoCommitmentInOutputs

`func (o *TxGenerationContextModel) HasAoCommitmentInOutputs() bool`

HasAoCommitmentInOutputs returns a boolean if a field has been set.

### GetTxKeyPub

`func (o *TxGenerationContextModel) GetTxKeyPub() string`

GetTxKeyPub returns the TxKeyPub field if non-nil, zero value otherwise.

### GetTxKeyPubOk

`func (o *TxGenerationContextModel) GetTxKeyPubOk() (*string, bool)`

GetTxKeyPubOk returns a tuple with the TxKeyPub field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTxKeyPub

`func (o *TxGenerationContextModel) SetTxKeyPub(v string)`

SetTxKeyPub sets TxKeyPub field to given value.

### HasTxKeyPub

`func (o *TxGenerationContextModel) HasTxKeyPub() bool`

HasTxKeyPub returns a boolean if a field has been set.

### GetTxKeySec

`func (o *TxGenerationContextModel) GetTxKeySec() string`

GetTxKeySec returns the TxKeySec field if non-nil, zero value otherwise.

### GetTxKeySecOk

`func (o *TxGenerationContextModel) GetTxKeySecOk() (*string, bool)`

GetTxKeySecOk returns a tuple with the TxKeySec field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTxKeySec

`func (o *TxGenerationContextModel) SetTxKeySec(v string)`

SetTxKeySec sets TxKeySec field to given value.

### HasTxKeySec

`func (o *TxGenerationContextModel) HasTxKeySec() bool`

HasTxKeySec returns a boolean if a field has been set.

### GetTxPubKeyP

`func (o *TxGenerationContextModel) GetTxPubKeyP() string`

GetTxPubKeyP returns the TxPubKeyP field if non-nil, zero value otherwise.

### GetTxPubKeyPOk

`func (o *TxGenerationContextModel) GetTxPubKeyPOk() (*string, bool)`

GetTxPubKeyPOk returns a tuple with the TxPubKeyP field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTxPubKeyP

`func (o *TxGenerationContextModel) SetTxPubKeyP(v string)`

SetTxPubKeyP sets TxPubKeyP field to given value.

### HasTxPubKeyP

`func (o *TxGenerationContextModel) HasTxPubKeyP() bool`

HasTxPubKeyP returns a boolean if a field has been set.


[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


