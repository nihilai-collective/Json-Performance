
----
### CitmCatalog Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1409.01 | 0.149884 | 8884.23ms | 500299 | 320 | 8.24307e+07 | 338622 | 0.365323 | 3.5871 | 16.0981 | 3.00896 | 0.0157056 | 0.020669 | 0.000313712 | 1(Win) | true |
| simdjson (ondemand) | 1141.97 | 0.0763586 | 5419.92ms | 500299 | 160 | 1.62849e+07 | 417806 | 0.222385 | 4.40721 | 17.6965 | 3.05735 | 0.0236595 | 0.0285356 | 0.000125225 | 2(Loss) | true |
