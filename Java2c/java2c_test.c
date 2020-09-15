#include "java2c.h"
#include <stdio.h>
#include <stdlib.h> /* malloc */

#define NUM_OF_ANIMALS (5)

int main()
{
    size_t Hash = 0;
    object_t* obj = NULL;
    animal_t* animal = NULL;
    dog_t* dog = NULL;
    cat_t* cat = NULL;
    legendary_animal_t* legendary_animal = NULL;
    dog_t* dog_toarray = NULL;
    cat_t* cat_toarray = NULL;
    cat_t* cat2_toarray = NULL;
    legendary_animal_t *legendary_toarray = NULL;
    animal_t *animal_toarray = NULL;
    animal_t *animal_arr[5];
    int i = 5;

    obj = AllocObject();
    if (NULL == obj)
    {
        fprintf(stderr, "allocation failed\n");
        exit (1);
    }

    Ctor(obj);

    animal = AllocAnimal();
    if (NULL == animal)
    {
        fprintf(stderr, "allocation failed\n");
        exit (1);
    }

    CtorAnimalDefault(animal);

    dog = AllocDog();
    if (NULL == dog)
    {
        fprintf(stderr, "allocation failed\n");
        exit (1);
    }

    CtorDog(dog);


    cat = AllocCat();
    if (NULL == cat)
    {
        fprintf(stderr, "allocation failed\n");
        exit (1);
    }

    CtorCatDefault(cat);

    legendary_animal = AllocLegendaryAnimal();
    if (NULL == legendary_animal)
    {
        fprintf(stderr, "allocation failed\n");
        exit (1);
    }

    CtorLegendaryAnimal(legendary_animal);

    ShowCounter();

    printf("%d\n", animal->id);
    printf("%d\n", dog->super->id);
    printf("%d\n", cat->super->id);
    printf("%d\n", legendary_animal->super->super->id);


    dog_toarray = AllocDog();
    CtorDog(dog_toarray);
    cat_toarray = AllocCat();
    CtorCatDefault(cat_toarray);
    cat2_toarray = AllocCat();
    CtorCatArgs(cat2_toarray, "white");
   legendary_toarray = AllocLegendaryAnimal();
    CtorLegendaryAnimal(legendary_toarray);
    animal_toarray = AllocAnimal();
    CtorAnimalDefault(animal_toarray);


    animal_arr[0] = dog_toarray->super;
    animal_arr[1] = (animal_t *)cat_toarray->super;
    animal_arr[2] = (animal_t *)cat2_toarray->super;
    animal_arr[3] = (animal_t *)legendary_toarray->super->super;
    animal_arr[4] = (animal_t*)animal_toarray;
  
    
    for(i = 0; i < NUM_OF_ANIMALS; ++i)
    {
        ((SayHello_Animal_t)(*(animal_arr[i]->super->class->func_table))[SAYHELLO])(animal_arr[i]);
        printf("%d\n", ((GetNumMasters_Animal_t)(*(animal_arr[i]->super->class->func_table))[GETNUMMASTERS])(animal_arr[i]));
    }

    for(i = 0; i < NUM_OF_ANIMALS; ++i)
    {
       foo(animal_arr[i]);
    }
 

    return 0;
}