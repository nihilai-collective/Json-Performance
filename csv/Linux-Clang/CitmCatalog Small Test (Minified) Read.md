
----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1862.87 | 0.0412381 | 173.978ms | 3223 | 320 | 148.15 | 1649.97 | 0.25428 | 1.3079 | 1(Win) | true |
| Jsonifier (two-stage) | 1629.64 | 0.0801859 | 191.165ms | 3223 | 80 | 182.987 | 1886.11 | 0.121428 | 1.49803 | 2(Loss) | true |
| Glaze | 1367.22 | 0.0729722 | 226.28ms | 3223 | 80 | 215.301 | 2248.12 | 0.0990694 | 1.79015 | 3(Loss) | true |
| simdjson (ondemand) | 1082.58 | 0.112305 | 289.7ms | 3223 | 30 | 305.013 | 2839.23 | 0.213217 | 2.26678 | 4(Loss) | true |
