# This is a sample Python script.

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.







import requests

url_to_the_file = 'https://services.it4profit.com/product/ru/722/PriceAvail.xml?USERNAME=sale@unicomps.ru&PASSWORD=unicomps21'
r = requests.get(url_to_the_file)
with open('asbisProducts.txt', 'wb') as f:
    f.write(r.content)

def print_hi(name):
    # Use a breakpoint in the code line below to debug your script.
    print(f'Has been download, {name}')  # Press Ctrl+F8 to toggle the breakpoint.


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    print_hi('ASBIS')

# See PyCharm help at https://www.jetbrains.com/help/pycharm/
