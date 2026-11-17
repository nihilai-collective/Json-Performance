
----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 708.009 | 0.0593282 | 8569.79ms | 500299 | 640 | 1.02302e+08 | 673893 | 0.00823042 | 4.2926 | 1(Win) | true |
| simdjson (ondemand) | 658.945 | 0.272068 | 9243.97ms | 500299 | 30 | 1.16423e+08 | 724070 | 0.125521 | 4.61235 | 2(Loss) | true |
