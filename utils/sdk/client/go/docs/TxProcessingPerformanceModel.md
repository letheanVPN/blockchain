# TxProcessingPerformanceModel

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**TxCheckInputs** | Pointer to **int32** |  | [optional] 
**TxAddOneTx** | Pointer to **int32** |  | [optional] 
**TxProcessExtra** | Pointer to **int32** |  | [optional] 
**TxProcessAttachment** | Pointer to **int32** |  | [optional] 
**TxProcessInputs** | Pointer to **int32** |  | [optional] 
**TxPushGlobalIndex** | Pointer to **int32** |  | [optional] 
**TxCheckExist** | Pointer to **int32** |  | [optional] 
**TxPrintLog** | Pointer to **int32** |  | [optional] 
**TxPrapareAppend** | Pointer to **int32** |  | [optional] 
**TxAppend** | Pointer to **int32** |  | [optional] 
**TxAppendRlWait** | Pointer to **int32** |  | [optional] 
**TxAppendIsExpired** | Pointer to **int32** |  | [optional] 
**TxStoreDb** | Pointer to **int32** |  | [optional] 
**TxCheckInputsPrefixHash** | Pointer to **int32** |  | [optional] 
**TxCheckInputsAttachmentCheck** | Pointer to **int32** |  | [optional] 
**TxCheckInputsLoop** | Pointer to **int32** |  | [optional] 
**TxCheckInputsLoopKimageCheck** | Pointer to **int32** |  | [optional] 
**TxCheckInputsLoopChInValSig** | Pointer to **int32** |  | [optional] 
**TxCheckInputsLoopScanOutputkeysGetItemSize** | Pointer to **int32** |  | [optional] 
**TxCheckInputsLoopScanOutputkeysRelativeToAbsolute** | Pointer to **int32** |  | [optional] 
**TxCheckInputsLoopScanOutputkeysLoop** | Pointer to **int32** |  | [optional] 
**TxCheckInputsLoopScanOutputkeysLoopGetSubitem** | Pointer to **int32** |  | [optional] 
**TxCheckInputsLoopScanOutputkeysLoopFindTx** | Pointer to **int32** |  | [optional] 
**TxCheckInputsLoopScanOutputkeysLoopHandleOutput** | Pointer to **int32** |  | [optional] 
**TxMixinCount** | Pointer to **int32** |  | [optional] 

## Methods

### NewTxProcessingPerformanceModel

`func NewTxProcessingPerformanceModel() *TxProcessingPerformanceModel`

NewTxProcessingPerformanceModel instantiates a new TxProcessingPerformanceModel object
This constructor will assign default values to properties that have it defined,
and makes sure properties required by API are set, but the set of arguments
will change when the set of required properties is changed

### NewTxProcessingPerformanceModelWithDefaults

`func NewTxProcessingPerformanceModelWithDefaults() *TxProcessingPerformanceModel`

NewTxProcessingPerformanceModelWithDefaults instantiates a new TxProcessingPerformanceModel object
This constructor will only assign default values to properties that have it defined,
but it doesn't guarantee that properties required by API are set

### GetTxCheckInputs

`func (o *TxProcessingPerformanceModel) GetTxCheckInputs() int32`

GetTxCheckInputs returns the TxCheckInputs field if non-nil, zero value otherwise.

### GetTxCheckInputsOk

`func (o *TxProcessingPerformanceModel) GetTxCheckInputsOk() (*int32, bool)`

GetTxCheckInputsOk returns a tuple with the TxCheckInputs field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTxCheckInputs

`func (o *TxProcessingPerformanceModel) SetTxCheckInputs(v int32)`

SetTxCheckInputs sets TxCheckInputs field to given value.

### HasTxCheckInputs

`func (o *TxProcessingPerformanceModel) HasTxCheckInputs() bool`

HasTxCheckInputs returns a boolean if a field has been set.

### GetTxAddOneTx

`func (o *TxProcessingPerformanceModel) GetTxAddOneTx() int32`

