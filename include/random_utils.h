
#define rand_v(type, suffix) rand_##suffix
#define rand_decl(type, suffix) type rand_v(type, suffix)(type low, type high)
#define rand_arr_decl(type, suffix) void random_##suffix##_arr(type* buffer, type low, type high, unsigned int len)

rand_decl(float, f32);
rand_arr_decl(float, f32);
