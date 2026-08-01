# Smart Traffic Management System (C++ Console)

A console-based prototype that simulates intelligent city traffic operations using Object-Oriented Programming in C++. It supports user authentication, dynamic traffic signal control based on vehicle density and emergencies, violation reporting with challan generation, and emergency logging — with all records persisted to text files. :contentReference[oaicite:0]{index=0}

---

## Table of Contents
- [Overview](#overview)
- [Key Features](#key-features)
- [System Design](#system-design)
- [Data Persistence](#data-persistence)
- [Getting Started](#getting-started)
- [How to Use](#how-to-use)
- [Files Generated at Runtime](#files-generated-at-runtime)
- [Notes & Assumptions](#notes--assumptions)
- [Future Enhancements](#future-enhancements)
- [Credits](#credits)

---

## Overview

This project demonstrates an OOP-driven approach to simulate a four-way intersection with: user registration/login, adaptive signal timing by vehicle count, emergency priority handling, violation reporting with fixed penalties and unique challans, and emergency case logging by type and location. All modules are menu-driven and records are saved to plain text files. :contentReference[oaicite:1]{index=1}

---

## Key Features

1. **User Authentication**  
   - Register and login using a username/password stored in a local text file. :contentReference[oaicite:2]{index=2}

2. **Smart Signal Control**  
   - Accepts vehicle counts and emergency flags for North, East, South, and West.  
   - Prioritizes directions with emergencies first; otherwise sorts by density.  
   - Logs each control session to a history file. :contentReference[oaicite:3]{index=3}

3. **Violation Reporting & Challan Generation**  
   - Choose from predefined violation types (e.g., overspeeding, no helmet).  
   - Applies fixed penalties and generates a **unique challan ID** maintained via a counter file.  
   - Persists reports to a violations log. :contentReference[oaicite:4]{index=4}

4. **Emergency Reporting**  
   - Record incidents such as accidents, bridge collapse, tree/pole fall, or water logging.  
   - Store by **type** and **street/location**; filterable on retrieval. :contentReference[oaicite:5]{index=5}

5. **Persistent Storage (No DB Required)**  
   - All modules use text files to simulate a lightweight database. :contentReference[oaicite:6]{index=6}

---

## System Design

The application follows a modular OOP structure, centered on four classes: :contentReference[oaicite:7]{index=7}

- `User` — registration and login; credentials saved to a file.  
- `TrafficControl` — computes and logs the order/duration of green lights using vehicle counts and emergency priority.  
- `Violation` — records rule violations, maps to fixed penalties, and creates unique challans.  
- `Emergency` — logs incidents and supports filtered queries by type or location.

**OOP Principles Employed**  
- *Encapsulation*: Each class hides internal data and exposes minimal public APIs.  
- *Abstraction*: Main menu interacts with high-level methods like `controlSignal()` or `reportViolation()` without internal details.  
(Additional extensibility via inheritance/polymorphism is suggested as future work.) :contentReference[oaicite:8]{index=8}

---

## Data Persistence

Instead of a database, the system uses plain text files (created on demand): :contentReference[oaicite:9]{index=9}

- `users.txt` — registered usernames/passwords.  
- `signal_log.txt` — chronological record of intersections handled and the final signal order/timings.  
- `challan_id.txt` — persistent counter to ensure unique challan numbers.  
- `violations.txt` — all reported violations with challan IDs and penalties.  
- `emergencies.txt` — emergency incidents with type and location; used for filtered retrieval.

> Tip: Keep these files alongside the executable to avoid path issues on first run.

---

## Getting Started

### Prerequisites
- A C++17-compatible compiler (e.g., `g++`, `clang++`, or MSVC).

### Build
If the whole program is in a single file (e.g., `main.cpp`):
```bash
g++ -std=c++17 -O2 -o smart_traffic main.cpp
