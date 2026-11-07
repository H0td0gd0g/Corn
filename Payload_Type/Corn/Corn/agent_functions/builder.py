import pathlib
from mythic_container.PayloadBuilder import *
from mythic_container.MythicCommandBase import *
from mythic_container.MythicRPC import *
import json
import tempfile
from distutils.dir_util import copy_tree
import asyncio


class CornAgent(PayloadType):
    
    # meta data
    name = "Corn"
    file_extension = "exe"
    author = "@H0td0gd0g"
    supported_os = [SupportedOS]
    wrapper = False
    supports_dynamic_loading = False
    
    # Communication Settings
    c2_profiles = ["http"]
    mythic_encrypts = False
    translation_container = "Corntranslator"
    
    # build param
    build_parameters = [
        BuildParameter(
            name = "output",
            parameter_type=BuildParameterType.ChooseOne,
            description="Choose output format",
            choices = ["exe"],
            default_value="exe"
        ),
    ]
    agent_path = pathlib.Path(".") / "Corn"
    agent_code_path = agent_path / "agent_code"
    agent_icon_path = agent_path / "agent_functions" / "corn.png"
    
    build_steps = [
        BuildStep("Gathering Files",       "Creating script payload"),
        BuildStep("Applying configuration","Updating configuration constants"),
        BuildStep("Compiling",             "Compiling with mingw"),
    ]
    
    async def build(self) -> BuildResponse:
        resp = BuildResponse(status=BuildStatus.Success)
        config = {
            "payload_uuid": self.uuid,
            "callback_host": "",
            "USER_AGENT": "",
            "httpMethod": "POST",
            "post_uri": "",
            "headers": [],
            "callback_port": 80,
            "ssl":False,
            "proxyEnabled": False,
            "proxy_host": "",
            "proxy_user": "",
            "proxy_pass": "",
        }
        stdout_err = ""
        for c2 in self.c2info:
            profile = c2.get_c2profile()
            for key, val in c2.get_parameters_dict().items():
                if isinstance(val, dict) and 'enc_key' in val:
                    stdout_err += "Setting {} to {}".format(key, val["enc_key"] if val["enc_key"] is not None else "")
                    encKey = base64.b64decode(val["enc_key"]) if val["enc_key"] is not None else ""
                else:
                    config[key] = val
            break
        
        if "https://" in config["callback_host"]:
            config["ssl"] = True
        
        config["callback_host"] = config["callback_host"].replace("https://", "").replace("http://","")
        
        if config["proxy_host"] != "":
            config["proxyEnabled"] = True
            
        await SendMythicRPCPayloadUpdatebuildStep(MythicRPCPayloadUpdateBuildStepMessage(
                PayloadUUID=self.uuid,
                StepName="Gathering Files",
                StepStdout="Found all files for payload",
                StepSuccess=True
            ))
        agent_build_path = tempfile.TemporaryDirectory(suffix=self.uuid)
        copy_tree(str(self.agent_code_path), agent_build_path.name)

        await SendMythicRPCPayloadUpdatebuildStep(MythicRPCPayloadUpdateBuildStepMessage(
            PayloadUUID=self.uuid,
            StepName="Applying configuration",
            StepStdout="All configuration setting applied",
            StepSuccess=True
        ))
        with open(agent_build_path.name+"/ceos/include/Config.h", "r+") as f:
            content = f.read()
            content = content.replace("%UUID%", Config["payload_uuid"])
            content = content.replace("%HOSTNAME%", Config["callback_host"])
            content = content.replace("%ENDPOINT%", Config["post_uri"])
            if Config["ssl"]:
                content = content.replace("%SSL%", "TRUE")
            else:
                content = content.replace("%SSL%", "FALSE")
                content = content.replace("%PORT%", str(Config["callback_port"]))
                content = content.replace("%SLEEPTIME%", str(Config["callback_interval"]))
                content = content.replace("%USERAGENT%", Config["USER_AGENT"])
                content = content.replace("%PROXYURL%", Config["proxy_host"])
            if Config["proxyEnabled"]:
                content = content.replace("%PROXYENABLED%", "TRUE")
            else:
                content = content.replace("%PROXYENABLED%", "FALSE")
            f.seek(0)
            f.write(content)
            f.truncate()
        command = "make -C {} exe".format(agent_build_path.name+"/")
        filename = agent_build_path.name + "/Corn/build/Corn.exe"
        proc = await asyncio.create_subprocess_shell(command, stdout=asyncio.subprocess.PIPE,stderr=asyncio.subprocess.PIPE)

        stdout, stderr = await proc.communicate()
        print(stdout)
        print(stderr)

        await SendMythicRPCPayloadUpdatebuildStep(MythicRPCPayloadUpdateBuildStepMessage(
            PayloadUUID=self.uuid,
            StepName="Compiling",
            StepStdout="Successfuly compiled Ra",
            StepSuccess=True
        ))
        build_msg = ""
        resp.payload = open(filename, "rb").read()

        return resp
        