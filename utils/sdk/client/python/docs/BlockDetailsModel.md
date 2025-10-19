# BlockDetailsModel


## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**actual_timestamp** | **int** |  | [optional] 
**already_generated_coins** | **str** |  | [optional] 
**base_reward** | **int** |  | [optional] 
**blob** | **str** |  | [optional] 
**block_cumulative_size** | **int** |  | [optional] 
**block_tself_size** | **int** |  | [optional] 
**cumulative_diff_adjusted** | **str** |  | [optional] 
**cumulative_diff_precise** | **str** |  | [optional] 
**difficulty** | **str** |  | [optional] 
**effective_fee_median** | **int** |  | [optional] 
**height** | **int** |  | [optional] 
**id** | **str** |  | [optional] 
**is_orphan** | **bool** |  | [optional] 
**miner_text_info** | **str** |  | [optional] 
**object_in_json** | **str** |  | [optional] 
**penalty** | **int** |  | [optional] 
**pow_seed** | **str** |  | [optional] 
**prev_id** | **str** |  | [optional] 
**summary_reward** | **int** |  | [optional] 
**this_block_fee_median** | **int** |  | [optional] 
**timestamp** | **int** |  | [optional] 
**total_fee** | **int** |  | [optional] 
**total_txs_size** | **int** |  | [optional] 
**transactions_details** | [**List[TransactionDetailsModel]**](TransactionDetailsModel.md) |  | [optional] 
**type** | **int** |  | [optional] 

## Example

```python
from lthn.models.block_details_model import BlockDetailsModel

# TODO update the JSON string below
json = "{}"
# create an instance of BlockDetailsModel from a JSON string
block_details_model_instance = BlockDetailsModel.from_json(json)
# print the JSON string representation of the object
print(BlockDetailsModel.to_json())

# convert the object into a dict
block_details_model_dict = block_details_model_instance.to_dict()
# create an instance of BlockDetailsModel from a dict
block_details_model_from_dict = BlockDetailsModel.from_dict(block_details_model_dict)
```
[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