GetTxAddOneTx returns the TxAddOneTx field if non-nil, zero value otherwise.

### GetTxAddOneTxOk

`func (o *TxProcessingPerformanceModel) GetTxAddOneTxOk() (*int32, bool)`

GetTxAddOneTxOk returns a tuple with the TxAddOneTx field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTxAddOneTx

`func (o *TxProcessingPerformanceModel) SetTxAddOneTx(v int32)`

SetTxAddOneTx sets TxAddOneTx field to given value.

### HasTxAddOneTx

`func (o *TxProcessingPerformanceModel) HasTxAddOneTx() bool`

HasTxAddOneTx returns a boolean if a field has been set.

### GetTxProcessExtra

`func (o *TxProcessingPerformanceModel) GetTxProcessExtra() int32`

GetTxProcessExtra returns the TxProcessExtra field if non-nil, zero value otherwise.

### GetTxProcessExtraOk

`func (o *TxProcessingPerformanceModel) GetTxProcessExtraOk() (*int32, bool)`

GetTxProcessExtraOk returns a tuple with the TxProcessExtra field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTxProcessExtra

`func (o *TxProcessingPerformanceModel) SetTxProcessExtra(v int32)`

SetTxProcessExtra sets TxProcessExtra field to given value.

### HasTxProcessExtra

`func (o *TxProcessingPerformanceModel) HasTxProcessExtra() bool`

HasTxProcessExtra returns a boolean if a field has been set.

### GetTxProcessAttachment

`func (o *TxProcessingPerformanceModel) GetTxProcessAttachment() int32`

GetTxProcessAttachment returns the TxProcessAttachment field if non-nil, zero value otherwise.

### GetTxProcessAttachmentOk

`func (o *TxProcessingPerformanceModel) GetTxProcessAttachmentOk() (*int32, bool)`

GetTxProcessAttachmentOk returns a tuple with the TxProcessAttachment field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTxProcessAttachment

`func (o *TxProcessingPerformanceModel) SetTxProcessAttachment(v int32)`

SetTxProcessAttachment sets TxProcessAttachment field to given value.

### HasTxProcessAttachment

`func (o *TxProcessingPerformanceModel) HasTxProcessAttachment() bool`

HasTxProcessAttachment returns a boolean if a field has been set.

### GetTxProcessInputs

`func (o *TxProcessingPerformanceModel) GetTxProcessInputs() int32`

GetTxProcessInputs returns the TxProcessInputs field if non-nil, zero value otherwise.

### GetTxProcessInputsOk

`func (o *TxProcessingPerformanceModel) GetTxProcessInputsOk() (*int32, bool)`

GetTxProcessInputsOk returns a tuple with the TxProcessInputs field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTxProcessInputs

`func (o *TxProcessingPerformanceModel) SetTxProcessInputs(v int32)`

SetTxProcessInputs sets TxProcessInputs field to given value.

### HasTxProcessInputs

`func (o *TxProcessingPerformanceModel) HasTxProcessInputs() bool`

HasTxProcessInputs returns a boolean if a field has been set.

### GetTxPushGlobalIndex

`func (o *TxProcessingPerformanceModel) GetTxPushGlobalIndex() int32`

GetTxPushGlobalIndex returns the TxPushGlobalIndex field if non-nil, zero value otherwise.

### GetTxPushGlobalIndexOk

`func (o *TxProcessingPerformanceModel) GetTxPushGlobalIndexOk() (*int32, bool)`

GetTxPushGlobalIndexOk returns a tuple with the TxPushGlobalIndex field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTxPushGlobalIndex

`func (o *TxProcessingPerformanceModel) SetTxPushGlobalIndex(v int32)`

SetTxPushGlobalIndex sets TxPushGlobalIndex field to given value.

### HasTxPushGlobalIndex

`func (o *TxProcessingPerformanceModel) HasTxPushGlobalIndex() bool`

HasTxPushGlobalIndex returns a boolean if a field has been set.

### GetTxCheckExist

`func (o *TxProcessingPerformanceModel) GetTxCheckExist() int32`

