
----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10533.3 | 0.223072 | 4523.7ms | 500299 | 640 | 6.53432e+06 | 45296.6 | 0.279675 | 0.234846 | 1(Win) | true |
| simdjson (reflection) | 8455.57 | 0.0534126 | 5683.2ms | 500299 | 4890 | 4.44191e+06 | 56427 | 0.015802 | 0.292639 | 2(Loss) | true |
| Glaze | 4071.26 | 0.156622 | 6009.57ms | 500299 | 1280 | 4.31239e+07 | 117193 | 0.146328 | 0.607946 | 3(Loss) | true |
