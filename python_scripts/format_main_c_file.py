import re
import os


def main():
    try:
        replace_c_file()
    except FileNotFoundError:
        print("Source file or output file doesn't exist!")
    except FileExistsError:
        print("Output file exists!")


def replace_c_file(src="../main.c",
                   out="../formatted_main.c",
                   template="../main_full_template.c"):

    # Check to ensure src and template files exist, and out file does not exist
    if os.path.isfile(out):
        raise FileExistsError

    if not os.path.isfile(src) or not os.path.isfile(template):
        raise FileNotFoundError

    # Regular expressions definitions
    re_includes = re.compile("/\* USER CODE BEGIN Includes \*/.*/\* USER CODE END Includes \*/", re.DOTALL)
    re_typedefs = re.compile("/\* USER CODE BEGIN PTD \*/.*/\* USER CODE END PTD \*/", re.DOTALL)
    re_defines = re.compile("/\* USER CODE BEGIN PD \*/.*/\* USER CODE END PD \*/", re.DOTALL)
    re_variables = re.compile("/\* USER CODE BEGIN PV \*/.*/\* USER CODE END PV \*/", re.DOTALL)
    re_init_code = re.compile("/\* USER CODE BEGIN 2 \*/.*/\* USER CODE END 2 \*/", re.DOTALL)
    re_while_code = re.compile("/\* USER CODE BEGIN WHILE \*/.*/\* USER CODE END WHILE \*/", re.DOTALL)

    re_list = [re_includes, re_typedefs, re_defines,
               re_variables, re_init_code, re_while_code]

    # Attempt to find main file, search for user written code
    with open(src, "r") as input_file:
        file_txt = input_file.read()
        input_file_list = [re.search(re_item, file_txt).group()
                           for re_item in re_list]

    # Writes to new main file
    with open(template, "r") as template_file:
        with open(out, "w") as write_file:
            template_txt = template_file.read()

            for re_item, input_item in zip(re_list, input_file_list):
                template_txt = re_item.sub(input_item, template_txt)

            write_file.write(template_txt)

    # Done!
    print("Done!")


if __name__ == "__main__":
    main()