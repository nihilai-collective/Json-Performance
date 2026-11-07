
----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1783.81 | 0.33253 | 175.629ms | 3223 | 1280 | 42023.8 | 1723.1 | 0.0612164 | 1.36654 | 1(Win) | true |
| Jsonifier (two-stage) | 1597.16 | 0.236641 | 194.854ms | 3223 | 2560 | 53093.8 | 1924.47 | 0.0612555 | 1.52843 | 2(Loss) | true |
| Glaze | 1382.75 | 0.0457575 | 227.238ms | 3223 | 320 | 331.062 | 2222.88 | 0.0775213 | 1.76942 | 3(Loss) | true |
| simdjson (ondemand) | 1086.48 | 0.138822 | 287.295ms | 3223 | 40 | 616.948 | 2829.03 | 0.369864 | 2.25693 | 4(Loss) | true |
