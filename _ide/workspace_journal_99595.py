# 2025-09-02T18:54:35.357946
import vitis

client = vitis.create_client()
client.set_workspace(path="workspace_soc")

vitis.dispose()

