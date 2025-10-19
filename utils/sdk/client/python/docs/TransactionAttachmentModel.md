# TransactionAttachmentModel


## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**type** | **str** |  | [optional] 
**short_view** | **str** |  | [optional] 
**details_view** | **str** |  | [optional] 

## Example

```python
from lthn.models.transaction_attachment_model import TransactionAttachmentModel

# TODO update the JSON string below
json = "{}"
# create an instance of TransactionAttachmentModel from a JSON string
transaction_attachment_model_instance = TransactionAttachmentModel.from_json(json)
# print the JSON string representation of the object
print(TransactionAttachmentModel.to_json())

# convert the object into a dict
transaction_attachment_model_dict = transaction_attachment_model_instance.to_dict()
# create an instance of TransactionAttachmentModel from a dict
transaction_attachment_model_from_dict = TransactionAttachmentModel.from_dict(transaction_attachment_model_dict)
```
[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


