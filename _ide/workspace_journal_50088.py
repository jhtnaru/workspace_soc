# 2025-09-09T11:50:48.000851
import vitis

client = vitis.create_client()
client.set_workspace(path="workspace_soc")

vitis.dispose()

