import sys
import os
import math
sys.path.append(f'{os.path.dirname(os.path.dirname(__file__))}/')
from utils.binaryreader import BinaryReader
from core.world import WorldParserCore


class Parse:
    def __init__(self, path):
        file = open(path, 'rb')
        meso_file_path = f'{os.path.dirname(__file__)}/tiles.dat'
        meso_file = open(meso_file_path, 'wb')
        self.world_data = BinaryReader(file.read())
        self.version = self.world_data.int32()
        self.relogic = self.world_data.string(7)
        self.savefile_type = self.world_data.uint8()
        self.revision = self.world_data.uint32()
        self.is_favorite = self.world_data.uint64() != 0

        self.pointers = [self.world_data.int32() for _ in range(self.world_data.int16().value)]
        tileframeimportant_size = math.ceil(self.world_data.int16().value / 8)
        self.tileframeimportant = []
        for _ in range(tileframeimportant_size):
            current_bit = self.world_data.bits()
            self.tileframeimportant.extend(current_bit)
        
        self.world_data.read_until(self.pointers[0].value)
        self.name = self.world_data.string()
        self.world_data.read_until(self.world_data.tell() + 20)
        self.world_size_y = self.world_data.int32()
        self.world_size_x = self.world_data.int32()

        self.world_data.read_until(self.pointers[1].value)
        meso_file.write(self.world_data.data[self.world_data.tell(): ])
        meso_file.close()
        self.world_tiles = WorldParserCore.ParseTiles(meso_file_path, self.world_size_x.value, self.world_size_y.value)
            
        file.close()       
