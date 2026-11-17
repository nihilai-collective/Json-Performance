
----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9094.18 | 0.123706 | 35.4881ms | 3223 | 320 | 55.9402 | 337.984 | 0.0434373 | 0.249927 | 1(Win) | true |
| simdjson (reflection) | 7097.69 | 0.0474209 | 46.0004ms | 3223 | 1280 | 53.9805 | 433.055 | 0.0276095 | 0.326588 | 2(Loss) | true |
| Glaze | 2892.52 | 0.0609908 | 107.575ms | 3223 | 320 | 134.414 | 1062.63 | 0.0626784 | 0.83366 | 3(Loss) | true |
