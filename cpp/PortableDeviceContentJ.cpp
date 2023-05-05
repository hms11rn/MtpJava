#include <initguid.h> 

#include "pch.h"
#include "PortableDeviceContentJ.h"
#include "PortableDevice.h"

#include <PortableDevice.h>
#include <PortableDeviceApi.h>
#include <jni.h>
#include <iostream>
#include <atlbase.h>
#include <atlstr.h>

// 

using namespace std;

IPortableDeviceContent* pContent;
IPortableDeviceValues* pCollection;
IPortableDevicePropVariantCollection* propColl;


IPortableDevicePropVariantCollection* PortableDeviceContentJ::getPropCollection() {
	if (propColl == nullptr) {
		HRESULT hr = CoCreateInstance
		(CLSID_PortableDevicePropVariantCollection, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&propColl));
	}
	propColl->Clear();
	return propColl;
}

HRESULT StreamCopy(IStream* pDestStream, IStream* pSourceStream, DWORD cbTransferSize, DWORD* pcbWritten);

IPortableDeviceValues* getCollection() {
	if (pCollection == nullptr) {
		HRESULT hr = CoCreateInstance(CLSID_PortableDeviceValues, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pCollection));
		if (FAILED(hr)) {
			// handle error
		}
	}
	pCollection->Clear();
	return pCollection;
}
LPWSTR deviceID;
PortableDeviceContentJ::PortableDeviceContentJ(IPortableDeviceContent* content, LPWSTR deviceIDs)
{	
	deviceID = deviceIDs;
	if (ppProperties == nullptr) {
		pContent = content;
		HRESULT hr = content->Properties(&ppProperties);
		if (FAILED(hr)) {
			cout << "incorrect hr" << endl;
			// handle error
		}
	}
}

jobject PortableDeviceContentJ::getObject(LPWSTR idd, JNIEnv* env)
{
	jclass javaClass = env->FindClass("com/github/hms11rn/mtp/win32/PortableDeviceObjectWin32");
	jmethodID constructor = env->GetMethodID(javaClass, "<init>", "(Ljava/lang/String;)V");
	
	jstring idJava = env->NewString((jchar*)idd, wcslen(idd));
	jobject javaObject = env->NewObject(javaClass, constructor, idJava);
	
	return javaObject;
}

BOOL PortableDeviceContentJ::deleteFile(LPWSTR idd, int recursion)
{
	if (recursion != 0 && recursion != 1)
		recursion = 0;
	IPortableDevicePropVariantCollection* coll;
	IPortableDevicePropVariantCollection* result;
	coll = getPropCollection();
	PROPVARIANT del;
	PropVariantInit(&del);
	del.vt = VT_LPWSTR; 
	del.pwszVal = idd;
	coll->Add(&del);
	pContent->Delete(recursion, coll, &result);
	PROPVARIANT resultPropVariant;
	result->GetAt(0, &resultPropVariant); // Result shoul only have a single item in it;
	SCODE resultSCODE = resultPropVariant.scode;
	return resultSCODE == S_OK;
}




IPortableDeviceContent* PortableDeviceContentJ::getContent() {
	return pContent;
}


IPortableDeviceProperties* PortableDeviceContentJ::getProperties() {
	return ppProperties;
}

