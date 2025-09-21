# 2025-09-21T15:14:10.702166
import vitis

client = vitis.create_client()
client.set_workspace(path="workspace_soc")

platform = client.get_component(name="platform_stepper")
status = platform.build()

comp = client.get_component(name="app_stepper")
comp.build()

client.delete_component(name="app_stepper")

client.delete_component(name="platform_stepper")

platform = client.create_platform_component(name = "platform_stepper",hw_design = "$COMPONENT_LOCATION/../../workspace_vivado/basys3_exam/soc_stepper_wrapper.xsa",os = "standalone",cpu = "microblaze_riscv_0",domain_name = "standalone_microblaze_riscv_0")

comp = client.create_app_component(name="app_stepper",platform = "$COMPONENT_LOCATION/../platform_stepper/export/platform_stepper/platform_stepper.xpfm",domain = "standalone_microblaze_riscv_0",template = "hello_world")

status = platform.build()

comp.build()

status = platform.build()

comp.build()

vitis.dispose()

