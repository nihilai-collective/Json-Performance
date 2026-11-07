
----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2219.47 | 0.084582 | 5535.31ms | 500299 | 640 | 2.1159e+07 | 214971 | 0.444917 | 1.11527 | 1(Win) | true |
| Jsonifier (two-stage) | 1853.34 | 0.0933058 | 6588.84ms | 500299 | 1280 | 7.38543e+07 | 257439 | 0.76289 | 1.33561 | 2(Loss) | true |
| Glaze | 1566.89 | 0.0818938 | 7867.87ms | 500299 | 320 | 1.98992e+07 | 304503 | 0.00827543 | 1.5799 | 3(Loss) | true |
| simdjson (ondemand) | 1144.42 | 0.0985851 | 5313.64ms | 500299 | 160 | 2.7029e+07 | 416911 | 0.057826 | 2.16314 | 4(Loss) | true |
