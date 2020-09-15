#include <stddef.h>

///////object methods//////
object_t* AllocObject();
void Ctor(object_t* this);
int Equals(object_t* obj1, object_t* obj2);
int HashCode(object_t* this);
object_t* Clone(object_t* this);
void Finalize(object_t* this);
metadata_t* GetClass(object_t* this);
const char* ToString(object_t* this);//creates immutable string

//////animal methods///////
animal_t* AllocAnimal();
void CtorDefault(animal_t* this);
void CtorArgs(animal_t*, int num_masters);

void SayHelloAnimal(animal_t* this);
void ShowCounter(); //not in v_table. this is a static func
void FinalizeAnimal(animal_t* this);
const char* ToStringAnimal(animal_t* this);
int GetNumMasters(animal_t* this);


/////dog methods//////////
dog_t* AllocDog();
void CtorDog(dog_t* this);
void SayHelloDog(dog_t* this);
void FinalizeDog(dog_t* this);
const char* ToStringDog(dog_t* this);

//////cat methods/////////
cat_t* AllocCat();
void CtorCat1Arg(cat_t* this);
void CtorCat2Args(cat_t* this, const char* colors);

void FinalizeCat(cat_t* this);
const char* ToStringCat(cat_t* this);

//////legendary animal methods//////
legendary_animal_t* AllocLegendaryAnimal();
void CtorLegendaryAnimal(legendary_animal_t* this);

const char* ToStringLegendaryAnimal(legendary_animal_t* this);
void SayHelloLegendaryAnimal(legendary_animal_t* this);
void FinalizeLegendaryAnimal(legendary_animal_t* this);

typedef void* (*(*v_table)[])(void*); //contains - hashCode, equals, ToString, GetLegs..
typedef const char* (*to_string_legend_t)(legendary_animal_t*);//example to show cast of func to insert and pul out
                                                            //of v_table


typedef enum classes
{
    OBJECT,
    ANIMAL,
    CAT,
    DOG, 
    LEGENDARY_ANIMAL,
    NUM_OF_CLASSES
}classes_t;

static int g_counter = 0;
static int g_is_loaded[NUM_OF_CLASSES] = {0};

typedef struct metadata
{
    const char* name;
    size_t size;
    metadata_t* super;  //check if need
    v_table func_table;
}metadata_t;

typedef struct object
{
    metadata_t* class;
}object_t;

typedef struct animal
{
    object_t *super;
    int id;
    int num_masters;
    int num_legs;
}animal_t;

typedef struct dog
{
    animal_t *super;
    const char *colors;
    int num_masters;
}dog_t;

typedef struct cat
{
    animal_t *super;
    int num_masters;
    const char* colors;
}cat_t;

typedef struct legendary_animal
{
    cat_t *super;
}legendary_animal_t;


