# DiskSpace Optimizer

<div align="center">

![Disk Space](https://img.shields.io/badge/Disk%20Space-Optimizer-blue?style=for-the-badge&logo=hard-drive)
![C++](https://img.shields.io/badge/C++-17-orange?style=for-the-badge&logo=cplusplus)
![OpenSSL](https://img.shields.io/badge/OpenSSL-SHA256-green?style=for-the-badge&logo=openssl)

**Intelligent Duplicate File Detection & Management System**

*Reclaim your disk space with cryptographic precision*

[Features](#-features) • [Installation](#-installation) • [Usage](#-usage)

</div>

---

## 🎯 Overview

**diskSpace Optimizer** is a powerful, high-performance C++ utility that intelligently identifies and manages duplicate files across your filesystem. Built with enterprise-grade SHA-256 cryptographic hashing, it ensures 100% accuracy in duplicate detection while providing an intuitive interactive interface for file management.

### Why diskSpace Optimizer?

- 🔍 **Cryptographic Accuracy**: Uses SHA-256 hashing for bulletproof duplicate detection
- ⚡ **High Performance**: Optimized C++ implementation for lightning-fast scanning
- 🛡️ **Safe Operations**: Interactive prompts prevent accidental data loss
- 📁 **Recursive Scanning**: Deep directory traversal for comprehensive analysis
- 🎛️ **User Control**: Choose which files to keep with full transparency

---

## ✨ Features

### 🔐 Advanced Detection
- **SHA-256 Hashing**: Military-grade cryptographic hashing ensures perfect duplicate identification
- **Recursive Scanning**: Automatically traverses all subdirectories
- **File Integrity**: Validates file content, not just names or sizes
- **Error Resilience**: Graceful handling of permission issues and corrupted files

### 🎮 Interactive Management
- **Smart Grouping**: Groups identical files for easy comparison
- **User Choice**: Select which file to keep from each duplicate group
- **Safe Moving**: Moves duplicates to designated directory before deletion
- **Confirmation Prompts**: Multiple safety checks prevent accidental data loss

### 🚀 Performance & Reliability
- **Memory Efficient**: Stream-based file processing for large files
- **Cross-Platform**: Works on Linux, macOS, and Windows
- **Error Handling**: Comprehensive error reporting and recovery
- **Progress Feedback**: Real-time scanning status updates

---

## 🛠️ Installation

#### 🐧 Linux
```bash
# Clone repository
git clone https://github.com/yourusername/diskSpace-Optimizer.git
cd diskSpace-Optimizer

# Compile
g++ -std=c++17 -O3 -o diskSpaceOptimizer diskSpace_Optimizer.cpp -lssl -lcrypto

# Make executable
chmod +x diskSpaceOptimizer

# Run
./diskSpaceOptimizer
```

#### 🪟 Windows
```bash
# Clone repository
git clone https://github.com/yourusername/diskSpace-Optimizer.git
cd diskSpace-Optimizer

# Compile
g++ -std=c++17 -O3 -o diskSpaceOptimizer.exe diskSpace_Optimizer.cpp -lssl -lcrypto

# Run
./diskSpaceOptimizer.exe
```

---

## 🚀 Usage

```bash
./diskSpaceOptimizer
```

The program will prompt you for three things:

    1. **Source Directory**: The folder to scan for duplicates.

    2. **Destination Directory**: The folder where duplicates will be moved.

    3. **Action (y/n)**: Choose y to permanently delete all duplicates, or n to move them to the destination directory.

⚠️ Warning: Permanent deletion is irreversible and does not use the Recycle Bin. When in doubt, choose n to move the files for review.


---

