# TransactionInputModel


## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**amount** | **int** |  | [optional] 
**global_indexes** | **List[int]** |  | [optional] 
**htlc_origin** | **str** |  | [optional] 
**kimage_or_ms_id** | **str** |  | [optional] 
**multisig_count** | **int** |  | [optional] 

## Example

```python
from lthn.models.transaction_input_model import TransactionInputModel

# TODO update the JSON string below
json = "{}"
# create an instance of TransactionInputModel from a JSON string
transaction_input_model_instance = TransactionInputModel.from_json(json)
# print the JSON string representation of the object
print(TransactionInputModel.to_json())

# convert the object into a dict
transaction_input_model_dict = transaction_input_model_instance.to_dict()
# create an instance of TransactionInputModel from a dict
transaction_input_model_from_dict = TransactionInputModel.from_dict(transaction_input_model_dict)
```
[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


