# BlockTemplateRequestModel


## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**miner_address** | **str** |  | [optional] 
**stakeholder_address** | **str** |  | [optional] 
**ex_nonce** | **str** |  | [optional] 
**pos_block** | **bool** |  | [optional] 
**ignore_pow_ts_check** | **bool** |  | [optional] 
**pe** | [**PosEntryModel**](PosEntryModel.md) |  | [optional] 
**explicit_txs** | **List[str]** |  | [optional] 

## Example

```python
from lthn.models.block_template_request_model import BlockTemplateRequestModel

# TODO update the JSON string below
json = "{}"
# create an instance of BlockTemplateRequestModel from a JSON string
block_template_request_model_instance = BlockTemplateRequestModel.from_json(json)
# print the JSON string representation of the object
print(BlockTemplateRequestModel.to_json())

# convert the object into a dict
block_template_request_model_dict = block_template_request_model_instance.to_dict()
# create an instance of BlockTemplateRequestModel from a dict
block_template_request_model_from_dict = BlockTemplateRequestModel.from_dict(block_template_request_model_dict)
```
[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


