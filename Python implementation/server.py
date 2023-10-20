import redis
import pika

RABBITMQ_HOST = '192.168.10.60'
RABBITMQ_PORT = 5672

def handle_message(message):
    decoded_message = message['data'].decode()
    print(f"Received: {decoded_message}")

    credentials = pika.PlainCredentials('guest', 'guest')
    parameters = pika.ConnectionParameters(host=RABBITMQ_HOST, port=RABBITMQ_PORT, credentials=credentials)
    connection = pika.BlockingConnection(parameters)
    channel = connection.channel()


    exchange_name = 'topic-exchange'
    routing_key = 'general'

    if 'tiasense' in decoded_message:
        routing_key = 'tiasense'
    elif 'veerasense' in decoded_message:
        routing_key = 'veerasense'

    # Publish the message to RabbitMQ
    channel.basic_publish(exchange=exchange_name, routing_key=routing_key, body=decoded_message)
    print(f"Sent to RabbitMQ with routing key: {routing_key}")

    connection.close()

def main():
    r = redis.Redis(host='localhost', port=6379, db=0)
    pubsub = r.pubsub()
    pubsub.subscribe('chatroom')

    for message in pubsub.listen():
        if message['type'] == 'message':
            handle_message(message)

if __name__ == '__main__':
    main()
