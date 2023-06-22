#include "PortableDeviceObjectJ.h"

#include <jni.h>
#include <PortableDeviceApi.h>

class PortableDeviceContentJ
{
	private:
		IPortableDevicePropVariantCollection* getPropCollection();
		IPortableDeviceKeyCollection* getContentTypeKey();

	public:
		void release();
		PortableDeviceContentJ(IPortableDeviceContent*);
		IPortableDeviceContent* getContent();

		jobject getObjects(JNIEnv* env, jobject, jstring parentID);
		// Add Object From File
		jstring addObjectFromFile(JNIEnv* env, LPWSTR parent, jstring, jobject, jstring contentType, jstring contentFormat, HRESULT*);
		// Add Object From Java InputStream
		jstring addObjectFromInputStream(JNIEnv* env, LPWSTR parent, LPWSTR name, jobject inputStream, LPWSTR type, LPWSTR format);
		// Add Folder
		jstring addFolderObject(JNIEnv* env, LPWSTR javaName, LPWSTR parent);
		// Copy Object to File
		void copyObjectToFile(JNIEnv* env, LPWSTR id, LPWSTR outDir);
		// Update Property in the Object
		void updateProperty(JNIEnv* env, LPWSTR id, GUID category, DWORD pid, int vt, LPWSTR value);
		// Delete Object
		BOOL deleteFile(LPWSTR idd, int recursion);		
		// Get Bytes of Object
		BYTE* getBytes(JNIEnv* env, LPWSTR id, DWORD*);
		// Write Bytes onto Object
		DWORD writeBytes(JNIEnv*, LPWSTR id, BYTE* buffer, DWORD bufferSize, BOOL append, DWORD rewrite, LPWSTR* newObjectID);


};