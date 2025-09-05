# 2025-09-02T14:05:19.167817
import vitis

client = vitis.create_client()
client.set_workspace(path="workspace_soc")

platform = client.create_platform_component(name = "platform_led_sw",hw_design = "$COMPONENT_LOCATION/../../workspace_vivado/basys3_exam/soc_led_sw_wrapper.xsa",os = "standalone",cpu = "microblaze_riscv_0",domain_name = "standalone_microblaze_riscv_0")

comp = client.create_app_component(name="app_led_sw",platform = "$COMPONENT_LOCATION/../platform_led_sw/export/platform_led_sw/platform_led_sw.xpfm",domain = "standalone_microblaze_riscv_0",template = "hello_world")

client.delete_component(name="app_led_sw")

comp = client.create_app_component(name="app_led_sw",platform = "$COMPONENT_LOCATION/../platform_led_sw/export/platform_led_sw/platform_led_sw.xpfm",domain = "standalone_microblaze_riscv_0",template = "hello_world")

platform = client.get_component(name="platform_led_sw")
status = platform.build()

comp = client.get_component(name="app_led_sw")
comp.build()

status = comp.clean()

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

vitis.dispose()

