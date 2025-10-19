# TransactionExtraModel


## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**type** | **str** |  | [optional] 
**short_view** | **str** |  | [optional] 
**details_view** | **str** |  | [optional] 

## Example

```python
from lthn.models.transaction_extra_model import TransactionExtraModel

# TODO update the JSON string below
json = "{}"
# create an instance of TransactionExtraModel from a JSON string
transaction_extra_model_instance = TransactionExtraModel.from_json(json)
# print the JSON string representation of the object
print(TransactionExtraModel.to_json())

# convert the object into a dict
transaction_extra_model_dict = transaction_extra_model_instance.to_dict()
# create an instance of TransactionExtraModel from a dict
transaction_extra_model_from_dict = TransactionExtraModel.from_dict(transaction_extra_model_dict)
```
[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


