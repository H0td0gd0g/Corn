#from mywebhook.webhook import *
import mythic_container
import asyncio
import aio_pika
import Corn
# import websocket.mythic.c2_functions.websocket
from Corntranslator.translator import *
from mythic_container.config import settings


async def create_on_start_queues():
    await asyncio.sleep(5)
    try:
        conn = await aio_pika.connect_robust(
            host=settings.get("rabbitmq_host", "127.0.0.1"),
            port=settings.get("rabbitmq_port", 5672),
            login="mythic_user",
            password=settings.get("rabbitmq_password", "rabbitmq_password"),
            virtualhost="mythic_vhost",
        )
        channel = await conn.channel()
        await channel.declare_queue("corn_container_on_start", durable=False)
        await channel.declare_queue("Corntranslator_container_on_start", durable=False)
        print("[+] on_start queues created")
        await conn.close()
    except Exception as e:
        print(f"[-] on_start queue creation failed: {e}")


loop = asyncio.get_event_loop()
loop.run_until_complete(mythic_container.mythic_service.start_services())
asyncio.ensure_future(create_on_start_queues())
loop.run_forever()