GetTxCheckExist returns the TxCheckExist field if non-nil, zero value otherwise.

### GetTxCheckExistOk

`func (o *TxProcessingPerformanceModel) GetTxCheckExistOk() (*int32, bool)`

GetTxCheckExistOk returns a tuple with the TxCheckExist field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTxCheckExist

`func (o *TxProcessingPerformanceModel) SetTxCheckExist(v int32)`

SetTxCheckExist sets TxCheckExist field to given value.

### HasTxCheckExist

`func (o *TxProcessingPerformanceModel) HasTxCheckExist() bool`

HasTxCheckExist returns a boolean if a field has been set.

### GetTxPrintLog

`func (o *TxProcessingPerformanceModel) GetTxPrintLog() int32`

GetTxPrintLog returns the TxPrintLog field if non-nil, zero value otherwise.

### GetTxPrintLogOk

`func (o *TxProcessingPerformanceModel) GetTxPrintLogOk() (*int32, bool)`

GetTxPrintLogOk returns a tuple with the TxPrintLog field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTxPrintLog

`func (o *TxProcessingPerformanceModel) SetTxPrintLog(v int32)`

SetTxPrintLog sets TxPrintLog field to given value.

### HasTxPrintLog

`func (o *TxProcessingPerformanceModel) HasTxPrintLog() bool`

HasTxPrintLog returns a boolean if a field has been set.

### GetTxPrapareAppend

`func (o *TxProcessingPerformanceModel) GetTxPrapareAppend() int32`

GetTxPrapareAppend returns the TxPrapareAppend field if non-nil, zero value otherwise.

### GetTxPrapareAppendOk

`func (o *TxProcessingPerformanceModel) GetTxPrapareAppendOk() (*int32, bool)`

GetTxPrapareAppendOk returns a tuple with the TxPrapareAppend field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTxPrapareAppend

`func (o *TxProcessingPerformanceModel) SetTxPrapareAppend(v int32)`

SetTxPrapareAppend sets TxPrapareAppend field to given value.

### HasTxPrapareAppend

`func (o *TxProcessingPerformanceModel) HasTxPrapareAppend() bool`

HasTxPrapareAppend returns a boolean if a field has been set.

### GetTxAppend

`func (o *TxProcessingPerformanceModel) GetTxAppend() int32`

GetTxAppend returns the TxAppend field if non-nil, zero value otherwise.

### GetTxAppendOk

`func (o *TxProcessingPerformanceModel) GetTxAppendOk() (*int32, bool)`

GetTxAppendOk returns a tuple with the TxAppend field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTxAppend

`func (o *TxProcessingPerformanceModel) SetTxAppend(v int32)`

SetTxAppend sets TxAppend field to given value.

### HasTxAppend

`func (o *TxProcessingPerformanceModel) HasTxAppend() bool`

HasTxAppend returns a boolean if a field has been set.

### GetTxAppendRlWait

`func (o *TxProcessingPerformanceModel) GetTxAppendRlWait() int32`

GetTxAppendRlWait returns the TxAppendRlWait field if non-nil, zero value otherwise.

### GetTxAppendRlWaitOk

`func (o *TxProcessingPerformanceModel) GetTxAppendRlWaitOk() (*int32, bool)`

GetTxAppendRlWaitOk returns a tuple with the TxAppendRlWait field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTxAppendRlWait

`func (o *TxProcessingPerformanceModel) SetTxAppendRlWait(v int32)`

SetTxAppendRlWait sets TxAppendRlWait field to given value.

### HasTxAppendRlWait

`func (o *TxProcessingPerformanceModel) HasTxAppendRlWait() bool`

HasTxAppendRlWait returns a boolean if a field has been set.

### GetTxAppendIsExpired

`func (o *TxProcessingPerformanceModel) GetTxAppendIsExpired() int32`

GetTxAppendIsExpired returns the TxAppendIsExpired field if non-nil, zero value otherwise.

### GetTxAppendIsExpiredOk

`func (o *TxProcessingPerformanceModel) GetTxAppendIsExpiredOk() (*int32, bool)`

