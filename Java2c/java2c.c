
#include "java2c.h"

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <stdio.h> /* fprintf */
#include <string.h> /*strcat */

void AnimalPreCtor(animal_t* this);
void PreCtor(cat_t* this);

typedef void* (*void_ptr_t)(void*);

void*(*object_v_table[])(void*) = 
{
    (void_ptr_t)Equals,
    (void_ptr_t)HashCode,
    (void_ptr_t)Clone,
    (void_ptr_t)Finalize,
    (void_ptr_t)GetClass,
    (void_ptr_t)ToString
};

metadata_t obj_metadata = {&object_v_table ,"il.co.ilrd.Java2c.Object@", sizeof(object_t), NULL };

void*(*animal_v_table[])(void*) = 
{
    (void_ptr_t)Equals,
    (void_ptr_t)HashCode,
    (void_ptr_t)Clone,
    (void_ptr_t)FinalizeAnimal,
    (void_ptr_t)GetClass,
    (void_ptr_t)ToStringAnimal,
    (void_ptr_t)SayHelloAnimal,
    (void_ptr_t)GetNumMasters,

};

metadata_t animal_metadata = {&animal_v_table, "il.co.ilrd.Java2c.Animal@" , sizeof(animal_t), &obj_metadata };

void*(*dog_v_table[])(void*) = 
{
    (void_ptr_t)Equals,
    (void_ptr_t)HashCode,
    (void_ptr_t)Clone,
    (void_ptr_t)FinalizeDog,
    (void_ptr_t)GetClass,
    (void_ptr_t)ToStringDog,
    (void_ptr_t)SayHelloDog,
    (void_ptr_t)GetNumMasters,
};

metadata_t dog_metadata = {&dog_v_table, "il.co.ilrd.Java2c.Dog@", sizeof(dog_t), &animal_metadata };

void*(*cat_v_table[])(void*) =
{
    (void_ptr_t)Equals,
    (void_ptr_t)HashCode,
    (void_ptr_t)Clone,
    (void_ptr_t)FinalizeCat,
    (void_ptr_t)GetClass,
    (void_ptr_t)ToStringCat,
    (void_ptr_t)SayHelloAnimal,
    (void_ptr_t)GetNumMasters,
};

metadata_t cat_metadata = {&cat_v_table, "il.co.ilrd.Java2c.Cat@", sizeof(cat_t), &animal_metadata };


void*(*legendary_v_table[])(void*) =
{
    (void_ptr_t)Equals,
    (void_ptr_t)HashCode,
    (void_ptr_t)Clone,
    (void_ptr_t)FinalizeLegendaryAnimal,
    (void_ptr_t)GetClass,
    (void_ptr_t)ToStringLegendaryAnimal,
    (void_ptr_t)SayHelloLegendaryAnimal,
    (void_ptr_t)GetNumMasters,
};

metadata_t legendary_metadata = { &legendary_v_table, "il.co.ilrd.Java2c.LegendaryAnimal@", sizeof(legendary_animal_t), &cat_metadata};

static int g_counter = 0;
static int g_is_loaded[NUM_OF_CLASSES] = {0};


/******************** object methods ************************/
object_t* AllocObject()
{
    object_t *obj = NULL;

    obj = (object_t*)malloc(sizeof(object_t));
    if (NULL == obj)
    {
        fprintf(stderr, "allocation failed\n");
        return NULL;
    }

    obj->class = NULL;

    return obj;
}


void Ctor(object_t* this)
{
    if(this->class == NULL)
    {
        this->class = &obj_metadata;
    }
}

int Equals(object_t* obj1, object_t* obj2)
{
    return obj1->class == obj2->class;
}

size_t HashCode(object_t* this)
{
    printf("printing hashcode\n");
    return this->class->size;
}

object_t* Clone(object_t* this)
{
    object_t *cloned_obj = NULL;

    cloned_obj = (object_t*)malloc(sizeof(object_t));
    if (NULL == cloned_obj)
    {
        fprintf(stderr, "allocation failed\n");
        return NULL;
    }

    cloned_obj->class = this->class;

    return cloned_obj;
}

void Finalize(object_t* this)
{
    free(this);
    this = NULL;
}

metadata_t* GetClass(object_t* this)
{
    return this->class;
}

const char* ToString(object_t* this)
{
    static char buffertostring[20];

    sprintf(buffertostring, "%s%ld\n", this->class->name, HashCode(this));

    return buffertostring;
}




/****************************animal methods********************************/
animal_t* AllocAnimal()
{   
    animal_t *animal = NULL;
    
    animal = (animal_t*)malloc(sizeof(animal_t));
    if (NULL == animal)
    {
        fprintf(stderr, "allocation failed\n");
        return NULL;
    }

    animal->id = 0;
    animal->num_legs = 0;
    animal->num_masters = 0;
    animal->super = AllocObject();

    return animal;
}


void CtorAnimalDefault(animal_t* this)
{
    AnimalPreCtor(this);
    printf("Animal ctor\n");
    this->id = ++g_counter;
    ((SayHello_Animal_t)(*this->super->class->func_table)[SAYHELLO])(this);
   ShowCounter();
    printf( "%s\n" ,((to_string_Animal_t)(*this->super->class->func_table)[TOSTRING])(this));
    printf("%s", ToString(this->super));
}

void CtorAnimalArgs(animal_t* this, int num_masters)
{
    AnimalPreCtor(this);

    printf("Animal ctor int\n");
    this->id = ++g_counter;
    this->num_masters = num_masters;
}



