
----
### CitmCatalog Test (Minified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 20960.6 | 0.144168 | 2288.9ms | 500299 | 1280 | 1.37849e+06 | 22762.8 | 0.0573151 | 0.117972 | 1(Win) | true |
| simdjson (stage-1) | 17986.9 | 0.18262 | 2654.78ms | 500299 | 1280 | 3.00368e+06 | 26526.1 | 0.173819 | 0.137496 | 2(Loss) | true |
