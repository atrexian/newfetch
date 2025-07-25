# 🚀 Newfetch

A sleek, minimalist system info tool written in C — **fast** and **simple**.

![Newfetch demo](./demo.png)

---

## ✨ Features

- 🧠 Shows essential system info (User, Host, Distro, Kernel, Arch, Uptime, CPU and RAM)
- 🎨 Colorful output with ASCII art and themed palettes
- 🪶 Lightweight with zero runtime dependencies
- 🧩 Modular codebase and simple build process

---

## 📦 Installation

### 📥 Arch Linux (AUR)
```bash
yay -S newfetch
```

### 🧪 Manual (Any Distro)
```bash
git clone https://github.com/atrexian/newfetch.git
cd newfetch
chmod +x newfetch
sudo mv newfetch /usr/local/bin/
```

---

## 💻 Supported Distributions

Newfetch runs on **any Linux distribution** — it’s written in pure C, fast, and portable.

However, only the following distros have dedicated ASCII logos included in the source:

- 🟦 Arch Linux
    - 🟩 Manjaro
- 🟥 Debian
- 🟦 Fedora
- 🟪 Gentoo
- 🟩 openSUSE
- 🟧 Ubuntu
    - 🟩 Linux Mint
- 🟩 Void

For all other distros, Newfetch will gracefully fall back to the classic **Tux** logo 🐧.

Want your distro supported? [Open a PR](https://github.com/atrexian/newfetch/pulls) with an ASCII art!

---

### 📄 License

**GNU General Public License v3.0**

See [LICENSE](https://github.com/atrexian/newfetch/blob/main/LICENSE) for full details.

Built for the terminal. Designed for hackers. Made with 💙 by [@Atrexian](https://github.com/atrexian).