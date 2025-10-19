# MaintainersInfoModel


## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**ver_major** | **int** |  | [optional] 
**ver_minor** | **int** |  | [optional] 
**ver_revision** | **int** |  | [optional] 
**build_no** | **int** |  | [optional] 
**mode** | **int** |  | [optional] 

## Example

```python
from lthn.models.maintainers_info_model import MaintainersInfoModel

# TODO update the JSON string below
json = "{}"
# create an instance of MaintainersInfoModel from a JSON string
maintainers_info_model_instance = MaintainersInfoModel.from_json(json)
# print the JSON string representation of the object
print(MaintainersInfoModel.to_json())

# convert the object into a dict
maintainers_info_model_dict = maintainers_info_model_instance.to_dict()
# create an instance of MaintainersInfoModel from a dict
maintainers_info_model_from_dict = MaintainersInfoModel.from_dict(maintainers_info_model_dict)
```
[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