jstring PortableDeviceContentJ::addFile(JNIEnv* env, LPWSTR parent, jstring javaName, jobject javaFile, jstring contentType, jstring contentFormat, HRESULT* result)
{
	HRESULT hr;


	jmethodID pathMethod;
	jstring jFileLocation;
	
	// streams
	CComPtr<IStream> pFileStream;
	CComPtr<IStream> pDeviceStream;
	CComPtr<IPortableDeviceDataStream> pDeviceDataStream;
	// File info
	LPWSTR wszFileLocation;
	LPWSTR wszFileName;
	STATSTG fileStats;
	DWORD dwBufferSize = 0;
	// keys
	IPortableDeviceValues* pValues;
	
	// out
	LPWSTR wszObjectID;
	jstring jObjectID;
	
	// Content Type
	LPWSTR wszContentType;
	GUID contentTypeGuid;
	wszContentType = (WCHAR*)env->GetStringChars(contentType, nullptr);
	hr = CLSIDFromString(wszContentType, &contentTypeGuid);
	// Content Format
	LPWSTR wszContentFormat;
	GUID contentFormatGuid;
	wszContentFormat = (WCHAR*)env->GetStringChars(contentFormat, nullptr);
	hr = CLSIDFromString(wszContentFormat, &contentFormatGuid);

	pathMethod = env->GetMethodID(env->FindClass("java/io/File"), "getAbsolutePath", "()Ljava/lang/String;");
	jFileLocation = (jstring)env->CallObjectMethod(javaFile, pathMethod);
	wszFileLocation = (WCHAR*)env->GetStringChars(jFileLocation, nullptr);
	wszFileName = (WCHAR*)env->GetStringChars(javaName, nullptr);
	hr = SHCreateStreamOnFileW(wszFileLocation, STGM_READ, &pFileStream);
	env->ReleaseStringChars(jFileLocation, (jchar*)wszFileLocation);

	if (SUCCEEDED(hr)) {
		pValues = getCollection();
		pValues->SetStringValue(WPD_OBJECT_PARENT_ID, parent);
		pValues->SetStringValue(WPD_OBJECT_NAME, wszFileName);
		pValues->SetStringValue(WPD_OBJECT_ORIGINAL_FILE_NAME, wszFileName);
		pValues->SetGuidValue(WPD_OBJECT_CONTENT_TYPE, contentTypeGuid);
		pValues->SetGuidValue(WPD_OBJECT_FORMAT, contentFormatGuid);
		pFileStream->Stat(&fileStats, STATFLAG_NONAME);
		pValues->SetUnsignedLargeIntegerValue(WPD_OBJECT_SIZE, fileStats.cbSize.QuadPart);

		hr = pContent->CreateObjectWithPropertiesAndData(pValues, &pDeviceStream, &dwBufferSize, nullptr);
		if (SUCCEEDED(hr)) {
			HRESULT hr = pDeviceStream->QueryInterface(IID_IPortableDeviceDataStream, (void**)&pDeviceDataStream); // pDeviceDataStream has nothing to do with device as of yet TODO
			DWORD totalBytesWritten = 0;
			hr = StreamCopy(pDeviceDataStream, pFileStream, dwBufferSize, &totalBytesWritten);
			if (hr == 0x80070050) {
				jclass generalPortableDeviceException = env->FindClass("com/github/hms11rn/mtp/PortableDeviceException");
				env->ThrowNew(generalPortableDeviceException, "Could not write to file (Does that file already exist?)");
				return nullptr;
			}
			hr = pDeviceDataStream->Commit(STGC_DEFAULT);
			if (SUCCEEDED(hr))
			{
				pDeviceDataStream->GetObjectID(&wszObjectID);
				jObjectID = (jstring)env->NewString((jchar*)wszObjectID, wcslen(wszObjectID));
				CoTaskMemFree(wszObjectID);
				return jObjectID;
			}
		}
		if (FAILED(hr))
		{
			if (hr == E_POINTER) {
				*result = E_POINTER;
			}
			// Handle error
			return nullptr;
		}
	}
	env->ReleaseStringChars(contentType, (jchar*) wszContentType);
	env->ReleaseStringChars(javaName, (jchar*)wszFileName);
	env->ReleaseStringChars(contentFormat, (jchar*)wszContentFormat);

	return nullptr;
}

jstring PortableDeviceContentJ::addFolder(JNIEnv* env, LPWSTR wszName, LPWSTR parent)
{
	HRESULT hr;
	
	LPWSTR outID;
	jstring outIDJava;
	IPortableDeviceValues* values;

	values = getCollection();
	values->SetStringValue(WPD_OBJECT_PARENT_ID, parent);
	values->SetStringValue(WPD_OBJECT_NAME, wszName);
	values->SetStringValue(WPD_OBJECT_ORIGINAL_FILE_NAME, wszName);
	values->SetGuidValue(WPD_OBJECT_CONTENT_TYPE, WPD_CONTENT_TYPE_FOLDER);
	hr = pContent->CreateObjectWithPropertiesOnly(values, &outID);
	if (!SUCCEEDED(hr)) {
		// handle error
		return nullptr;
	}
	outIDJava = env->NewString((jchar*)outID, wcslen(outID));
	return outIDJava;
}

void PortableDeviceContentJ::copyFile(JNIEnv* env, LPWSTR id, LPWSTR outDir) {
	HRESULT hr;
	IPortableDeviceResources* pResources;

	DWORD optimalBufferSize = 0;
	CComPtr<IStream> pObjectStream;
	CComPtr<IStream> pFileStream;

	hr = pContent->Transfer(&pResources);
	hr = pResources->GetStream(id, WPD_RESOURCE_DEFAULT, STGM_READ, &optimalBufferSize, &pObjectStream);
	if (SUCCEEDED(hr)) {
		hr = SHCreateStreamOnFileEx(outDir, STGM_CREATE | STGM_WRITE, 0, true, nullptr, &pFileStream);
		if (FAILED(hr)) {
			cout << "Failed to create file stream" << endl;
			// handle error
			return;
		}
	DWORD cbTotalBytesWritten = 0;
	hr = StreamCopy(pFileStream, pObjectStream, optimalBufferSize, &cbTotalBytesWritten);
	if (FAILED(hr)) {
		cout << "Failed to copy stream" << endl;
		//handle error
		return;
	}
	fflush(stdout); // memory

	}
	

}

