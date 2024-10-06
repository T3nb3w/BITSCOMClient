# BITS-COM-File-Downloader

## Description
This project is a C++ application that demonstrates how to download files using the **Background Intelligent Transfer Service (BITS)** via the **Component Object Model (COM)**. The program allows downloading a file from a specified URL and saves it to a local path using background file transfer mechanisms that continue even if the application is closed, as managed by BITS.

## Key Features
- **Background File Transfers**: Uses **BITS** to download files in the background with low network impact.
- **COM Interface Usage**: Leverages **COM** (`IBackgroundCopyManager`, `IBackgroundCopyJob`) to manage file download jobs.
- **Unicode Support**: Supports wide-character (Unicode) file paths and URLs.
- **Error Handling**: Retrieves and prints detailed error descriptions if the download fails.

## How to Build
1. Open the project in **Visual Studio**.
2. Build the solution to compile the application.

## How to Run
After building the project, run the compiled executable from the command line using the following format:
```bash
BITSCOMClient.exe <source_url> <destination_path>
