This is a TOTP (Time-Based One-Time Password) authenticator that adheres to [RFC 6238](https://datatracker.ietf.org/doc/html/rfc6238 "RFC 6238"). It utilizes the OpenSSL library for cryptographic operations. Secrets are securely stored in a file, encrypted using AES-256. The encrypted file can be transferred to different machines for usage.

## Build

Before building, ensure that you have OpenSSL library installed and that your compiler supports C++20. By default, the executable is located in the `build` folder.

### Windows

By default, Visual Studio Release build will statically link dependencies. You can install OpenSSL using vcpkg. Follow these steps:

1. Install OpenSSL using vcpkg:
    ```bat
    vcpkg.exe install openssl:x64-windows-static
    ```

2. Integrate vcpkg with Visual Studio:
    ```bat
    vcpkg.exe integrate install
    ```

3. Build the Visual Studio solution located in the `VisualStudio` folder.

### Linux

If you're on Linux, run the following command to build Authenticator:
```sh
make
```

## Prebuilt Binaries

Prebuilt binaries for x64 Windows and Linux can be found [here](https://github.com/pi-314159/Authenticator/releases "prebuilt binaries").

## Usage

By default, The authenticator stores secrets in the file named `Accounts` in the same folder. However, you can change this location by passing a command-line argument:
```sh
./Authenticator /path/to/secrets
```

### Command Options

After starting the program, you can use the following commands:

1. `l`: List all accounts. Each account is numbered.
2. `[number]`: Generate a new OTP for the specified account number.
3. `a`: Add a new account. Please decode the QR code by yourself as you'll be prompted to enter the account details.
4. `d[number]`: Delete an existing account by its account number.
5. `c`: Change the password of the encrypted file.
6. `q`: Quit the program.

### Example Usage

To generate a new OTP for the third account, use:
```
3
```

To add a new account, use:
```
a
```

Follow the prompts to enter the account details.

To delete the second account, use:
```
d2
```

## Contributions

Contributions to this project are welcome! If you find any bugs or have suggestions for improvements, please open an [issue](https://github.com/pi-314159/Authenticator/issues "issue") or submit a [pull request](https://github.com/pi-314159/Authenticator/pulls "pull request").

## License

Authenticator is licensed under the [MIT License](https://github.com/pi-314159/Authenticator/blob/main/LICENSE "MIT License").