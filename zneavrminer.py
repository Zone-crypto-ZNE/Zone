import serial
import time
import sys
import os
from hashlib import sha256

# Cross-platform port detection
def get_arduino_port():
    port = input("Enter Arduino port (e.g., COM3 for Windows, /dev/ttyUSB0 for Linux/Mac): ")
    return port

# Mine a block with SHA-256 PoW, targeting ~1 hour
def mine_block(wallet_address, block_num, difficulty=22):
    print(f"Mining block {block_num} for wallet {wallet_address}...")
    start_time = time.time()
    nonce = 0
    target = "0" * difficulty  # Hash must start with N zeros
    
    while True:
        data = f"{wallet_address}{block_num}{nonce}".encode()
        hash_result = sha256(data).hexdigest()
        if hash_result.startswith(target):
            elapsed = time.time() - start_time
            print(f"Block {block_num} mined in {elapsed/3600:.2f} hours! Hash: {hash_result}")
            return hash_result[:56]  # Truncate to 56 bytes for EEPROM
        nonce += 1
        if nonce % 1000000 == 0:  # Progress update
            print(f"Still mining block {block_num}... nonce: {nonce}")

# Main script
def main():
    print("Zone AVR Miner")
    action = input("Are you adding an Arduino (A) or adding blocks (B)? [A/B]: ").upper()

    if action == "A":
        wallet_address = input("Enter your wallet address: ")
        port = get_arduino_port()
        arduino_id = input("Enter a unique ID for this Arduino (no duplicates in wallet): ")
        
        try:
            with serial.Serial(port, 115200, timeout=1) as ser:
                time.sleep(2)  # Wait for Arduino to initialize
                print(f"Arduino {arduino_id} registered for wallet {wallet_address}")
                target_blocks = int(input("Enter target number of blocks (max 18): "))
                if target_blocks > 18:
                    print("Error: Max 18 blocks allowed.")
                    return
                print(f"Target set to {target_blocks} blocks for Arduino {arduino_id}.")
        except serial.SerialException:
            print("Error: Could not connect to Arduino. Check port and permissions.")
            sys.exit(1)

    elif action == "B":
        wallet_address = input("Enter your wallet address: ")
        port = get_arduino_port()
        arduino_id = input("Enter the Arduino ID: ")

        try:
            with serial.Serial(port, 115200, timeout=1) as ser:
                time.sleep(2)  # Wait for Arduino to initialize
                print(f"Syncing with Arduino {arduino_id}...")
                
                target_blocks = 18  # Fixed max from znemine.ino
                print(f"Syncing {target_blocks} blocks (~1 hour each)...")
                
                for i in range(target_blocks):
                    block_num = i + 1  # Block 1 to 18
                    hash_result = mine_block(wallet_address, block_num)
                    ser.write(f"STORE_BLOCK:{hash_result}\n".encode())
                    print(f"Block {block_num}/{target_blocks} synced to Arduino {arduino_id}: {hash_result}")
                    time.sleep(1)  # Pause for Arduino to process
                    
                ser.write(b"SYNC_DONE\n")
                print("SYNCING DONE!!")
                
        except serial.SerialException:
            print("Error: Could not connect to Arduino. Check port and permissions.")
            sys.exit(1)
    else:
        print("Invalid option. Use A or B.")
        sys.exit(1)

if __name__ == "__main__":
    if os.geteuid() == 0 or sys.platform == "win32":  # Sudo check
        main()
    else:
        print("This script requires sudo for serial access on Linux/Mac.")
        print("Run with: sudo python3 zneavrminer.py")
        sys.exit(1)
