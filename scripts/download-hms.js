const fs = require('fs');
const https = require('https');

const url = 'https://e.bambulab.com/query.php?lang=en';
const hmsJsonFile = 'resources/hms.json';
const deviceErrorFile = 'resources/device_error';
const hmsErrorFile = 'resources/hms_error';


const getFlatRecordsKeys = (root, varName) => {
    return `const char *${varName}[] PROGMEM = {${JSON.stringify(root.map((e) => String(e.ecode)), null, 2).slice(1, -1)}};`;
}
const getFlatRecordsValues = (root, varName = 0) => {
    return `const char *${varName}[] PROGMEM = {${JSON.stringify(root.map((e) => String(e.intro)), null, 2).slice(1, -1)}};`;
}

const getKeyValueLength = (root, varName) => {
    return `uint16_t ${varName} = ${root.length};`;
}

// Check the local file's modification time
let localModTime = null;
try {
    const stats = fs.statSync(hmsJsonFile);
    localModTime = stats.mtime.toUTCString();
} catch (err) {
    // File doesn't exist locally
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

            const output = [
                getKeyValueLength(device_hms, "hms_error_length"),
                getFlatRecordsKeys(device_hms, "hms_error_keys"),
                getFlatRecordsValues(device_hms, "hms_error_values"),
                getKeyValueLength(device_error, "device_error_length"),
                getFlatRecordsKeys(device_error, "device_error_keys"),
                getFlatRecordsValues(device_error, "device_error_values")
            ].join('\n\n');

            fs.writeFileSync(hmsJsonFile, data, 'utf8');
            fs.writeFileSync(hmsErrorFile + '.key.db', output);

        });
    } else {
        console.error('Error al descargar el archivo. Código de estado:', response.statusCode);
    }
}).on('error', (error) => {
    console.error('Error al realizar la solicitud:', error);
});

