void print_version() {
    char filename[MAX_PATH];
    GetModuleFileNameA(NULL, filename, MAX_PATH);

    DWORD dummy;
    DWORD size = GetFileVersionInfoSizeA(filename, &dummy);

    if (size == 0) return;

    void* data = malloc(size);

    if (!GetFileVersionInfoA(filename, 0, size, data)) {
        free(data);
        return;
    }

    VS_FIXEDFILEINFO* ver = NULL;
    UINT len = 0;

    if (VerQueryValueA(data, "\\", (LPVOID*)&ver, &len)) {
        int major = HIWORD(ver->dwFileVersionMS);
        int minor = LOWORD(ver->dwFileVersionMS);
        int patch = HIWORD(ver->dwFileVersionLS);

        std::cout << major << "." << minor << "." << patch << std::endl;
    }

    free(data);
}