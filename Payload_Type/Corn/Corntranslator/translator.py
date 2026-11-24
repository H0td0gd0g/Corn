import json
import binascii

from mythic_container.TranslationBase import *
from Corntranslator.commands_from_agent import *
from Corntranslator.commands_from_c2 import *
from Corntranslator.config import *


class Corntranslator(TranslationContainer):
    name = "Corntranslator"
    description = "translater for Corn agent"
    author = "@H0td0gd0g"

    async def generate_keys(self, inputMsg: TrGenerateEncryptionKeysMessage) -> TrGenerateEncryptionKeysMessageResponse:
        response = TrGenerateEncryptionKeysMessageResponse(Success=True)
        response.DecryptionKey = b""
        response.EncryptionKey = b""
        return response

    async def translate_to_c2_format(self, inputMsg: TrMythicC2ToCustomMessageFormatMessage) -> TrMythicC2ToCustomMessageFormatMessageResponse:
        response = TrMythicC2ToCustomMessageFormatMessageResponse(Success=True)
        print("C2 --> Agent :" + json.dumps(inputMsg.Message))
        if inputMsg.Message["action"] == "get_tasking":
            print("get_tasking response")
            response.Message = responseGetTasking(inputMsg.Message["tasks"])
        elif inputMsg.Message["action"] == "checkin":
            print("checkin response")
            response.Message = responseCheckin(inputMsg.Message["id"])
        return response

    async def translate_from_c2_format(self, inputMsg: TrCustomMessageToMythicC2FormatMessage) -> TrCustomMessageToMythicC2FormatMessageResponse:
        response = TrCustomMessageToMythicC2FormatMessageResponse(Success=True)
        print("Agent --> C2 :" + binascii.hexlify(inputMsg.Message).decode('utf-8'))
        # Mythic already base64-decodes the HTTP body and strips the UUID before calling us.
        # inputMsg.Message = raw bytes starting at the action byte
        # inputMsg.UUID    = the agent UUID extracted by Mythic
        data = inputMsg.Message
        response.Message = dispatchAction(data, inputMsg.UUID)
        return response
