#ifndef SGE_MACROS_HPP
#define SGE_MACROS_HPP

#define TOTAL_POSSIBLE_COMPONENTS 6

#ifndef SGE_COMPONENT_MEMORY_BUFFER_SIZE
/*!
 * The free space in the vectors holding the components that is reserved at the beginning of each game loop
 * in order to avoid reallocation in critical phases of the loop
 */
    #define SGE_COMPONENT_MEMORY_BUFFER_SIZE 32000
#endif


#endif //SGE_MACROS_HPP
