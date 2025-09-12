# 2025-09-12T09:30:31.409827
import vitis

client = vitis.create_client()
client.set_workspace(path="workspace_soc")

platform = client.create_platform_component(name = "platform_pwm",hw_design = "$COMPONENT_LOCATION/../../workspace_vivado/basys3_exam/soc_pwm_wrapper.xsa",os = "standalone",cpu = "microblaze_riscv_0",domain_name = "standalone_microblaze_riscv_0")

comp = client.create_app_component(name="app_pwm",platform = "$COMPONENT_LOCATION/../platform_pwm/export/platform_pwm/platform_pwm.xpfm",domain = "standalone_microblaze_riscv_0",template = "hello_world")

platform = client.get_component(name="platform_pwm")
status = platform.build()

comp = client.get_component(name="app_pwm")
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

client.delete_component(name="app_pwm")

client.delete_component(name="platform_pwm")

platform = client.create_platform_component(name = "platform_pwm_5ea",hw_design = "$COMPONENT_LOCATION/../../workspace_vivado/basys3_exam/soc_pwm_wrapper.xsa",os = "standalone",cpu = "microblaze_riscv_0",domain_name = "standalone_microblaze_riscv_0")

comp = client.create_app_component(name="app_pwm_5ea",platform = "$COMPONENT_LOCATION/../platform_pwm_5ea/export/platform_pwm_5ea/platform_pwm_5ea.xpfm",domain = "standalone_microblaze_riscv_0",template = "hello_world")

platform = client.get_component(name="platform_pwm_5ea")
status = platform.build()

comp = client.get_component(name="app_pwm_5ea")
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

platform = client.create_platform_component(name = "platform_intc",hw_design = "$COMPONENT_LOCATION/../../workspace_vivado/basys3_exam/soc_intc_wrapper.xsa",os = "standalone",cpu = "microblaze_riscv_0",domain_name = "standalone_microblaze_riscv_0")

comp = client.create_app_component(name="app_intc",platform = "$COMPONENT_LOCATION/../platform_intc/export/platform_intc/platform_intc.xpfm",domain = "standalone_microblaze_riscv_0",template = "hello_world")

platform = client.get_component(name="platform_intc")
status = platform.build()

comp = client.get_component(name="app_intc")
comp.build()

platform = client.get_component(name="platform_pwm_5ea")
status = platform.build()

comp = client.get_component(name="app_pwm_5ea")
comp.build()

platform = client.get_component(name="platform_intc")
status = platform.build()

comp = client.get_component(name="app_intc")
comp.build()

vitis.dispose()

