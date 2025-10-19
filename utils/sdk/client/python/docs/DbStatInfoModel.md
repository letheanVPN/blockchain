# DbStatInfoModel


## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**tx_count** | **int** |  | [optional] 
**write_tx_count** | **int** |  | [optional] 
**map_size** | **int** |  | [optional] 

## Example

```python
from lthn.models.db_stat_info_model import DbStatInfoModel

# TODO update the JSON string below
json = "{}"
# create an instance of DbStatInfoModel from a JSON string
db_stat_info_model_instance = DbStatInfoModel.from_json(json)
# print the JSON string representation of the object
print(DbStatInfoModel.to_json())

# convert the object into a dict
db_stat_info_model_dict = db_stat_info_model_instance.to_dict()
# create an instance of DbStatInfoModel from a dict
db_stat_info_model_from_dict = DbStatInfoModel.from_dict(db_stat_info_model_dict)
```
[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


