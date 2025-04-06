import tkinter as tk
from tkinter import ttk, messagebox
import json
import os
from hashlib import sha256  # For basic key validation simulation

class ZoneCryptoGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("Zone Crypto Wallet")
        self.root.geometry("500x350")
        
        self.logged_in = False
        self.current_address = None
        self.ledger_file = "ledger.json"
        self.load_ledger()
        
        # Variables
        self.address_var = tk.StringVar()
        self.key_var = tk.StringVar()
        self.balance_var = tk.StringVar(value="0 ZNE")
        self.status_var = tk.StringVar(value="Enter your wallet address and private key to log in.")
        
        self.setup_gui()
        
    def load_ledger(self):
        if os.path.exists(self.ledger_file):
            with open(self.ledger_file, "r") as f:
                self.ledger = json.load(f)  # {address: {"balance": X, "key_hash": "..."}}
        else:
            self.ledger = {}  # Initialize empty ledger
            self.save_ledger()
    
    def save_ledger(self):
        with open(self.ledger_file, "w") as f:
            json.dump(self.ledger, f, indent=4)
    
    def hash_key(self, key):
        # Simulate private key validation (in real crypto, this would involve ECDSA)
        return sha256(key.encode()).hexdigest()
    
    def setup_gui(self):
        # Login/Create Frame
        login_frame = ttk.LabelFrame(self.root, text="Zone Wallet Login")
        login_frame.grid(row=0, column=0, padx=10, pady=10, sticky="ew", columnspan=2)
        
        ttk.Label(login_frame, text="Wallet Address:").grid(row=0, column=0, padx=5, pady=5, sticky="e")
        ttk.Entry(login_frame, textvariable=self.address_var, width=40).grid(row=0, column=1, padx=5, pady=5)
        
        ttk.Label(login_frame, text="Private Key:").grid(row=1, column=0, padx=5, pady=5, sticky="e")
        ttk.Entry(login_frame, textvariable=self.key_var, show="*", width=40).grid(row=1, column=1, padx=5, pady=5)
        
        ttk.Button(login_frame, text="Log In", command=self.login).grid(row=2, column=0, padx=5, pady=5)
        ttk.Button(login_frame, text="Create Wallet", command=self.create_wallet).grid(row=2, column=1, padx=5, pady=5)
        
        # Status/Balance Frame
        status_frame = ttk.LabelFrame(self.root, text="Wallet Status")
        status_frame.grid(row=1, column=0, padx=10, pady=10, sticky="ew", columnspan=2)
        
        ttk.Label(status_frame, text="Balance:").grid(row=0, column=0, padx=5, pady=5, sticky="e")
        ttk.Label(status_frame, textvariable=self.balance_var, relief="sunken", width=20).grid(row=0, column=1, padx=5, pady=5)
        
        ttk.Label(status_frame, text="Status:").grid(row=1, column=0, padx=5, pady=5, sticky="e")
        ttk.Label(status_frame, textvariable=self.status_var, wraplength=400).grid(row=1, column=1, padx=5, pady=5)
        
        # Action Buttons (visible after login)
        self.action_frame = ttk.LabelFrame(self.root, text="Actions")
        self.action_frame.grid(row=2, column=0, padx=10, pady=10, sticky="ew", columnspan=2)
        self.action_frame.grid_remove()  # Hidden until login
        
        ttk.Button(self.action_frame, text="Log Out", command=self.logout).grid(row=0, column=0, padx=5, pady=5)
    
    def create_wallet(self):
        address = self.address_var.get().strip()
        key = self.key_var.get().strip()
        
        if not address or not key:
            messagebox.showerror("Error", "Wallet address and private key are required.")
            return
        
        if address in self.ledger:
            messagebox.showerror("Error", "Wallet address already exists.")
            return
        
        key_hash = self.hash_key(key)
        self.ledger[address] = {"balance": 0, "key_hash": key_hash}
        self.save_ledger()
        self.status_var.set(f"Wallet {address} created with 0 ZNE. Keep your private key safe!")
        self.address_var.set("")
        self.key_var.set("")
    
    def login(self):
        address = self.address_var.get().strip()
        key = self.key_var.get().strip()
        
        if not address or not key:
            messagebox.showerror("Error", "Wallet address and private key are required.")
            return
        
        if address not in self.ledger:
            messagebox.showerror("Error", "Wallet address not found.")
            return
        
        key_hash = self.hash_key(key)
        if self.ledger[address]["key_hash"] != key_hash:
            messagebox.showerror("Error", "Incorrect private key.")
            return
        
        self.logged_in = True
        self.current_address = address
        self.balance_var.set(f"{self.ledger[address]['balance']} ZNE")
        self.status_var.set(f"Logged in as {address}. Anyone with your private key can access this wallet.")
        self.action_frame.grid()  # Show logout button
        self.address_var.set("")
        self.key_var.set("")
    
    def logout(self):
        self.logged_in = False
        self.current_address = None
        self.balance_var.set("0 ZNE")
        self.status_var.set("Enter your wallet address and private key to log in.")
        self.action_frame.grid_remove()  # Hide logout button

if __name__ == "__main__":
    root = tk.Tk()
    app = ZoneCryptoGUI(root)
    root.mainloop()
