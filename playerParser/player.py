import math
import sys
import os
from Crypto.Cipher import AES
sys.path.append(f'{os.path.dirname(os.path.dirname(__file__))}/')
from utils.binaryreader import BinaryReader

class Parse:
    def __init__(self, path):
        self.file = open(path, 'rb')
        key = 'h3y_gUyZ'.encode('utf-16-le')
        cryptor = AES.new(key, AES.MODE_CBC, key)
        self.player_data = BinaryReader(cryptor.decrypt(self.file.read()))
        self.version = self.player_data.int32()
        self.relogic = self.player_data.string(7)
        self.savefile_type = self.player_data.uint8()
        self.revision = self.player_data.uint32()
        self.is_favorite = self.player_data.uint64() != 0
        self.name = self.player_data.string()
        self.difficulty = self.player_data.uint8()
        self.player_time = self.player_data.read_until(self.player_data.tell() + 8)
        self.hair = self.player_data.int32()
        self.hair_dye = self.player_data.uint8()
        self.hide_visual = self.player_data.read_until(self.player_data.tell() + 1)
        self.hide_misc = self.player_data.read_until(self.player_data.tell() + 2)
        self.skin_variant = self.player_data.uint8();
        self.stat_life = self.player_data.int32();
        self.stat_lifeMax = self.player_data.int32();
        self.stat_mana = self.player_data.int32();
        self.stat_manaMax = self.player_data.int32();
        self.extra_accessory = self.player_data.bool();
        self.downed_DD2_event_any_difficulty = self.player_data.bool();
        self.tax_money = self.player_data.int32();
        self.hair_color = self.player_data.RGB();
        self.skin_color = self.player_data.RGB();
        self.eye_color = self.player_data.RGB();
        self.shirt_color = self.player_data.RGB();
        self.under_shirt_color = self.player_data.RGB();
        self.pants_color = self.player_data.RGB();
        self.shoe_color = self.player_data.RGB();
        
        
        
