# 2025-09-20T15:45:42.464351
import vitis

client = vitis.create_client()
client.set_workspace(path="workspace_soc")

platform = client.create_platform_component(name = "platform_sensor_adc",hw_design = "$COMPONENT_LOCATION/../../workspace_project/Rooftop_Manage/soc_sensor_adc_wrapper.xsa",os = "standalone",cpu = "microblaze_riscv_0",domain_name = "standalone_microblaze_riscv_0")

comp = client.create_app_component(name="app_sensor_adc",platform = "$COMPONENT_LOCATION/../platform_sensor_adc/export/platform_sensor_adc/platform_sensor_adc.xpfm",domain = "standalone_microblaze_riscv_0",template = "hello_world")

platform = client.get_component(name="platform_sensor_adc")
status = platform.build()

comp = client.get_component(name="app_sensor_adc")
comp.build()

status = platform.build()

comp.build()

client.delete_component(name="app_sensor_adc")

client.delete_component(name="platform_sensor_adc")

platform = client.create_platform_component(name = "platform_sensor_adc",hw_design = "$COMPONENT_LOCATION/../../workspace_project/Rooftop_Manage/soc_sensor_adc_wrapper.xsa",os = "standalone",cpu = "microblaze_riscv_0",domain_name = "standalone_microblaze_riscv_0")

comp = client.create_app_component(name="app_sensor_adc",platform = "$COMPONENT_LOCATION/../platform_sensor_adc/export/platform_sensor_adc/platform_sensor_adc.xpfm",domain = "standalone_microblaze_riscv_0",template = "hello_world")

status = platform.build()

comp.build()

status = platform.build()

comp.build()

client.delete_component(name="app_sensor_adc")

client.delete_component(name="platform_sensor_adc")

platform = client.create_platform_component(name = "platform_sensor_adc",hw_design = "$COMPONENT_LOCATION/../../workspace_project/Rooftop_Manage/soc_sensor_adc_wrapper.xsa",os = "standalone",cpu = "microblaze_riscv_0",domain_name = "standalone_microblaze_riscv_0")

comp = client.create_app_component(name="app_sensor_adc",platform = "$COMPONENT_LOCATION/../platform_sensor_adc/export/platform_sensor_adc/platform_sensor_adc.xpfm",domain = "standalone_microblaze_riscv_0",template = "hello_world")

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

vitis.dispose()

