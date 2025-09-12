# 2025-09-10T16:58:51.293001
import vitis

client = vitis.create_client()
client.set_workspace(path="workspace_soc")

platform = client.get_component(name="platform_watch")
status = platform.build()

comp = client.get_component(name="app_watch")
comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

vitis.dispose()

