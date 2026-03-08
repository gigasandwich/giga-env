# Env var CRUD
- [x] READ
- [x] CREATE
- UPDATE
    - [ ] Key
    - [x] Value
- [x] DELETE

- Fix
    - [x] Warnings
    - [x] Values still persisting after deletion

# Path Modification
- [x] CRUD

# Control
- [ ] Can only *read/update/delete* if `envVar.exists()`
- [ ] Can't `envVar.create()` if `!envVar.exists()`
