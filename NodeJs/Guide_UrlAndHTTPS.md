##URL and HTTPS :

1. Creating new Url with base and added path.
 ```javascript
 const myURL = new URL('/foo', 'https://example.org/');
 // https://example.org/foo
 ```

 2. To encode a url query :
 `querystring.stringify(obj[, sep[, eq[, options]]])`

 3. Make a post request to a server : 
 ```javascript
 const https = require('https')

const data = JSON.stringify({
  todo: 'Buy the milk'
})

const options = {
  hostname: 'whatever.com',
  port: 443,
  path: '/todos',
  method: 'POST',
  headers: {
    'Content-Type': 'application/json',
    'Content-Length': data.length
  }
}

const req = https.request(options, res => {
  console.log(`statusCode: ${res.statusCode}`)

  res.on('data', d => {
    process.stdout.write(d)
  })
})

req.on('error', error => {
  console.error(error)
})

req.write(data)
req.end()
```