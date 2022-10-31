# CPP Engine

## Creating new Systems

### 1. Create new System Header File
Create a new System Header file in the [Systems Folder](./src/Systems/)

### 2. Include new system
Be sure to include the new system at the top of the [Engine.cpp](./src/Engine/Engine.cpp) file

### 3. Register the new system
After the new system is included we will need to actually register the system for use within the Engine's [setup hook](./src/Engine/Engine.cpp#L100-L105).