GetTxAppendIsExpiredOk returns a tuple with the TxAppendIsExpired field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTxAppendIsExpired

`func (o *TxProcessingPerformanceModel) SetTxAppendIsExpired(v int32)`

SetTxAppendIsExpired sets TxAppendIsExpired field to given value.

### HasTxAppendIsExpired

`func (o *TxProcessingPerformanceModel) HasTxAppendIsExpired() bool`

HasTxAppendIsExpired returns a boolean if a field has been set.

### GetTxStoreDb

`func (o *TxProcessingPerformanceModel) GetTxStoreDb() int32`

GetTxStoreDb returns the TxStoreDb field if non-nil, zero value otherwise.

### GetTxStoreDbOk

`func (o *TxProcessingPerformanceModel) GetTxStoreDbOk() (*int32, bool)`

GetTxStoreDbOk returns a tuple with the TxStoreDb field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTxStoreDb

`func (o *TxProcessingPerformanceModel) SetTxStoreDb(v int32)`

SetTxStoreDb sets TxStoreDb field to given value.

### HasTxStoreDb

`func (o *TxProcessingPerformanceModel) HasTxStoreDb() bool`

HasTxStoreDb returns a boolean if a field has been set.

### GetTxCheckInputsPrefixHash

`func (o *TxProcessingPerformanceModel) GetTxCheckInputsPrefixHash() int32`

GetTxCheckInputsPrefixHash returns the TxCheckInputsPrefixHash field if non-nil, zero value otherwise.

### GetTxCheckInputsPrefixHashOk

`func (o *TxProcessingPerformanceModel) GetTxCheckInputsPrefixHashOk() (*int32, bool)`

GetTxCheckInputsPrefixHashOk returns a tuple with the TxCheckInputsPrefixHash field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTxCheckInputsPrefixHash

`func (o *TxProcessingPerformanceModel) SetTxCheckInputsPrefixHash(v int32)`

SetTxCheckInputsPrefixHash sets TxCheckInputsPrefixHash field to given value.

### HasTxCheckInputsPrefixHash

`func (o *TxProcessingPerformanceModel) HasTxCheckInputsPrefixHash() bool`

HasTxCheckInputsPrefixHash returns a boolean if a field has been set.

### GetTxCheckInputsAttachmentCheck

`func (o *TxProcessingPerformanceModel) GetTxCheckInputsAttachmentCheck() int32`

GetTxCheckInputsAttachmentCheck returns the TxCheckInputsAttachmentCheck field if non-nil, zero value otherwise.

### GetTxCheckInputsAttachmentCheckOk

`func (o *TxProcessingPerformanceModel) GetTxCheckInputsAttachmentCheckOk() (*int32, bool)`

GetTxCheckInputsAttachmentCheckOk returns a tuple with the TxCheckInputsAttachmentCheck field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTxCheckInputsAttachmentCheck

`func (o *TxProcessingPerformanceModel) SetTxCheckInputsAttachmentCheck(v int32)`

SetTxCheckInputsAttachmentCheck sets TxCheckInputsAttachmentCheck field to given value.

### HasTxCheckInputsAttachmentCheck

`func (o *TxProcessingPerformanceModel) HasTxCheckInputsAttachmentCheck() bool`

HasTxCheckInputsAttachmentCheck returns a boolean if a field has been set.

### GetTxCheckInputsLoop

`func (o *TxProcessingPerformanceModel) GetTxCheckInputsLoop() int32`

GetTxCheckInputsLoop returns the TxCheckInputsLoop field if non-nil, zero value otherwise.

### GetTxCheckInputsLoopOk

`func (o *TxProcessingPerformanceModel) GetTxCheckInputsLoopOk() (*int32, bool)`

GetTxCheckInputsLoopOk returns a tuple with the TxCheckInputsLoop field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTxCheckInputsLoop

`func (o *TxProcessingPerformanceModel) SetTxCheckInputsLoop(v int32)`

