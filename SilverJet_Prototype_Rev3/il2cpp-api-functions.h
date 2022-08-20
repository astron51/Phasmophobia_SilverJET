// Crucial API Function

DO_API(char*, il2cpp_type_get_name, (const Il2CppType* type));
DO_API(uint32_t, il2cpp_method_get_param_count, (const MethodInfo* method));
DO_API(const Il2CppType*, il2cpp_method_get_param, (const MethodInfo* method, uint32_t index));
DO_API(const MethodInfo*, il2cpp_class_get_methods, (Il2CppClass* klass, void** iter));
DO_API(const char*, il2cpp_method_get_param_name, (const MethodInfo* method, uint32_t index));
DO_API(Il2CppClass*, il2cpp_class_from_name, (const Il2CppImage* image, const char* namespaze, const char* name));
DO_API(Il2CppDomain*, il2cpp_domain_get, ());
DO_API(const Il2CppAssembly*, il2cpp_domain_assembly_open, (Il2CppDomain* domain, const char* name));