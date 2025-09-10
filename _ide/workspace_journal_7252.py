# 2025-09-09T15:38:31.887854
import vitis

client = vitis.create_client()
client.set_workspace(path="workspace_soc")

platform = client.create_platform_component(name = "platform_stop_watch",hw_design = "$COMPONENT_LOCATION/../../workspace_vivado/basys3_exam/soc_stop_watch_wrapper.xsa",os = "standalone",cpu = "microblaze_riscv_0",domain_name = "standalone_microblaze_riscv_0")

comp = client.create_app_component(name="app_stop_watch",platform = "$COMPONENT_LOCATION/../platform_stop_watch/export/platform_stop_watch/platform_stop_watch.xpfm",domain = "standalone_microblaze_riscv_0",template = "hello_world")

platform = client.get_component(name="platform_stop_watch")
status = platform.build()

comp = client.get_component(name="app_stop_watch")
comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

platform = client.get_component(name="platform_txtlcd")
status = platform.build()

comp = client.get_component(name="app_txtlcd")
comp.build()

vitis.dispose()

