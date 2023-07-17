// AUTO GENERATED FILE, DO NOT EDIT.
//
// Generated by `package:ffigen`.
// ignore_for_file: type=lint
import 'dart:ffi' as ffi;

/// FFI bindings to SoLoud
class FlutterSoLoudFfi {
  /// Holds the symbol lookup function.
  final ffi.Pointer<T> Function<T extends ffi.NativeType>(String symbolName)
      _lookup;

  /// The symbols are looked up in [dynamicLibrary].
  FlutterSoLoudFfi(ffi.DynamicLibrary dynamicLibrary)
      : _lookup = dynamicLibrary.lookup;

  /// The symbols are looked up with [lookup].
  FlutterSoLoudFfi.fromLookup(
      ffi.Pointer<T> Function<T extends ffi.NativeType>(String symbolName)
          lookup)
      : _lookup = lookup;

  /// @brief check if a handle is still valid.
  /// @param handle handle to check
  /// @return true if it still exists
  int getIsValidVoiceHandle(
    int handle,
  ) {
    return _getIsValidVoiceHandle(
      handle,
    );
  }

  late final _getIsValidVoiceHandlePtr =
      _lookup<ffi.NativeFunction<ffi.Int Function(ffi.UnsignedInt)>>(
          'getIsValidVoiceHandle');
  late final _getIsValidVoiceHandle =
      _getIsValidVoiceHandlePtr.asFunction<int Function(int)>();
}
