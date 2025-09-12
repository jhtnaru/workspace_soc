# 2025-09-11T11:07:35.134306
import vitis

client = vitis.create_client()
client.set_workspace(path="workspace_soc")

platform = client.create_platform_component(name = "platform_pwm_4096step",hw_design = "$COMPONENT_LOCATION/../../workspace_vivado/basys3_exam/soc_pwm_led_servo_wrapper.xsa",os = "standalone",cpu = "microblaze_riscv_0",domain_name = "standalone_microblaze_riscv_0")

comp = client.create_app_component(name="app_pwm_4096step",platform = "$COMPONENT_LOCATION/../platform_pwm_4096step/export/platform_pwm_4096step/platform_pwm_4096step.xpfm",domain = "standalone_microblaze_riscv_0",template = "hello_world")

platform = client.get_component(name="platform_pwm_4096step")
status = platform.build()

comp = client.get_component(name="app_pwm_4096step")
comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

client.delete_component(name="app_pwm_4096step")

client.delete_component(name="platform_pwm_4096step")

platform = client.create_platform_component(name = "platform_pwm_4096step",hw_design = "$COMPONENT_LOCATION/../../workspace_vivado/basys3_exam/soc_pwm_4096step_wrapper.xsa",os = "standalone",cpu = "microblaze_riscv_0",domain_name = "standalone_microblaze_riscv_0")

comp = client.create_app_component(name="app_pwm_4096step",platform = "$COMPONENT_LOCATION/../platform_pwm_4096step/export/platform_pwm_4096step/platform_pwm_4096step.xpfm",domain = "standalone_microblaze_riscv_0",template = "hello_world")

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

client.delete_component(name="app_pwm_4096step")

client.delete_component(name="platform_pwm_4096step")

platform = client.create_platform_component(name = "platform_pwm_4096step",hw_design = "$COMPONENT_LOCATION/../../workspace_vivado/basys3_exam/soc_pwm_4096step_wrapper.xsa",os = "standalone",cpu = "microblaze_riscv_0",domain_name = "standalone_microblaze_riscv_0")

comp = client.create_app_component(name="app_pwm_4096step",platform = "$COMPONENT_LOCATION/../platform_pwm_4096step/export/platform_pwm_4096step/platform_pwm_4096step.xpfm",domain = "standalone_microblaze_riscv_0",template = "hello_world")

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

client.delete_component(name="app_pwm_4096step")

client.delete_component(name="platform_pwm_4096step")

platform = client.create_platform_component(name = "platform_pwm_4096step",hw_design = "$COMPONENT_LOCATION/../../workspace_vivado/basys3_exam/soc_pwm_4096step_wrapper.xsa",os = "standalone",cpu = "microblaze_riscv_0",domain_name = "standalone_microblaze_riscv_0")

comp = client.create_app_component(name="app_pwm_4096step",platform = "$COMPONENT_LOCATION/../platform_pwm_4096step/export/platform_pwm_4096step/platform_pwm_4096step.xpfm",domain = "standalone_microblaze_riscv_0",template = "hello_world")

status = platform.build()

comp.build()

status = platform.build()

comp.build()

client.delete_component(name="app_pwm_4096step")

client.delete_component(name="platform_pwm_4096step")

vitis.dispose()

