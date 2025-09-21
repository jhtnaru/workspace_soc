# 2025-09-21T11:17:54.061167
import vitis

client = vitis.create_client()
client.set_workspace(path="workspace_soc")

client.delete_component(name="app_sensor_d")

client.delete_component(name="platform_sensor_d")

platform = client.create_platform_component(name = "platform_sensor_dgt",hw_design = "$COMPONENT_LOCATION/../../workspace_vivado/basys3_exam/soc_sensor_dgt_wrapper.xsa",os = "standalone",cpu = "microblaze_riscv_0",domain_name = "standalone_microblaze_riscv_0")

comp = client.create_app_component(name="app_sensor_dgt",platform = "$COMPONENT_LOCATION/../platform_sensor_dgt/export/platform_sensor_dgt/platform_sensor_dgt.xpfm",domain = "standalone_microblaze_riscv_0",template = "hello_world")

platform = client.get_component(name="platform_sensor_dgt")
status = platform.build()

comp = client.get_component(name="app_sensor_dgt")
comp.build()

status = platform.build()

comp.build()

vitis.dispose()