SetTxCheckInputsLoop sets TxCheckInputsLoop field to given value.

### HasTxCheckInputsLoop

`func (o *TxProcessingPerformanceModel) HasTxCheckInputsLoop() bool`

HasTxCheckInputsLoop returns a boolean if a field has been set.

### GetTxCheckInputsLoopKimageCheck

`func (o *TxProcessingPerformanceModel) GetTxCheckInputsLoopKimageCheck() int32`

GetTxCheckInputsLoopKimageCheck returns the TxCheckInputsLoopKimageCheck field if non-nil, zero value otherwise.

### GetTxCheckInputsLoopKimageCheckOk

`func (o *TxProcessingPerformanceModel) GetTxCheckInputsLoopKimageCheckOk() (*int32, bool)`

GetTxCheckInputsLoopKimageCheckOk returns a tuple with the TxCheckInputsLoopKimageCheck field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTxCheckInputsLoopKimageCheck

`func (o *TxProcessingPerformanceModel) SetTxCheckInputsLoopKimageCheck(v int32)`

SetTxCheckInputsLoopKimageCheck sets TxCheckInputsLoopKimageCheck field to given value.

### HasTxCheckInputsLoopKimageCheck

`func (o *TxProcessingPerformanceModel) HasTxCheckInputsLoopKimageCheck() bool`

HasTxCheckInputsLoopKimageCheck returns a boolean if a field has been set.

### GetTxCheckInputsLoopChInValSig

`func (o *TxProcessingPerformanceModel) GetTxCheckInputsLoopChInValSig() int32`

GetTxCheckInputsLoopChInValSig returns the TxCheckInputsLoopChInValSig field if non-nil, zero value otherwise.

### GetTxCheckInputsLoopChInValSigOk

`func (o *TxProcessingPerformanceModel) GetTxCheckInputsLoopChInValSigOk() (*int32, bool)`

GetTxCheckInputsLoopChInValSigOk returns a tuple with the TxCheckInputsLoopChInValSig field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTxCheckInputsLoopChInValSig

`func (o *TxProcessingPerformanceModel) SetTxCheckInputsLoopChInValSig(v int32)`

SetTxCheckInputsLoopChInValSig sets TxCheckInputsLoopChInValSig field to given value.

### HasTxCheckInputsLoopChInValSig

`func (o *TxProcessingPerformanceModel) HasTxCheckInputsLoopChInValSig() bool`

HasTxCheckInputsLoopChInValSig returns a boolean if a field has been set.

### GetTxCheckInputsLoopScanOutputkeysGetItemSize

`func (o *TxProcessingPerformanceModel) GetTxCheckInputsLoopScanOutputkeysGetItemSize() int32`

GetTxCheckInputsLoopScanOutputkeysGetItemSize returns the TxCheckInputsLoopScanOutputkeysGetItemSize field if non-nil, zero value otherwise.

### GetTxCheckInputsLoopScanOutputkeysGetItemSizeOk

`func (o *TxProcessingPerformanceModel) GetTxCheckInputsLoopScanOutputkeysGetItemSizeOk() (*int32, bool)`

GetTxCheckInputsLoopScanOutputkeysGetItemSizeOk returns a tuple with the TxCheckInputsLoopScanOutputkeysGetItemSize field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTxCheckInputsLoopScanOutputkeysGetItemSize

`func (o *TxProcessingPerformanceModel) SetTxCheckInputsLoopScanOutputkeysGetItemSize(v int32)`

SetTxCheckInputsLoopScanOutputkeysGetItemSize sets TxCheckInputsLoopScanOutputkeysGetItemSize field to given value.

### HasTxCheckInputsLoopScanOutputkeysGetItemSize

`func (o *TxProcessingPerformanceModel) HasTxCheckInputsLoopScanOutputkeysGetItemSize() bool`

HasTxCheckInputsLoopScanOutputkeysGetItemSize returns a boolean if a field has been set.

### GetTxCheckInputsLoopScanOutputkeysRelativeToAbsolute

