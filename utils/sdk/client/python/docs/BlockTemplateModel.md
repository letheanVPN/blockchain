# BlockTemplateModel


## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**blocktemplate_blob** | **str** |  | [optional] 
**difficulty** | **str** |  | [optional] 
**height** | **int** |  | [optional] 
**miner_tx_tgc** | [**TxGenerationContextModel**](TxGenerationContextModel.md) |  | [optional] 
**block_reward_without_fee** | **int** |  | [optional] 
**block_reward** | **int** |  | [optional] 
**txs_fee** | **int** |  | [optional] 
**prev_hash** | **str** |  | [optional] 
**seed** | **str** |  | [optional] 

## Example

```python
from lthn.models.block_template_model import BlockTemplateModel

# TODO update the JSON string below
json = "{}"
# create an instance of BlockTemplateModel from a JSON string
block_template_model_instance = BlockTemplateModel.from_json(json)
# print the JSON string representation of the object
print(BlockTemplateModel.to_json())

# convert the object into a dict
block_template_model_dict = block_template_model_instance.to_dict()
# create an instance of BlockTemplateModel from a dict
block_template_model_from_dict = BlockTemplateModel.from_dict(block_template_model_dict)
```
[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


