
----
### CitmCatalog Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1613.13 | 0.0960317 | 8655.92ms | 500299 | 160 | 1.29084e+07 | 295775 | 0.208692 | 3.14132 | 14.9927 | 2.73963 | 0.0108578 | 0.0155599 | 0.000237883 | 1(Win) | true |
| simdjson (ondemand) | 1285.39 | 0.0619757 | 5250.43ms | 500299 | 320 | 1.69348e+07 | 371187 | 0.0710532 | 3.90963 | 16.5796 | 2.78509 | 0.0173639 | 0.023734 | 5.8921e-05 | 2(Loss) | true |
