# Arduino Projects

This repository contains various Arduino sketches.

## Compiling and Uploading Sketches

You can compile and upload sketches to your Arduino board using the `arduino-cli` tool.

### Commands

- **Compile:** To compile a sketch, use the `arduino-cli compile` command. You need to specify the board's FQBN and the path to your `.ino` file.

  ```bash
  arduino-cli compile --fqbn arduino:avr:uno <sketch_folder>/<sketch_file>.ino
  ```

- **Upload:** To upload a compiled sketch, use the `arduino-cli upload` command. You need to provide the port, the FQBN, and the path to the sketch folder.

  ```bash
  arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno <sketch_folder>
  ```

- **Reset:** To stop a running sketch, you can upload an empty sketch to the board.

  ```bash
  arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno empty
  ```

### Example

To compile and upload the `morse_with_D7` sketch from the root directory:

```bash
# Compile the sketch
arduino-cli compile --fqbn arduino:avr:uno morse_with_D7/morse_with_D7.ino

# Upload the sketch
arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno morse_with_D7
```

## Technical Details

### What is FQBN?

**FQBN** stands for **Fully Qualified Board Name**. It is a unique identifier that tells the `arduino-cli` exactly which board you are using. The format is `vendor:architecture:board`.

- **`vendor`**: The company that made the board (e.g., `arduino`).
- **`architecture`**: The processor architecture (e.g., `avr` for the Uno).
- **`board`**: The specific model of the board (e.g., `uno`).

The FQBN `arduino:avr:uno` corresponds to the official Arduino Uno. You can see a list of all available board FQBNs by running `arduino-cli board listall`.

### How to Find the Port

The port is the communication channel between your computer and the Arduino.

1.  Connect your Arduino to your computer via USB.
2.  Open your terminal and run the command:
    ```bash
    arduino-cli board list
    ```
3.  The output will show you a list of connected boards and their ports. The port for your Arduino will typically be listed under the `Port` column, often named something like `/dev/ttyACM0` on Linux or `COM3` on Windows.

    **Example Output:**
    ```
    Port         Type              Board Name      FQBN              Core
    /dev/ttyACM0 Serial Port (USB) Arduino Uno     arduino:avr:uno   arduino
    ```
    In this case, the port is `/dev/ttyACM0`.
