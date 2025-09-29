# 2025-09-22T13:55:20.354739
import vitis

client = vitis.create_client()
client.set_workspace(path="workspace_soc")

platform = client.get_component(name="platform_servo180")
status = platform.build()

comp = client.get_component(name="app_servo180")
comp.build()

vitis.dispose()

