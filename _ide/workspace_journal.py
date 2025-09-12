# 2025-09-12T12:28:39.674870
import vitis

client = vitis.create_client()
client.set_workspace(path="workspace_soc")

platform = client.get_component(name="platform_btn_fnd")
status = platform.build()

comp = client.get_component(name="app_btn_fnd")
comp.build()

platform = client.get_component(name="platform_intc")
status = platform.build()

comp = client.get_component(name="app_intc")
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

platform = client.create_platform_component(name = "platform_intc_stopwatch",hw_design = "$COMPONENT_LOCATION/../../workspace_vivado/basys3_exam/soc_intc_stopwatch_wrapper.xsa",os = "standalone",cpu = "microblaze_riscv_0",domain_name = "standalone_microblaze_riscv_0")

comp = client.create_app_component(name="app_intc_stopwatch",platform = "$COMPONENT_LOCATION/../platform_intc_stopwatch/export/platform_intc_stopwatch/platform_intc_stopwatch.xpfm",domain = "standalone_microblaze_riscv_0",template = "hello_world")

platform = client.get_component(name="platform_intc_stopwatch")
status = platform.build()

comp = client.get_component(name="app_intc_stopwatch")
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

platform = client.get_component(name="platform_stop_watch")
status = platform.build()

comp = client.get_component(name="app_stop_watch")
comp.build()

platform = client.get_component(name="platform_intc_stopwatch")
status = platform.build()

comp = client.get_component(name="app_intc_stopwatch")
comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

platform = client.create_platform_component(name = "platform_pwm_4096step",hw_design = "$COMPONENT_LOCATION/../../workspace_vivado/basys3_exam/soc_pwm_4096step_wrapper.xsa",os = "standalone",cpu = "microblaze_riscv_0",domain_name = "standalone_microblaze_riscv_0")

comp = client.create_app_component(name="app_pwm_4096step",platform = "$COMPONENT_LOCATION/../platform_pwm_4096step/export/platform_pwm_4096step/platform_pwm_4096step.xpfm",domain = "standalone_microblaze_riscv_0",template = "hello_world")

platform = client.get_component(name="platform_pwm_4096step")
status = platform.build()

comp = client.get_component(name="app_pwm_4096step")
comp.build()

status = platform.build()

comp.build()

