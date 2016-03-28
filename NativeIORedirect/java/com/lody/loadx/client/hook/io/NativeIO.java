package com.lody.loadx.client.hook.io;

/**
 * @author Lody
 * @version 1.0
 *
 *
 * 这是支持加固app的关键，因为很多app会去调用System.loadLibrary("/data/data/{包名}/xxx/XXX.so");
 * 这个时候在Java端的IO拦截是无效的，因为它在Native才打开目标文件（如dlopen函数），因此只有在Native Hook才有效果。
 *
 */
public class NativeIO {

    private static final boolean ENABLE_IO_REDIRECT = true;

    private static final int RESULT_OPEN_SUCCESS = 0;

    private static boolean loadSuccess = false;
    static {
        if (ENABLE_IO_REDIRECT) {
            try {
                System.loadLibrary("xhook");
                loadSuccess = open() == RESULT_OPEN_SUCCESS;
            }catch (Throwable e) {
                e.printStackTrace();
            }
        }
    }


    /**
     * Enable Native Hook and open the IO Redirect.
     *
     * @return hookResult, {@link NativeIO#RESULT_OPEN_SUCCESS}.
     */
    public static native int open();

    /**
     * Redirect all IO operation from a folder to a new folder.
     * @param originDir Old Folder
     * @param newDir New Folder
     */
    static native void nativeRedirectFolder(String originDir, String newDir);

    /**
     * Redirect all IO operation from a file to a new file.
     * @param originFilePath Old file path
     * @param newFilePath New file path
     */
    static native void nativeRedirectFile(String originFilePath, String newFilePath);



    public static void redirectFolder(String originDir, String newDir, boolean appendSlash) {
        if (loadSuccess) {
            if (appendSlash) {
                if (!originDir.endsWith("/")) {
                    originDir = originDir.concat("/");
                }
                if (!newDir.endsWith("/")) {
                    newDir = newDir.concat("/");
                }
            }
            nativeRedirectFolder(originDir, newDir);
        }
    }

    public static void redirectFile(String originFilePath, String newFilePath) {
        if (loadSuccess) {
            nativeRedirectFile(originFilePath, newFilePath);
        }
    }

}