`func (o *TxProcessingPerformanceModel) GetTxCheckInputsLoopScanOutputkeysRelativeToAbsolute() int32`

GetTxCheckInputsLoopScanOutputkeysRelativeToAbsolute returns the TxCheckInputsLoopScanOutputkeysRelativeToAbsolute field if non-nil, zero value otherwise.

### GetTxCheckInputsLoopScanOutputkeysRelativeToAbsoluteOk

`func (o *TxProcessingPerformanceModel) GetTxCheckInputsLoopScanOutputkeysRelativeToAbsoluteOk() (*int32, bool)`

GetTxCheckInputsLoopScanOutputkeysRelativeToAbsoluteOk returns a tuple with the TxCheckInputsLoopScanOutputkeysRelativeToAbsolute field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTxCheckInputsLoopScanOutputkeysRelativeToAbsolute

`func (o *TxProcessingPerformanceModel) SetTxCheckInputsLoopScanOutputkeysRelativeToAbsolute(v int32)`

SetTxCheckInputsLoopScanOutputkeysRelativeToAbsolute sets TxCheckInputsLoopScanOutputkeysRelativeToAbsolute field to given value.

### HasTxCheckInputsLoopScanOutputkeysRelativeToAbsolute

`func (o *TxProcessingPerformanceModel) HasTxCheckInputsLoopScanOutputkeysRelativeToAbsolute() bool`

HasTxCheckInputsLoopScanOutputkeysRelativeToAbsolute returns a boolean if a field has been set.

### GetTxCheckInputsLoopScanOutputkeysLoop

`func (o *TxProcessingPerformanceModel) GetTxCheckInputsLoopScanOutputkeysLoop() int32`

GetTxCheckInputsLoopScanOutputkeysLoop returns the TxCheckInputsLoopScanOutputkeysLoop field if non-nil, zero value otherwise.

### GetTxCheckInputsLoopScanOutputkeysLoopOk

`func (o *TxProcessingPerformanceModel) GetTxCheckInputsLoopScanOutputkeysLoopOk() (*int32, bool)`

GetTxCheckInputsLoopScanOutputkeysLoopOk returns a tuple with the TxCheckInputsLoopScanOutputkeysLoop field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTxCheckInputsLoopScanOutputkeysLoop

`func (o *TxProcessingPerformanceModel) SetTxCheckInputsLoopScanOutputkeysLoop(v int32)`

SetTxCheckInputsLoopScanOutputkeysLoop sets TxCheckInputsLoopScanOutputkeysLoop field to given value.

### HasTxCheckInputsLoopScanOutputkeysLoop

`func (o *TxProcessingPerformanceModel) HasTxCheckInputsLoopScanOutputkeysLoop() bool`

HasTxCheckInputsLoopScanOutputkeysLoop returns a boolean if a field has been set.

### GetTxCheckInputsLoopScanOutputkeysLoopGetSubitem

`func (o *TxProcessingPerformanceModel) GetTxCheckInputsLoopScanOutputkeysLoopGetSubitem() int32`

GetTxCheckInputsLoopScanOutputkeysLoopGetSubitem returns the TxCheckInputsLoopScanOutputkeysLoopGetSubitem field if non-nil, zero value otherwise.

### GetTxCheckInputsLoopScanOutputkeysLoopGetSubitemOk

`func (o *TxProcessingPerformanceModel) GetTxCheckInputsLoopScanOutputkeysLoopGetSubitemOk() (*int32, bool)`

GetTxCheckInputsLoopScanOutputkeysLoopGetSubitemOk returns a tuple with the TxCheckInputsLoopScanOutputkeysLoopGetSubitem field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTxCheckInputsLoopScanOutputkeysLoopGetSubitem

`func (o *TxProcessingPerformanceModel) SetTxCheckInputsLoopScanOutputkeysLoopGetSubitem(v int32)`

SetTxCheckInputsLoopScanOutputkeysLoopGetSubitem sets TxCheckInputsLoopScanOutputkeysLoopGetSubitem field to given value.

### HasTxCheckInputsLoopScanOutputkeysLoopGetSubitem

