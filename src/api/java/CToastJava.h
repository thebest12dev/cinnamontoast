/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class ctoast4j_CToastNative */

#ifndef _Included_ctoast4j_CToastNative
#define _Included_ctoast4j_CToastNative
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     ctoast4j_CToastNative
 * Method:    getReferenceById
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_ctoast4j_CToastNative_getReferenceById(JNIEnv *,
                                                                   jclass,
                                                                   jstring);

/*
 * Class:     ctoast4j_CToastNative
 * Method:    getText
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_ctoast4j_CToastNative_getText(JNIEnv *, jclass,
                                                             jint);

/*
 * Class:     ctoast4j_CToastNative
 * Method:    addComp
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_ctoast4j_CToastNative_addComp(JNIEnv *, jclass,
                                                          jint, jint);

/*
 * Class:     ctoast4j_CToastNative
 * Method:    createLabel
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ctoast4j_CToastNative_createLabel(JNIEnv *, jclass);

/*
 * Class:     ctoast4j_CToastNative
 * Method:    setText
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_ctoast4j_CToastNative_setText(JNIEnv *, jclass,
                                                          jint, jstring);

/*
 * Class:     ctoast4j_CToastNative
 * Method:    renderComp
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ctoast4j_CToastNative_renderComp(JNIEnv *, jclass,
                                                             jint);

/*
 * Class:     ctoast4j_CToastNative
 * Method:    setSize
 * Signature: (III)V
 */
JNIEXPORT void JNICALL Java_ctoast4j_CToastNative_setSize(JNIEnv *, jclass,
                                                          jint, jint, jint);

/*
 * Class:     ctoast4j_CToastNative
 * Method:    getColor
 * Signature: (I)[I
 */
JNIEXPORT jintArray JNICALL Java_ctoast4j_CToastNative_getColor(JNIEnv *,
                                                                jclass, jint);

/*
 * Class:     ctoast4j_CToastNative
 * Method:    setColor
 * Signature: (IIII)V
 */
JNIEXPORT void JNICALL Java_ctoast4j_CToastNative_setColor(JNIEnv *, jclass,
                                                           jint, jint, jint,
                                                           jint);

/*
 * Class:     ctoast4j_CToastNative
 * Method:    setVisible
 * Signature: (IZ)V
 */
JNIEXPORT void JNICALL Java_ctoast4j_CToastNative_setVisible__IZ(JNIEnv *,
                                                                 jclass, jint,
                                                                 jboolean);

/*
 * Class:     ctoast4j_CToastNative
 * Method:    setVisible
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_ctoast4j_CToastNative_setVisible__II(JNIEnv *,
                                                                 jclass, jint,
                                                                 jint);

#ifdef __cplusplus
}
#endif
#endif
