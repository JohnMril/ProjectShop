
from requests import Session
from requests.auth import HTTPBasicAuth  # or HTTPDigestAuth, or OAuth1, etc.
from zeep import Client
from zeep.transports import Transport
import xml.etree.ElementTree as ET
import copy
from tqdm import tqdm


session = Session()
login = "TC0039568|UNICOMPS"
passwd = "123456"
session.auth = HTTPBasicAuth(login, passwd)

client = Client(
    "https://apitest.merlion.com/re/mlservice3?wsdl",
    transport=Transport(session=session),
)

cat_id = "All"
catalog = client.service.getCatalog(cat_id)
# shipmentMethods = client.service.getCatalog("All")
# print(shipmentMethods)


