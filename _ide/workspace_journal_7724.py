# 2025-09-03T10:53:44.679610
import vitis

client = vitis.create_client()
client.set_workspace(path="workspace_soc")

vitis.dispose()

