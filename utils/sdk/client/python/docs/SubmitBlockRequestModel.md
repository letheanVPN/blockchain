# SubmitBlockRequestModel


## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**block_blob** | **str** |  | [optional] 

## Example

```python
from lthn.models.submit_block_request_model import SubmitBlockRequestModel

# TODO update the JSON string below
json = "{}"
# create an instance of SubmitBlockRequestModel from a JSON string
submit_block_request_model_instance = SubmitBlockRequestModel.from_json(json)
# print the JSON string representation of the object
print(SubmitBlockRequestModel.to_json())

# convert the object into a dict
submit_block_request_model_dict = submit_block_request_model_instance.to_dict()
# create an instance of SubmitBlockRequestModel from a dict
submit_block_request_model_from_dict = SubmitBlockRequestModel.from_dict(submit_block_request_model_dict)
```
[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


