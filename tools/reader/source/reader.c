/*
 *  xmlReader and Converter for Tiled map-editor
 * Quent42340
 * see COPYING
 * usage: reader <input map> <output map>
 * example: reader map.tmx map.map
 *
 */

#include <stdio.h>
#include <string.h>
#include <libxml/xmlreader.h>

#ifdef LIBXML_READER_ENABLED

char* outfilepath;

/**
 * processNode:
 * @reader: the xmlReader
 *
 * Dump information about the current node
 */
static void
processNode(xmlTextReaderPtr reader) {
    const xmlChar *name, *value;

    name = xmlTextReaderConstName(reader);
    if (name == NULL)
	name = BAD_CAST "--";

    value = xmlTextReaderConstValue(reader);

    /*printf("%d %d %s %d %d\n", 
	    xmlTextReaderDepth(reader),
	    xmlTextReaderNodeType(reader),
	    name,
	    xmlTextReaderIsEmptyElement(reader),
	    xmlTextReaderHasValue(reader));*/
		
    if(value != NULL) {
		if(xmlTextReaderNodeType(reader) == 3) {
			//printf("%s", xmlStrsub(value, 1, xmlStrlen(value)));
			unsigned short* table = (unsigned short*)malloc(xmlStrlen(value) / 2 * sizeof(unsigned short));
			char* tmp = (char*)malloc(5 * sizeof(char));
			char* preout = (char*)malloc(xmlStrlen(value) * sizeof(char));
			char* out = (char*)malloc(xmlStrlen(value) * sizeof(char));
			char* buffer = (char*)malloc(sizeof(char) * xmlStrlen(value) + 1);
			sprintf(buffer, "%s", value);
			// (Now buffer contains the map file)
			int counter = 0;
			char* token;
			unsigned short tile;
			const char delimiters[] = ",";
			token = strtok(buffer, delimiters);
			tile = (unsigned short)atof(token);
			table[counter] = tile - 1;
			sprintf(tmp, "%d,", table[counter]);
			strncat(preout, tmp, strlen(tmp));
			counter++;
			while(token != NULL){
				token = strtok(NULL, delimiters);
				if(token != NULL){
					tile = (unsigned short)atof(token);
					table[counter] = tile - 1;
					sprintf(tmp, "%d,", table[counter]);
					strncat(preout, tmp, strlen(tmp));
				}
				counter++;
			}
			free(buffer);
			//printf("%s\n", strncpy(out, preout, strlen(preout) - 1));
			
			FILE* file;
			file = fopen(outfilepath, "wb");
			//fwrite(out, sizeof(out), 1, file);
			//fprintf(file, "%s", strncpy(out, preout, strlen(preout) - 1));
			fwrite(table, 2, counter - 1, file);
			fclose(file);
		}
    }
}

/**
 * streamFile:
 * @filename: the file name to parse
 *
 * Parse and print information about an XML file.
 */
static void
streamFile(const char *filename) {
    xmlTextReaderPtr reader;
    int ret;

    reader = xmlReaderForFile(filename, NULL, 0);
    if (reader != NULL) {
        ret = xmlTextReaderRead(reader);
        while (ret == 1) {
            processNode(reader);
            ret = xmlTextReaderRead(reader);
        }
        xmlFreeTextReader(reader);
        if (ret != 0) {
            fprintf(stderr, "%s : failed to parse\n", filename);
        }
    } else {
        fprintf(stderr, "Unable to open %s\n", filename);
    }
}

int main(int argc, char **argv) {
    if (argc != 3) {
		printf("Usage: reader <input map> <output map>\n");
        return(1);
	}

    /*
     * this initialize the library and check potential ABI mismatches
     * between the version it was compiled for and the actual shared
     * library used.
     */
    LIBXML_TEST_VERSION

	outfilepath = argv[2];
    streamFile(argv[1]);

    /*
     * Cleanup function for the XML library.
     */
    xmlCleanupParser();
    /*
     * this is to debug memory for regression tests
     */
    xmlMemoryDump();
    return(0);
}

#else
int main(void) {
    fprintf(stderr, "XInclude support not compiled in\n");
    exit(1);
}
#endif
