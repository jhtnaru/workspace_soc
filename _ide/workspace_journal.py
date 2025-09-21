# 2025-09-21T16:40:41.614974
import vitis

client = vitis.create_client()
client.set_workspace(path="workspace_soc")

client.delete_component(name="app_servo180")

client.delete_component(name="platform_servo180")

platform = client.create_platform_component(name = "platform_servo180",hw_design = "$COMPONENT_LOCATION/../../workspace_vivado/basys3_exam/soc_servo180_wrapper.xsa",os = "standalone",cpu = "microblaze_riscv_0",domain_name = "standalone_microblaze_riscv_0")

comp = client.create_app_component(name="app_servo180",platform = "$COMPONENT_LOCATION/../platform_servo180/export/platform_servo180/platform_servo180.xpfm",domain = "standalone_microblaze_riscv_0",template = "hello_world")

platform = client.get_component(name="platform_servo180")
status = platform.build()

comp = client.get_component(name="app_servo180")
comp.build()

status = platform.build()

comp.build()

vitis.dispose()

