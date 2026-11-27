
----
### CitmCatalog Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 22198.1 | 0.109746 | 2161.54ms | 500299 | 2560 | 1.42444e+06 | 21493.8 | 0.0144303 | 0.111395 | 1(Win) | true |
| simdjson (stage-1) | 18987.1 | 0.0659683 | 2527.79ms | 500299 | 4890 | 1.34376e+06 | 25128.8 | 0.0104301 | 0.130258 | 2(Loss) | true |
