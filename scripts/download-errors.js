const fs = require('fs');
const https = require('https');

const url = 'https://e.bambulab.com/query.php?lang=en';
const hmsDataFileC = 'src/xtouch/bbl/bbl-errors.c';
const hmsDataFileH = 'src/xtouch/bbl/bbl-errors.h';

// StatusPanel.cpp
const message_containing_retry = [
    "07018004",
    "07018005",
    "07018006",
    "07018006",
    "07018007",
    "07008012",
    "07018012",
    "07028012",
    "07038012",
    "07FF8003",
    "07FF8004",
    "07FF8005",
    "07FF8006",
    "07FF8007",
    "07FF8010",
    "07FF8011",
    "07FF8012",
    "07FF8013",
    "12FF8007"
];
const message_containing_done = [
    "07FF8007",
    "12FF8007"
];


const getFlatRecordsKeysC = (root, varName) => {
    return `const char *${varName}[] PROGMEM = {${JSON.stringify(root.map((e) => String(e.ecode)), null, 2).slice(1, -1)}};`;
}
const getFlatRecordsKeysH = (root, varName) => {
    return `extern const char *${varName}[] PROGMEM;`;
}
const getFlatRecordsValuesC = (root, varName = 0) => {
    return `const char *${varName}[] PROGMEM = {${JSON.stringify(root.map((e) => String(e.intro)), null, 2).slice(1, -1)}};`;
}
const getFlatRecordsValuesH = (root, varName = 0) => {
    return `extern const char *${varName}[] PROGMEM;`;
}

const getKeyValueLengthC = (root, varName) => {
    return `int ${varName} = ${root.length};`;
}
const getKeyValueLengthH = (root, varName) => {
    return `extern int ${varName};`;
}


https.get(url, (response) => {
    if (response.statusCode === 200) {
        let data = '';

        response.on('data', (chunk) => {
            data += chunk;
        });

        response.on('end', () => {

            // data = data.replace(/ /g);
            const dataObject = JSON.parse(data);
            const device_hms = dataObject.data.device_hms.en;
            const device_error = dataObject.data.device_error.en;

            const outputC = [
                `
#include <pgmspace.h>
`,
                getKeyValueLengthC(device_hms, "hms_error_length"),
                getFlatRecordsKeysC(device_hms, "hms_error_keys"),
                getFlatRecordsValuesC(device_hms, "hms_error_values"),
                getKeyValueLengthC(device_error, "device_error_length"),
                getFlatRecordsKeysC(device_error, "device_error_keys"),
                getFlatRecordsValuesC(device_error, "device_error_values"),
                `int message_containing_retry_total = ${message_containing_retry.length};`,
                `int message_containing_done_total = ${message_containing_done.length};`,
                `const char *message_containing_retry[] PROGMEM = {
${JSON.stringify(message_containing_retry, null, 2).slice(1, -1)}
};
const char *message_containing_done[] PROGMEM = {
${JSON.stringify(message_containing_done, null, 2).slice(1, -1)}
};`
            ].join('\n\n');


            fs.writeFileSync(hmsDataFileC, outputC);


            const outputH = [
                `#ifndef _XLCD_BBL_ERRORS
#define _XLCD_BBL_ERRORS

#ifdef __cplusplus
extern "C"
{
#endif

#include <pgmspace.h>`,
                getKeyValueLengthH(device_hms, "hms_error_length"),
                getFlatRecordsKeysH(device_hms, "hms_error_keys"),
                getFlatRecordsValuesH(device_hms, "hms_error_values"),
                getKeyValueLengthH(device_error, "device_error_length"),
                getFlatRecordsKeysH(device_error, "device_error_keys"),
                getFlatRecordsValuesH(device_error, "device_error_values"),
                `extern int message_containing_retry_total;`,
                `extern int message_containing_done_total;`,
                `extern const char *message_containing_retry[] PROGMEM;`,
                `extern const char *message_containing_done[] PROGMEM;`,
                `#ifdef __cplusplus
}
#endif

#endif`
            ].join('\n\n');
            fs.writeFileSync(hmsDataFileH, outputH);
            console.log('[xtouch error downloader] Done!!');
        });
    } else {
        console.error('[xtouch error downloader] Error al descargar el archivo. Código de estado:', response.statusCode);
    }
}).on('error', (error) => {
    console.error('[xtouch error downloader] Error al realizar la solicitud:', error);
});

