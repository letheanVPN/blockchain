# TxPoolPerformanceModel


## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**tx_processing_time** | **int** |  | [optional] 
**check_inputs_types_supported_time** | **int** |  | [optional] 
**expiration_validate_time** | **int** |  | [optional] 
**validate_amount_time** | **int** |  | [optional] 
**validate_alias_time** | **int** |  | [optional] 
**check_keyimages_ws_ms_time** | **int** |  | [optional] 
**check_inputs_time** | **int** |  | [optional] 
**begin_tx_time** | **int** |  | [optional] 
**update_db_time** | **int** |  | [optional] 
**db_commit_time** | **int** |  | [optional] 
**check_post_hf4_balance** | **int** |  | [optional] 

## Example

```python
from lthn.models.tx_pool_performance_model import TxPoolPerformanceModel

# TODO update the JSON string below
json = "{}"
# create an instance of TxPoolPerformanceModel from a JSON string
tx_pool_performance_model_instance = TxPoolPerformanceModel.from_json(json)
# print the JSON string representation of the object
print(TxPoolPerformanceModel.to_json())

# convert the object into a dict
tx_pool_performance_model_dict = tx_pool_performance_model_instance.to_dict()
# create an instance of TxPoolPerformanceModel from a dict
tx_pool_performance_model_from_dict = TxPoolPerformanceModel.from_dict(tx_pool_performance_model_dict)
```
[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


