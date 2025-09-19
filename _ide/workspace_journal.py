# 2025-09-19T09:38:03.843825
import vitis

client = vitis.create_client()
client.set_workspace(path="workspace_soc")

platform = client.get_component(name="platform_rtc_read")
status = platform.build()

comp = client.get_component(name="app_rtc_read")
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

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

platform = client.create_platform_component(name = "platform_stepper",hw_design = "$COMPONENT_LOCATION/../../workspace_vivado/basys3_exam/soc_stepper_wrapper.xsa",os = "standalone",cpu = "microblaze_riscv_0",domain_name = "standalone_microblaze_riscv_0")

comp = client.create_app_component(name="app_stepper",platform = "$COMPONENT_LOCATION/../platform_stepper/export/platform_stepper/platform_stepper.xpfm",domain = "standalone_microblaze_riscv_0",template = "hello_world")

platform = client.get_component(name="platform_stepper")
status = platform.build()

comp = client.get_component(name="app_stepper")
comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

platform = client.create_platform_component(name = "platform_fan_motor",hw_design = "$COMPONENT_LOCATION/../../workspace_vivado/basys3_exam/soc_fan_motor_wrapper.xsa",os = "standalone",cpu = "microblaze_riscv_0",domain_name = "standalone_microblaze_riscv_0")

comp = client.create_app_component(name="app_fan_motor",platform = "$COMPONENT_LOCATION/../platform_fan_motor/export/platform_fan_motor/platform_fan_motor.xpfm",domain = "standalone_microblaze_riscv_0",template = "hello_world")

platform = client.get_component(name="platform_fan_motor")
status = platform.build()

comp = client.get_component(name="app_fan_motor")
comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

