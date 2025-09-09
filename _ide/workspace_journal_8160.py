# 2025-09-08T09:38:47.377265
import vitis

client = vitis.create_client()
client.set_workspace(path="workspace_soc")

platform = client.create_platform_component(name = "platform_dht11_i2c",hw_design = "$COMPONENT_LOCATION/../../workspace_vivado/basys3_exam/soc_dht11_i2c_wrapper.xsa",os = "standalone",cpu = "microblaze_riscv_0",domain_name = "standalone_microblaze_riscv_0")

comp = client.create_app_component(name="app_dht11_i2c",platform = "$COMPONENT_LOCATION/../platform_dht11_i2c/export/platform_dht11_i2c/platform_dht11_i2c.xpfm",domain = "standalone_microblaze_riscv_0",template = "hello_world")

platform = client.get_component(name="platform_dht11_i2c")
status = platform.build()

comp = client.get_component(name="app_dht11_i2c")
comp.build()

platform = client.get_component(name="platform_dht11")
status = platform.build()

comp = client.get_component(name="app_dht11")
comp.build()

platform = client.get_component(name="platform_dht11_i2c")
status = platform.build()

comp = client.get_component(name="app_dht11_i2c")
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

platform = client.get_component(name="platform_dht11")
status = platform.build()

comp = client.get_component(name="app_dht11")
comp.build()

platform = client.get_component(name="platform_dht11_i2c")
status = platform.build()

comp = client.get_component(name="app_dht11_i2c")
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

platform = client.create_platform_component(name = "platform_txtlcd",hw_design = "$COMPONENT_LOCATION/../../workspace_vivado/basys3_exam/soc_txtlcd_wrapper.xsa",os = "standalone",cpu = "microblaze_riscv_0",domain_name = "standalone_microblaze_riscv_0")

comp = client.create_app_component(name="app_txtlcd",platform = "$COMPONENT_LOCATION/../platform_txtlcd/export/platform_txtlcd/platform_txtlcd.xpfm",domain = "standalone_microblaze_riscv_0",template = "hello_world")

platform = client.get_component(name="platform_txtlcd")
status = platform.build()

comp = client.get_component(name="app_txtlcd")
comp.build()

status = platform.build()

comp.build()

platform = client.get_component(name="platform_dht11_i2c")
status = platform.build()

comp = client.get_component(name="app_dht11_i2c")
comp.build()

platform = client.get_component(name="platform_txtlcd")
status = platform.build()

comp = client.get_component(name="app_txtlcd")
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

platform = client.create_platform_component(name = "platform_keypad",hw_design = "$COMPONENT_LOCATION/../../workspace_vivado/basys3_exam/soc_keypad_wrapper.xsa",os = "standalone",cpu = "microblaze_riscv_0",domain_name = "standalone_microblaze_riscv_0")

comp = client.create_app_component(name="app_keypad",platform = "$COMPONENT_LOCATION/../platform_keypad/export/platform_keypad/platform_keypad.xpfm",domain = "standalone_microblaze_riscv_0",template = "hello_world")

platform = client.get_component(name="platform_keypad")
status = platform.build()

comp = client.get_component(name="app_keypad")
comp.build()

status = platform.build()

comp.build()

client.delete_component(name="app_keypad")

client.delete_component(name="platform_keypad")

platform = client.create_platform_component(name = "platform_keypad",hw_design = "$COMPONENT_LOCATION/../../workspace_vivado/basys3_exam/soc_keypad_wrapper.xsa",os = "standalone",cpu = "microblaze_riscv_0",domain_name = "standalone_microblaze_riscv_0")

comp = client.create_app_component(name="app_keypad",platform = "$COMPONENT_LOCATION/../platform_keypad/export/platform_keypad/platform_keypad.xpfm",domain = "standalone_microblaze_riscv_0",template = "hello_world")

status = platform.build()

comp.build()

status = platform.build()

comp.build()

vitis.dispose()