// Currently only supports updaing string value
void PortableDeviceContentJ::updateProperty(JNIEnv* env, LPWSTR id, GUID category, DWORD pid, LPWSTR value) {
	IPortableDeviceProperties* pProperties;
	IPortableDeviceValues* pValues;
	IPortableDeviceValues* outValues;
	PROPERTYKEY prop;
	prop.fmtid = category;
	prop.pid = pid;
	pValues = getCollection();
	pValues->SetStringValue(prop, value);
	pContent->Properties(&pProperties);

	pProperties->SetValues(id, pValues, &outValues);
		
}
// ?????
PortableDeviceContentJ::PortableDeviceContentJ()
{
}

jbyteArray PortableDeviceContentJ::getBytes(JNIEnv* env, LPWSTR id) {
	HRESULT hr;
	CComPtr<IStream> pObjectStream;
	DWORD optimalBufferSize = 0;
	IPortableDeviceResources* pResources;

	hr = pContent->Transfer(&pResources);
	if (FAILED(hr)) {
		printf("Failed to get portable device resources hr = 0x%lx\n", optimalBufferSize, hr);
		// handle error (maybe device closed?)
		return nullptr;
	}
	hr = pResources->GetStream(id, WPD_RESOURCE_DEFAULT, STGM_READ, &optimalBufferSize, &pObjectStream);
	if (FAILED(hr)) {
		printf("Failed to get Stream hr = 0x%lx\n", hr);
		// handle error (???)
		return nullptr;
	}
	BYTE* pObjectData = new (std::nothrow) BYTE[optimalBufferSize];
	if (pObjectData != NULL)
	{
		DWORD cbTotalBytesRead = 0;
		DWORD cbTotalBytesWritten = 0;

		DWORD cbBytesRead = 0;
		DWORD cbBytesWritten = 0;
		 do {
		hr = pObjectStream->Read(pObjectData, optimalBufferSize, &cbBytesRead);
		if (FAILED(hr))
		{
			printf("! Failed to read %d bytes from the source stream, hr = 0x%lx\n", optimalBufferSize, hr);
		}
		 } while (SUCCEEDED(hr) && (cbBytesRead > 0));

		jbyteArray bArr = env->NewByteArray(optimalBufferSize);
		env->SetByteArrayRegion(bArr, 0, optimalBufferSize, (jbyte*)pObjectData);
		delete[] pObjectData;
		pObjectData = NULL;
		return bArr;

	}
}

// from jmtp library
HRESULT StreamCopy(IStream* pDestStream, IStream* pSourceStream, DWORD cbTransferSize, DWORD* pcbWritten)
{
	HRESULT hr = S_OK;

	// Allocate a temporary buffer (of Optimal transfer size) for the read results to
	// be written to.
	BYTE* pObjectData = new (std::nothrow) BYTE[cbTransferSize];
	if (pObjectData != NULL)
	{
		DWORD cbTotalBytesRead = 0;
		DWORD cbTotalBytesWritten = 0;

		DWORD cbBytesRead = 0;
		DWORD cbBytesWritten = 0;

		// Read until the number of bytes returned from the source stream is 0, or
		// an error occured during transfer.
		do
		{
			// Read object data from the source stream
			hr = pSourceStream->Read(pObjectData, cbTransferSize, &cbBytesRead);
			if (FAILED(hr))
			{
				printf("! Failed to read %d bytes from the source stream, hr = 0x%lx\n", cbTransferSize, hr);
			}

			// Write object data to the destination stream
			if (SUCCEEDED(hr))
			{
				cbTotalBytesRead += cbBytesRead; // Calculating total bytes read from device for debugging purposes only

				hr = pDestStream->Write(pObjectData, cbBytesRead, &cbBytesWritten);
				if (FAILED(hr))
				{
					printf("! Failed to write %d bytes of object data to the destination stream, hr = 0x%lx\n", cbBytesRead, hr);
					return 0x80070050;
				}

				if (SUCCEEDED(hr))
				{
					cbTotalBytesWritten += cbBytesWritten; // Calculating total bytes written to the file for debugging purposes only
				}
			}

			// Output Read/Write operation information only if we have received data and if no error has occured so far.
			if (SUCCEEDED(hr) && (cbBytesRead > 0))
			{
				//printf("Read %d bytes from the source stream...Wrote %d bytes to the destination stream...\n", cbBytesRead, cbBytesWritten);
			}

		} while (SUCCEEDED(hr) && (cbBytesRead > 0));

		// If the caller supplied a pcbWritten parameter and we
		// and we are successful, set it to cbTotalBytesWritten
		// before exiting.
		if ((SUCCEEDED(hr)) && (pcbWritten != NULL))
		{
			*pcbWritten = cbTotalBytesWritten;
		}

		// Remember to delete the temporary transfer buffer
		delete[] pObjectData;
		pObjectData = NULL;
	}
	else
	{
		printf("! Failed to allocate %d bytes for the temporary transfer buffer.\n", cbTransferSize);

		return hr;
	}
	return hr;
}

