import random
import string

def generate_random_word(min_length=3, max_length=14):
    length = random.randint(min_length, max_length)
    word = ''.join(random.choices(string.ascii_lowercase, k=length))
    return word

def generate_random_words(num_words=1001, filename='test.txt'):
    with open(filename, 'w') as file:
        for _ in range(num_words):
            word = generate_random_word()
            file.write(word + '\n')

generate_random_words()
