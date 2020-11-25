#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS_GLOBALS
#include "SwitchMechanism.h"
#include "ServerMechanism.h"
#define MAX_INT 2147483647
/*The parametes:
 * switch or server 
 * if argv[1] == switch, then argc == 7 or argc == 8
 *      argv[1]: switch
 *      argv[2]: run_id  - a positive number greater than zero
 *      argv[3]: num_of_segment
 *      argv[4]: segment_lenght
 *      argv[5]: input_file_name
 *      argv[6]: segment_path
 *      argv[7]: optional: max_int
 *
 * if argv[1] == server, then argc == 7
 *      argv[1]: server
 *      argv[2]: run_id  - a positive number greater than zero
 *      argv[3]: num_of_ports
 *      argv[4]: segment_length
 *      argv[5]: k - sorting parameter
 *      argv[6]: input_files_directory - a path to the input files
 *      argv[7]: output_prefix_name - a path to the output file
 *
 * if argv[1] == validate, then argc == 4
 *      argv[1]: validate
 *      argv[2]: file_to_check_path
 *      argv[3]: size_of_file
 */
int main(int argc, char* argv[])
{
   // printf("\nhelloworldy\n");
    if (argc < 2) {
        printf("Too few arguments");
        return -1;
    }

    //printf("argc is: %d\n", argc);
    //for (int i = 0; i < argc; i++) {
    //    printf("argv[%d] is: %s\n",i, argv[i]);
    //}
    if (!(strcmp(argv[1], "switch") == 0 || strcmp(argv[1], "server") == 0
        || strcmp(argv[1], "validate") == 0)) {
        printf("Error: The first parameter should be 'switch' or 'server' or 'validate'");
        return -1;
    }
    if (strcmp(argv[1], "switch") == 0) {

        if (argc < 7) {
            printf("Error: Too few arguments");
            return -1;
        }

        if (argc > 8) {
            printf("Error: Too many arguments");
            return -1;
        }

        int run_id;
        int num_of_segments;
        int segment_length;
        char* input_file_name = argv[5];
        char* segments_path = argv[6];
        FILE* input_file = NULL;
        int maximum_value = MAX_INT;

        run_id = atoi(argv[2]);
        if (run_id < 1) {
            printf("Error: The second parameter is illegal.\n Run ID should be an integer greater than zero");
            return -1;
         }   

        num_of_segments = atoi(argv[3]);
        if (num_of_segments < 1) {
            printf("Error: The third parameter is illegal.\n Number of segments should be an integer greater than zero");
            return -1;
        }

        segment_length = atoi(argv[4]);
        if (segment_length < 1) {
            printf("Error: The fourth parameter is illegal.\n The lenght of segments should be an integer greater than zero");
            return -1;
        }

        input_file = fopen(input_file_name, "r");
        if (input_file == NULL) {
            printf("Error: The fifth parameter should be a path to a pointer to an input file");
            return -1;
        }

        if (argc == 8) {
            maximum_value = atoi(argv[7]);
            if (maximum_value < 1) {
                fclose(input_file);
                printf("Error: The sixth parameter is illegal.\n Maximum value should be an integer greater than zero");
                return -1;
            }
        }
//      printf("call mechanism apply switch");
       mechanism_results res = mehcanism_apply_switch_flow(run_id, num_of_segments, segment_length,
           input_file, segments_path, maximum_value);
       fclose(input_file);
       if (res != MECHANISM_SUCCESS) {
           return -1;
       }
     
    }
    if (strcmp(argv[1], "server") == 0) {
        if (argc < 8) {
            printf("Error: Too few arguments");
            return -1;
        }

        if (argc > 8) {
            printf("Error: Too many arguments");
            return -1;
        }
        int run_id;
        int num_of_segments;
        int segment_length;
        int k;
        char* input_files_directory = argv[6];
        char* output_prefix_name = argv[7];

        run_id = atoi(argv[2]);
        if (run_id < 1) {
            printf("Error: The first parameter is illegal.\n Run ID should be an integer greater than zero");
            return -1;
        }
        num_of_segments = atoi(argv[3]);
        if (num_of_segments < 1) {
            printf("Error: The second parameter is illegal.\n Number of segments should be an integer greater than zero");
            return -1;
        }

        segment_length = atoi(argv[4]);
        if (segment_length < 1) {
            printf("Error: The third parameter is illegal.\n The lenght of segments should be an integer greater than zero");
            return -1;
        }

        k = atoi(argv[5]);
        if (k < 1) {
            printf("Error: The fourth parameter is illegal.\n The lenght of segments should be an integer greater than zero");
            return -1;
        }

        mechanism_results res = mechanism_apply_server_flow(run_id, num_of_segments, segment_length, k,
           input_files_directory, output_prefix_name);
    
    }

    if (strcmp(argv[1], "validate") == 0) {
        if (argc < 4) {
            printf("Error: Too few arguments");
            return -1;
        }

        if (argc > 4) {
            printf("Error: Too many arguments");
            return -1;
        }

        char* file_to_check_path = argv[2];
        int size_of_file = atoi(argv[3]);
        check_if_sorted(file_to_check_path, size_of_file);
    }
    //printf("success new version\n");//for_release
	return 0;
}