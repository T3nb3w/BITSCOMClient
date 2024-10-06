#include <iostream>
#include <windows.h>
#include <Bits.h>
#pragma comment(lib, "bits")

int wmain(int argc, wchar_t* argv[])
{
    if (argc != 3) {
        std::wcerr << L"Usage: BITSCOMClient.exe <source_url> <destination_path>\n";
        return 1;
    }

    if (FAILED(CoInitialize(nullptr))) return 1;

    IBackgroundCopyManager* pMgr;
    if (FAILED(CoCreateInstance(CLSID_BackgroundCopyManager, nullptr, CLSCTX_ALL,
        IID_IBackgroundCopyManager, reinterpret_cast<void**>(&pMgr))))
    {
        CoUninitialize();
        return 1;
    }

    IBackgroundCopyJob* pJob;
    GUID jobId;
    if (SUCCEEDED(pMgr->CreateJob(L"Sample job", BG_JOB_TYPE_DOWNLOAD, &jobId, &pJob)))
    {
        pJob->AddFile(argv[1], argv[2]);
        pJob->Resume();

        BG_JOB_STATE state;
        do {
            pJob->GetState(&state);
            Sleep(200);
        } while (state != BG_JOB_STATE_ERROR && state != BG_JOB_STATE_TRANSFERRED);

        if (state == BG_JOB_STATE_ERROR) {
            IBackgroundCopyError* pError;
            if (SUCCEEDED(pJob->GetError(&pError))) {
                PWSTR desc;
                pError->GetErrorDescription(LANG_USER_DEFAULT, &desc);
                std::wcout << desc << std::endl;
                CoTaskMemFree(desc);
                pError->Release();
            }
        }
        else {
            pJob->Complete();
            std::wcout << L"Download success!\n";
        }
        pJob->Release();
    }

    pMgr->Release();
    CoUninitialize();
    return 0;
}
