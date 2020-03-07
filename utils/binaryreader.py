import struct
import uuid
import datetime
from utils.rect import Rect
from utils.data import Data


class BinaryReader:
    def __init__(self, data):
        self.data = data
        self.offset = 0
        
    def tell(self):
        return self.offset

    def bool(self):
        address = self.tell()
        self.offset += 1
        size = self.offset - address
        return Data(struct.unpack('?', self.data[address: self.offset])[0], address, size)

    def int8(self):
        address = self.tell()
        self.offset += 1
        size = self.offset - address
        return Data(struct.unpack('B', self.data[address: self.offset])[0], address, size)

    def uint8(self):
        address = self.tell()
        self.offset += 1
        size = self.offset - address
        return Data(struct.unpack('B', self.data[address: self.offset])[0], address, size)

    def int16(self):
        address = self.tell()
        self.offset += 2
        size = self.offset - address
        return Data(struct.unpack('h', self.data[address: self.offset])[0], address, size)

    def uint16(self):
        address = self.tell()
        self.offset += 2
        size = self.offset - address
        return Data(struct.unpack('H', self.data[address: self.offset])[0], address, size)

    def int32(self):
        address = self.tell()
        self.offset += 4
        size = self.offset - address
        return Data(struct.unpack('i', self.data[address: self.offset])[0], address, size)

    def uint32(self):
        address = self.tell()
        self.offset += 4
        size = self.offset - address
        return Data(struct.unpack('I', self.data[address: self.offset])[0], address, size)

    def int64(self):
        address = self.tell()
        self.offset += 8
        size = self.offset - address
        return Data(struct.unpack('q', self.data[address: self.offset])[0], address, size)

    def uint64(self):
        address = self.tell()
        self.offset += 8
        size = self.offset - address
        return Data(struct.unpack('Q', self.data[address: self.offset])[0], address, size)

    def single(self):
        address = self.tell()
        self.offset += 4
        size = self.offset - address        
        return Data(struct.unpack('f', self.data[address: self.offset])[0], address, size)

    def double(self):
        address = self.tell()
        self.offset += 8
        size = self.offset - address
        return Data(struct.unpack('d', self.data[address: self.offset])[0], address, size)

    def bits(self):
        address = self.tell()
        self.offset += 1
        size = self.offset - address
        data = Data(struct.unpack('B', self.data[address: self.offset])[0], address, size)
        return (bool(data.value & 0b0000_0001),
                bool(data.value & 0b0000_0010),
                bool(data.value & 0b0000_0100),
                bool(data.value & 0b0000_1000),
                bool(data.value & 0b0001_0000),
                bool(data.value & 0b0010_0000),
                bool(data.value & 0b0100_0000),
                bool(data.value & 0b1000_0000))

    def rect(self):
        address = self.tell()
        self.offset += 16
        size = self.offset - address
        left, right, top, bottom = Data(struct.unpack('iiii', self.data[address: self.offset]), address, size).value
        return Rect(left, right, top, bottom)

    def uleb128(self):
        times = 0
        value = 0
        more = True
        while more:
            byte = self.uint8().value
            shifted_byte = (byte & 0b0111_1111) << (7 * times)
            times += 1
            value += shifted_byte
            more = bool(byte & 0b1000_0000)
        return value

    def string(self, size=None):
        if size is None:
            size = self.uleb128()
        address = self.tell()
        self.offset += size
        size = self.offset - address
        return Data(str(self.data[address: self.offset], encoding='latin1'), address, size)

    def uuid(self):
        address = self.tell()
        self.offset += 16
        size = self.offset - address
        uuid_bytes = Data(self.data[address: self.offset], address, size)
        return uuid_bytes

    def datetime(self):
        address = self.tell()
        self.offset += 8
        size = self.offset - address
        datetime_bytes = Data(self.data[address: self.offset], address, size)
        return datetime_bytes
        
    def RGB(self):
        return [self.uint8(), self.uint8(), self.uint8()]

    def read_until(self, size):
        data = bytearray()
        if self.tell() > size:
            pass
        address = self.tell()
        while self.tell() < size:
            self.offset += 1
            data += self.data[self.offset - 1: self.offset]
        return Data(data, address, size)

    def skip_until(self, address):
        self.offset = address