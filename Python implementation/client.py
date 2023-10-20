import redis
import argparse
import random
import time

def main(message, topic):
    r = redis.Redis(host='localhost', port=6379, db=0)
    while True:
        full_message = f'[{args.id}] {message} {topic}'
        r.publish('chatroom', full_message)
        sleep_time = random.uniform(1, 5)
        time.sleep(sleep_time+3)

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Redis Pub/Sub Client')
    parser.add_argument('--id', required=True, help='Client ID')
    parser.add_argument('--message', required=True, help='Message to publish')
    parser.add_argument('--topic', required=True, help='Topic: Tiasense or veerasense')
    args = parser.parse_args()

    main(args.message, args.topic)
