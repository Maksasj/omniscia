<div>
  <img align="left" src="https://github.com/Maksasj/omniscia/blob/master/docs/readme_icon.png" width="288px">

  # Omniscia
  Omnisicia - 2D platformer game, with the main mechanic time manipulation (traveling to the past, future, speed up and slow down time)

  Omnisicia highly inspired by [Celeste](https://store.steampowered.com/app/504230/Celeste/) as well as by [Braid](https://store.steampowered.com/app/26800/Braid/)

  *Note game is an under development, wait for realeses under realease page*

  <img src="https://img.shields.io/github/stars/Maksasj/omniscia" alt="stars">
  <img src="https://img.shields.io/github/license/Maksasj/omniscia" alt="license">
</div>

---

## Todo List
- ### Priority
  - [x] Super renderer component, allows to request render call on any of rendering stages
  - [ ] Check for memory leaks
  - [ ] Sound system 
- ### Core
  - [ ] System system manager
  - [x] Level manager
- ### ECS
  - [x] Templated constructors
  - [x] Box Collider Component
  - [x] Tile renderer component
  - [x] Mesh builder
  - Prototypes
    - [ ] Prototype serialization
- ### GFX
  - [ ] Better rendering stages
  - [ ] Rendering stage configuration
  - [x] Sprite mesh merging
  - [x] Batch rendering
  - [ ] Instancing
- ### Editor
  - [x] Use tile groups instead of tile grid

## Build
```bash
cmake -B build -G Ninja

make.bat
```

## License
*Todo*
