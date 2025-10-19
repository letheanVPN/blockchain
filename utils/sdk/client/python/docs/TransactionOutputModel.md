# TransactionOutputModel


## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**amount** | **int** |  | [optional] 
**global_index** | **int** |  | [optional] 
**is_spent** | **bool** |  | [optional] 
**minimum_sigs** | **int** |  | [optional] 
**pub_keys** | **List[str]** |  | [optional] 

## Example

```python
from lthn.models.transaction_output_model import TransactionOutputModel

# TODO update the JSON string below
json = "{}"
# create an instance of TransactionOutputModel from a JSON string
transaction_output_model_instance = TransactionOutputModel.from_json(json)
# print the JSON string representation of the object
print(TransactionOutputModel.to_json())

# convert the object into a dict
transaction_output_model_dict = transaction_output_model_instance.to_dict()
# create an instance of TransactionOutputModel from a dict
transaction_output_model_from_dict = TransactionOutputModel.from_dict(transaction_output_model_dict)
```
[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


