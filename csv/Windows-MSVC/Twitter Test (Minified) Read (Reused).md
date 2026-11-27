
----
### Twitter Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1955.87 | 0.220959 | 6912.15ms | 466906 | 160 | 4.04878e+07 | 227662 | 0.478946 | 1.26565 | 1(Win) | true |
| Jsonifier (two-stage) | 1446.17 | 0.156388 | 9072.25ms | 466906 | 320 | 7.41958e+07 | 307901 | 0.195601 | 1.71176 | 2(Loss) | true |
| Glaze | 1414.76 | 0.479454 | 9123.49ms | 466906 | 30 | 6.83141e+07 | 314737 | 0.126929 | 1.74977 | 3(Loss) | true |
| simdjson (ondemand) | 1195.58 | 0.188466 | 5199.69ms | 466906 | 160 | 7.88293e+07 | 372435 | 0.490059 | 2.07059 | 4(Loss) | true |
