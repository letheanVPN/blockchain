# VersionModel


## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**version** | **str** |  | [optional] 
**version_long** | **str** |  | [optional] 
**major** | **str** |  | [optional] 
**minor** | **str** |  | [optional] 
**revision** | **str** |  | [optional] 

## Example

```python
from lthn.models.version_model import VersionModel

# TODO update the JSON string below
json = "{}"
# create an instance of VersionModel from a JSON string
version_model_instance = VersionModel.from_json(json)
# print the JSON string representation of the object
print(VersionModel.to_json())

# convert the object into a dict
version_model_dict = version_model_instance.to_dict()
# create an instance of VersionModel from a dict
version_model_from_dict = VersionModel.from_dict(version_model_dict)
```
[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


