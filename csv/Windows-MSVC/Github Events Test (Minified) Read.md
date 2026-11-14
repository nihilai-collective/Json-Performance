
----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 666.119 | 0.413406 | 7677.33ms | 53331 | 2560 | 2.55064e+08 | 76353.3 | 0.775832 | 3.71515 | 1(Win) | true |
| simdjson (ondemand) | 565.702 | 0.46248 | 9088.04ms | 53331 | 1280 | 2.21299e+08 | 89906.7 | 0.152356 | 4.37493 | 2(Loss) | true |
