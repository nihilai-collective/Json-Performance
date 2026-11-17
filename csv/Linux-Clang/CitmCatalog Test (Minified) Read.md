
----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1993.15 | 0.17155 | 6237.54ms | 500299 | 160 | 2.69825e+07 | 239382 | 0.343977 | 1.24191 | 1(Win) | true |
| Jsonifier (two-stage) | 1744.21 | 0.19494 | 6996.64ms | 500299 | 160 | 4.54972e+07 | 273547 | 0.303297 | 1.41918 | 2(Loss) | true |
| Glaze | 1412.66 | 0.187236 | 8623.97ms | 500299 | 80 | 3.19927e+07 | 337747 | 0.629593 | 1.75239 | 3(Loss) | true |
| simdjson (ondemand) | 1051.22 | 0.215962 | 5862.2ms | 500299 | 40 | 3.84314e+07 | 453875 | 0.204283 | 2.35492 | 4(Loss) | true |
