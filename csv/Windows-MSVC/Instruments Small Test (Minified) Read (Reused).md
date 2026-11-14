
----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2677.69 | 0.177901 | 184.293ms | 4669 | 1280 | 11202 | 1662.89 | 0.164165 | 1.12375 | 1(Win) | true |
| Jsonifier (two-stage) | 1660.44 | 0.115254 | 287.272ms | 4669 | 1280 | 12227.2 | 2681.64 | 0.0902317 | 1.81741 | 2(Loss) | true |
| Glaze | 1620.68 | 0.140147 | 290.476ms | 4669 | 1280 | 18976.9 | 2747.42 | 0.331595 | 1.86097 | 3(Loss) | true |
| simdjson (ondemand) | 967.674 | 0.098333 | 475.441ms | 4669 | 4890 | 100114 | 4601.45 | 0.181291 | 3.12774 | 4(Loss) | true |
