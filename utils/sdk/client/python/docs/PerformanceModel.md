# PerformanceModel


## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**block_processing** | [**BlockProcessingPerformanceModel**](BlockProcessingPerformanceModel.md) |  | [optional] 
**tx_processing** | [**TxProcessingPerformanceModel**](TxProcessingPerformanceModel.md) |  | [optional] 
**tx_pool** | [**TxPoolPerformanceModel**](TxPoolPerformanceModel.md) |  | [optional] 
**db_stat_info** | [**DbStatInfoModel**](DbStatInfoModel.md) |  | [optional] 

## Example

```python
from lthn.models.performance_model import PerformanceModel

# TODO update the JSON string below
json = "{}"
# create an instance of PerformanceModel from a JSON string
performance_model_instance = PerformanceModel.from_json(json)
# print the JSON string representation of the object
print(PerformanceModel.to_json())

# convert the object into a dict
performance_model_dict = performance_model_instance.to_dict()
# create an instance of PerformanceModel from a dict
performance_model_from_dict = PerformanceModel.from_dict(performance_model_dict)
```
[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


