
----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3182.12 | 0.145235 | 9866.86ms | 1151920 | 160 | 4.02232e+07 | 345228 | 0.185978 | 1.58447 | 7.52399 | 1.27505 | 0.00430977 | 0.0297747 | 6.32097e-06 | 1(Win) | true |
| simdjson (ondemand) | 2841.58 | 0.0926765 | 5450.85ms | 1151920 | 80 | 1.02696e+07 | 386600 | 0.172929 | 1.80732 | 7.98506 | 1.20223 | 0.00636829 | 0.0307527 | 4.10185e-06 | 2(Loss) | true |
