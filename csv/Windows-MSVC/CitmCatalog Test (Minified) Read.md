
----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 685.624 | 0.149281 | 8873.11ms | 500299 | 320 | 3.45339e+08 | 695895 | 0.0519295 | 4.43259 | 1(Win) | true |
| simdjson (ondemand) | 638.492 | 0.126251 | 9482.92ms | 500299 | 640 | 5.69636e+08 | 747264 | 0.143234 | 4.75983 | 2(Loss) | true |
