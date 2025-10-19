# TransactionDetailsModel


## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**amount** | **int** |  | [optional] 
**attachments** | [**List[TransactionAttachmentModel]**](TransactionAttachmentModel.md) |  | [optional] 
**blob** | **str** |  | [optional] 
**blob_size** | **int** |  | [optional] 
**extra** | [**List[TransactionExtraModel]**](TransactionExtraModel.md) |  | [optional] 
**fee** | **int** |  | [optional] 
**id** | **str** |  | [optional] 
**ins** | [**List[TransactionInputModel]**](TransactionInputModel.md) |  | [optional] 
**keeper_block** | **int** |  | [optional] 
**object_in_json** | **str** |  | [optional] 
**outs** | [**List[TransactionOutputModel]**](TransactionOutputModel.md) |  | [optional] 
**pub_key** | **str** |  | [optional] 
**timestamp** | **int** |  | [optional] 

## Example

```python
from lthn.models.transaction_details_model import TransactionDetailsModel

# TODO update the JSON string below
json = "{}"
# create an instance of TransactionDetailsModel from a JSON string
transaction_details_model_instance = TransactionDetailsModel.from_json(json)
# print the JSON string representation of the object
print(TransactionDetailsModel.to_json())

# convert the object into a dict
transaction_details_model_dict = transaction_details_model_instance.to_dict()
# create an instance of TransactionDetailsModel from a dict
transaction_details_model_from_dict = TransactionDetailsModel.from_dict(transaction_details_model_dict)
```
[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


