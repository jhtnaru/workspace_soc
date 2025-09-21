# 2025-09-21T10:17:46.515228
import vitis

client = vitis.create_client()
client.set_workspace(path="workspace_soc")

platform = client.create_platform_component(name = "platform_sensor_d",hw_design = "$COMPONENT_LOCATION/../../workspace_vivado/basys3_exam/soc_sensor_d_wrapper.xsa",os = "standalone",cpu = "microblaze_riscv_0",domain_name = "standalone_microblaze_riscv_0")

comp = client.create_app_component(name="app_sensor_d",platform = "$COMPONENT_LOCATION/../platform_sensor_d/export/platform_sensor_d/platform_sensor_d.xpfm",domain = "standalone_microblaze_riscv_0",template = "hello_world")

platform = client.get_component(name="platform_sensor_d")
status = platform.build()

comp = client.get_component(name="app_sensor_d")
comp.build()

status = platform.build()

comp.build()

vitis.dispose()

