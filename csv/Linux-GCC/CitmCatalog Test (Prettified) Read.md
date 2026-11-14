
----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2774.12 | 0.124318 | 5043.5ms | 1151920 | 80 | 1.93889e+07 | 396002 | 0.173479 | 0.892361 | 1(Win) | true |
| simdjson (ondemand) | 2701.63 | 0.0712195 | 5230.82ms | 1151920 | 640 | 5.3675e+07 | 406628 | 0.241623 | 0.91631 | 2(Loss) | true |
