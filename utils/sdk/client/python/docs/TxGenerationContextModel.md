# TxGenerationContextModel


## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**asset_ids** | **List[str]** |  | [optional] 
**blinded_asset_ids** | **List[str]** |  | [optional] 
**amount_commitments** | **List[str]** |  | [optional] 
**asset_id_blinding_masks** | **List[str]** |  | [optional] 
**amounts** | **List[str]** |  | [optional] 
**amount_blinding_masks** | **List[str]** |  | [optional] 
**pseudo_outs_blinded_asset_ids** | **List[str]** |  | [optional] 
**pseudo_outs_plus_real_out_blinding_masks** | **List[str]** |  | [optional] 
**real_zc_ins_asset_ids** | **List[str]** |  | [optional] 
**zc_input_amounts** | **List[int]** |  | [optional] 
**pseudo_out_amount_commitments_sum** | **str** |  | [optional] 
**pseudo_out_amount_blinding_masks_sum** | **str** |  | [optional] 
**real_in_asset_id_blinding_mask_x_amount_sum** | **str** |  | [optional] 
**amount_commitments_sum** | **str** |  | [optional] 
**amount_blinding_masks_sum** | **str** |  | [optional] 
**asset_id_blinding_mask_x_amount_sum** | **str** |  | [optional] 
**ao_asset_id** | **str** |  | [optional] 
**ao_asset_id_pt** | **str** |  | [optional] 
**ao_amount_commitment** | **str** |  | [optional] 
**ao_amount_blinding_mask** | **str** |  | [optional] 
**ao_commitment_in_outputs** | **bool** |  | [optional] 
**tx_key_pub** | **str** |  | [optional] 
**tx_key_sec** | **str** |  | [optional] 
**tx_pub_key_p** | **str** |  | [optional] 

## Example

```python
from lthn.models.tx_generation_context_model import TxGenerationContextModel

# TODO update the JSON string below
json = "{}"
# create an instance of TxGenerationContextModel from a JSON string
tx_generation_context_model_instance = TxGenerationContextModel.from_json(json)
# print the JSON string representation of the object
print(TxGenerationContextModel.to_json())

# convert the object into a dict
tx_generation_context_model_dict = tx_generation_context_model_instance.to_dict()
# create an instance of TxGenerationContextModel from a dict
tx_generation_context_model_from_dict = TxGenerationContextModel.from_dict(tx_generation_context_model_dict)
```
[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


