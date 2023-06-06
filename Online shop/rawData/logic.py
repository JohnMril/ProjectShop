from requests import Session
from requests.auth import HTTPBasicAuth  # or HTTPDigestAuth, or OAuth1, etc.
from zeep import Client
from zeep.transports import Transport
from zeep.helpers import serialize_object
import xml.etree.ElementTree as ET
import copy
from tqdm import tqdm


session = Session()
login = "sale471W1"
passwd = "J3G5Nw2aYt15"
session.auth = HTTPBasicAuth(login, passwd)

client = Client(
    "https://3logic.ru/ws/soap/soap.php?wsdl",
    transport=Transport(session=session),
)
# 108439382
print("end0")

category = client.service.getProductList(108439382, False, False)

print(category)














# root = ET.fromstring(categoryList.Result)
# categories_id = []

# for child in root:
#     categories_id.append(child.attrib["category_id"])
    
# tree = ET.ElementTree(root)

# print(categories_id)
# print(tree)