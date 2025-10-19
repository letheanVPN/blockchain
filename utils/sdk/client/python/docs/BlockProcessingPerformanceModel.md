# BlockProcessingPerformanceModel


## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**block_processing_time_0** | **int** |  | [optional] 
**block_processing_time_1** | **int** |  | [optional] 
**target_calculating_time_2** | **int** |  | [optional] 
**longhash_calculating_time_3** | **int** |  | [optional] 
**all_txs_insert_time_5** | **int** |  | [optional] 
**etc_stuff_6** | **int** |  | [optional] 
**insert_time_4** | **int** |  | [optional] 
**raise_block_core_event** | **int** |  | [optional] 
**validate_miner_transaction_time** | **int** |  | [optional] 
**collect_rangeproofs_data_from_tx_time** | **int** |  | [optional] 
**verify_multiple_zc_outs_range_proofs_time** | **int** |  | [optional] 
**target_calculating_enum_blocks** | **int** |  | [optional] 
**target_calculating_calc** | **int** |  | [optional] 
**pos_validate_ki_search** | **int** |  | [optional] 
**pos_validate_get_out_keys_for_inputs** | **int** |  | [optional] 
**pos_validate_zvp** | **int** |  | [optional] 

## Example

```python
from lthn.models.block_processing_performance_model import BlockProcessingPerformanceModel

# TODO update the JSON string below
json = "{}"
# create an instance of BlockProcessingPerformanceModel from a JSON string
block_processing_performance_model_instance = BlockProcessingPerformanceModel.from_json(json)
# print the JSON string representation of the object
print(BlockProcessingPerformanceModel.to_json())

# convert the object into a dict
block_processing_performance_model_dict = block_processing_performance_model_instance.to_dict()
# create an instance of BlockProcessingPerformanceModel from a dict
block_processing_performance_model_from_dict = BlockProcessingPerformanceModel.from_dict(block_processing_performance_model_dict)
```
[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