`func (o *TxProcessingPerformanceModel) HasTxCheckInputsLoopScanOutputkeysLoopGetSubitem() bool`

HasTxCheckInputsLoopScanOutputkeysLoopGetSubitem returns a boolean if a field has been set.

### GetTxCheckInputsLoopScanOutputkeysLoopFindTx

`func (o *TxProcessingPerformanceModel) GetTxCheckInputsLoopScanOutputkeysLoopFindTx() int32`

GetTxCheckInputsLoopScanOutputkeysLoopFindTx returns the TxCheckInputsLoopScanOutputkeysLoopFindTx field if non-nil, zero value otherwise.

### GetTxCheckInputsLoopScanOutputkeysLoopFindTxOk

`func (o *TxProcessingPerformanceModel) GetTxCheckInputsLoopScanOutputkeysLoopFindTxOk() (*int32, bool)`

GetTxCheckInputsLoopScanOutputkeysLoopFindTxOk returns a tuple with the TxCheckInputsLoopScanOutputkeysLoopFindTx field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTxCheckInputsLoopScanOutputkeysLoopFindTx

`func (o *TxProcessingPerformanceModel) SetTxCheckInputsLoopScanOutputkeysLoopFindTx(v int32)`

SetTxCheckInputsLoopScanOutputkeysLoopFindTx sets TxCheckInputsLoopScanOutputkeysLoopFindTx field to given value.

### HasTxCheckInputsLoopScanOutputkeysLoopFindTx

`func (o *TxProcessingPerformanceModel) HasTxCheckInputsLoopScanOutputkeysLoopFindTx() bool`

HasTxCheckInputsLoopScanOutputkeysLoopFindTx returns a boolean if a field has been set.

### GetTxCheckInputsLoopScanOutputkeysLoopHandleOutput

`func (o *TxProcessingPerformanceModel) GetTxCheckInputsLoopScanOutputkeysLoopHandleOutput() int32`

GetTxCheckInputsLoopScanOutputkeysLoopHandleOutput returns the TxCheckInputsLoopScanOutputkeysLoopHandleOutput field if non-nil, zero value otherwise.

### GetTxCheckInputsLoopScanOutputkeysLoopHandleOutputOk

`func (o *TxProcessingPerformanceModel) GetTxCheckInputsLoopScanOutputkeysLoopHandleOutputOk() (*int32, bool)`

GetTxCheckInputsLoopScanOutputkeysLoopHandleOutputOk returns a tuple with the TxCheckInputsLoopScanOutputkeysLoopHandleOutput field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTxCheckInputsLoopScanOutputkeysLoopHandleOutput

`func (o *TxProcessingPerformanceModel) SetTxCheckInputsLoopScanOutputkeysLoopHandleOutput(v int32)`

SetTxCheckInputsLoopScanOutputkeysLoopHandleOutput sets TxCheckInputsLoopScanOutputkeysLoopHandleOutput field to given value.

### HasTxCheckInputsLoopScanOutputkeysLoopHandleOutput

`func (o *TxProcessingPerformanceModel) HasTxCheckInputsLoopScanOutputkeysLoopHandleOutput() bool`

HasTxCheckInputsLoopScanOutputkeysLoopHandleOutput returns a boolean if a field has been set.

### GetTxMixinCount

`func (o *TxProcessingPerformanceModel) GetTxMixinCount() int32`

GetTxMixinCount returns the TxMixinCount field if non-nil, zero value otherwise.

### GetTxMixinCountOk

`func (o *TxProcessingPerformanceModel) GetTxMixinCountOk() (*int32, bool)`

GetTxMixinCountOk returns a tuple with the TxMixinCount field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTxMixinCount

`func (o *TxProcessingPerformanceModel) SetTxMixinCount(v int32)`

SetTxMixinCount sets TxMixinCount field to given value.

### HasTxMixinCount

`func (o *TxProcessingPerformanceModel) HasTxMixinCount() bool`

HasTxMixinCount returns a boolean if a field has been set.


[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


