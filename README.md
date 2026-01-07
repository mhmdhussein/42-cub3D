# cub3D: A Raycasting-Based 3D Engine

**cub3D** is a simple 3D raycasting engine written in **C**, inspired by *Wolfenstein 3D*.  
This project is part of the 42 curriculum and is built using the **MiniLibX** graphics library.

The goal is to render a first-person view inside a maze using raycasting techniques.

---

## 📌 Features

- Real-time **raycasting** rendering
- Textured walls (North, South, East, West)
- Configurable **floor and ceiling colors**
- Player movement:
  - `W`, `A`, `S`, `D` — move
  - `←` / `→` — rotate view
- Clean window handling (ESC / close button)
- `.cub` file parsing with error handling

---

## 🕹️ Controls

| Key | Action |
|----|-------|
| W | Move forward |
| S | Move backward |
| A | Strafe left |
| D | Strafe right |
| ← | Rotate left |
| → | Rotate right |
| ESC | Exit the program |

---

## 🗺️ Map Format (`.cub`)

The program takes a **scene description file** with the `.cub` extension.

### Identifiers

```text
NO ./path_to_north_texture
SO ./path_to_south_texture
WE ./path_to_west_texture
EA ./path_to_east_texture
F 220,100,0
C 225,30,0
````

### Map Rules

* `1` = wall
* `0` = empty space
* `N`, `S`, `E`, `W` = player spawn & orientation
* The map **must be closed/surrounded by walls**
* Spaces are valid and must be handled correctly

### Example Map

```text
111111
100101
101001
1100N1
111111
```

---

## 🛠️ Installation & Compilation

### Requirements

* macOS or Linux
* `gcc` / `cc`
* **MiniLibX**
* `make`

### Compile

```bash
make
```

### Clean

```bash
make clean
make fclean
```

---

## ▶️ Usage

```bash
./cub3D maps/example.cub
```

If the configuration file is invalid, the program exits with:

```text
Error
<explicit error message>
```

---

## 🧠 Concepts Used

* Raycasting algorithms
* Vector math & trigonometry
* Event-driven programming
* Texture mapping
* File parsing & validation
* Memory management in C

---

## 📂 Project Structure (example)

```text
cub3D/
├── src/
├── includes/
├── textures/
├── maps/
├── Makefile
└── README.md
```

---

## 📸 Demo

![cub3D demo](assets/demo.gif)

---

## 🙏 Acknowledgements
Big thanks to my partner [Razane Traoui](https://github.com/razanetraoui) for her commitment, collaboration, and the many hours spent coding, debugging, and refining this project together. This work truly wouldn’t have been possible without her.

## 📚 Resources

This project was made possible thanks to the following references and learning materials:

* *Wolfenstein 3D* — inspiration for raycasting and level design
* Lode Vandevenne’s **Raycasting Tutorial**
* 42 documentation and evaluation guidelines
* Various community articles and math references on raycasting and trigonometry

---

## ⚠️ Disclaimer

This project is inspired by *Wolfenstein 3D* for **technical and educational purposes only**.
All historical references are used strictly for learning computer graphics concepts and game engine fundamentals.

---

## 📝 License

This project is licensed under the [MIT License](https://opensource.org/licenses/MIT).
You are free to use, modify, and distribute this project with proper attribution.

---

## ⭐ Final Note

cub3D is a challenging but rewarding introduction to **graphics programming**, **raycasting**, and **low-level engine design**.
If you’re starting this project: be patient, test often, and don’t skip the math, it's quite fun 😉