void AnimalPreCtor(animal_t* this)
{
    if(NULL == this->super->class)
    {
        this->super->class = &animal_metadata;
    }


  if(g_is_loaded[ANIMAL] == 0)
   {
       printf("Static block Animal 1\n");
       printf("Static block Animal 2\n");
       g_is_loaded[ANIMAL] = 1;
   }

   Ctor(this->super);
    printf("Instance initialization block Animal\n");

    this->num_legs = 5;
    this->num_masters = 1;
    this->id = 0;
}


void ShowCounter() /*not in v_table. this is a static func*/
{
    printf("%d\n", g_counter);
}

void SayHelloAnimal(animal_t* this)
{
    printf("Animal hello!\n");
    printf("I have %d legs\n", this->num_legs);
}

void FinalizeAnimal(animal_t* this)
{
    printf("finalize Animal with ID %d", this->id);
    Finalize(this->super);
    free(this);
    this = NULL;
}

const char* ToStringAnimal(animal_t* this)
{
    static char buffertostring[20];

    int to_string = this->id;
    sprintf(buffertostring, "Animal with ID: %d", to_string);

    return buffertostring;
}


int GetNumMasters(animal_t* this)
{
    return this->num_masters;
}




/*****************************dog methods********************************************/
dog_t* AllocDog()
{
    dog_t *dog = NULL;
    
    dog = (dog_t*)malloc(sizeof(dog_t));
    if (NULL == dog)
    {
        fprintf(stderr, "allocation failed\n");
        return NULL;
    }

   dog->colors = NULL;
   dog->num_legs = 0;
   dog->super = AllocAnimal();

    return dog;
}


void CtorDog(dog_t* this)
{
    if(NULL == this->super->super->class)
    {
        this->super->super->class = &dog_metadata;
    }


  if(g_is_loaded[DOG] == 0)
   {
       printf("Static block dog \n");
       g_is_loaded[DOG] = 1;
   }

    CtorAnimalArgs(this->super, 2);
    this->num_legs = 4;
    this->super->num_legs = 4;
    printf("Instance initialization block Dog\n");

    printf("Dog ctor\n");
}


void SayHelloDog(dog_t* this)
{
    /*this->num_legs = 4;*/
    printf("Dog Hello!\n");
    printf("I have %d legs\n", this->num_legs);
}


void FinalizeDog(dog_t* this)
{
    printf("Finalize dog with ID: %d\n", this->super->id);
    FinalizeAnimal(this->super);
    free(this);
    this = NULL;
}


const char* ToStringDog(dog_t* this)
{
    static char buffertostring[20];

    int to_string = ((animal_t *)this)->id;
    sprintf(buffertostring, "Dog with ID: %d", to_string);

    return buffertostring;
}

/*************************************cat methods*************************************/
cat_t* AllocCat()
{
    cat_t *cat = NULL;
    
    cat = (cat_t*)malloc(sizeof(cat_t));
    if (NULL == cat)
    {
        fprintf(stderr, "allocation failed\n");
        return NULL;
    }

   cat->colors = NULL;
   cat->num_masters = 0;
   cat->super = AllocAnimal();

    return cat;
}


void CtorCatDefault(cat_t* this)
{
    CtorCatArgs(this, "Black");
    printf("Cat ctor\n");
    this->num_masters = 2;

}


void CtorCatArgs(cat_t* this, const char* colors)
{
    PreCtor(this);
    this->colors = colors;
    printf("Cat ctor with color %s\n", colors);
}

void PreCtor(cat_t* this)
{
    if(this->super->super->class == NULL)
    {
        this->super->super->class = &cat_metadata;
    }

    if(!g_is_loaded[CAT])
    {
        printf("Static block Cat\n");
        g_is_loaded[CAT] = 1;
    }
    
    CtorAnimalDefault(this->super);

    this->num_masters = 5;
}


void FinalizeCat(cat_t* this)
{
    printf("Finalize cat with ID: %d", this->super->id);
    FinalizeAnimal(this->super);
    free(this);
    this = NULL;
}


const char* ToStringCat(cat_t* this)
{
    static char buffertostring[20];

    int to_string = ((animal_t *)this)->id;
    sprintf(buffertostring, "cat with ID: %d", to_string);

    return buffertostring;
}

/************************legendary animal methods*********************************/
legendary_animal_t* AllocLegendaryAnimal()
{
    legendary_animal_t *legendary_animal = NULL;
    
    legendary_animal = (legendary_animal_t*)malloc(sizeof(legendary_animal_t));
    if (NULL == legendary_animal)
    {
        fprintf(stderr, "allocation failed\n");
        return NULL;
    }

  legendary_animal->super = AllocCat();

    return legendary_animal;
}


void CtorLegendaryAnimal(legendary_animal_t* this)
{
    if(this->super->super->super->class == NULL)
    {
        this->super->super->super->class = &legendary_metadata;
    }

    if(!g_is_loaded[LEGENDARY_ANIMAL])
    {
        printf("Static block Legendary Animal\n");
        g_is_loaded[LEGENDARY_ANIMAL] = 1;
    }

    CtorCatDefault(this->super);
    printf("Legendary ctor\n");

}

const char* ToStringLegendaryAnimal(legendary_animal_t* this)
{
    static char buffertostring[20];

    int to_string = ((animal_t *)this)->id;
    sprintf(buffertostring, "legendary animal with ID: %d", to_string);
    return buffertostring;
}


void SayHelloLegendaryAnimal(legendary_animal_t* this)
{
    printf("Legendary Hello!\n");
}


void FinalizeLegendaryAnimal(legendary_animal_t* this)
{
    printf("finalize LegendaryAnimal with ID: %d\n",this->super->super->id);
    FinalizeCat(this->super);
    free(this);
    this = NULL;
}


/*****************Java2c methods*****************/
void foo(animal_t *animal)
{   
    printf( "%s\n" ,((to_string_Animal_t)(*animal->super->class->func_table)[TOSTRING])(animal));
}