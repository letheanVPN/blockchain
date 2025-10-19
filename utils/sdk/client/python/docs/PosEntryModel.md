# PosEntryModel


## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**amount** | **int** |  | [optional] 
**g_index** | **int** |  | [optional] 
**keyimage** | **str** |  | [optional] 
**block_timestamp** | **int** |  | [optional] 
**stake_unlock_time** | **int** |  | [optional] 
**tx_id** | **str** |  | [optional] 
**tx_out_index** | **int** |  | [optional] 
**wallet_index** | **int** |  | [optional] 

## Example

```python
from lthn.models.pos_entry_model import PosEntryModel

# TODO update the JSON string below
json = "{}"
# create an instance of PosEntryModel from a JSON string
pos_entry_model_instance = PosEntryModel.from_json(json)
# print the JSON string representation of the object
print(PosEntryModel.to_json())

# convert the object into a dict
pos_entry_model_dict = pos_entry_model_instance.to_dict()
# create an instance of PosEntryModel from a dict
pos_entry_model_from_dict = PosEntryModel.from_dict(pos_entry_model_dict)
```
[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


