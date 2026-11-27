
----
### Instruments Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 26232.5 | 0.10365 | 1522.72ms | 213963 | 30 | 1950.12 | 7778.57 | 0.107445 | 0.19729 | 0.640377 | 0.0752747 | 4.34655e-05 | 1.86948e-06 | 0 | 1(Win) | true |
| Glaze | 5476.72 | 0.0952347 | 4467.91ms | 213963 | 1280 | 1.61153e+06 | 37257.9 | 0.0136781 | 0.924171 | 3.59472 | 0.575403 | 0.000533325 | 7.62033e-06 | 4.13331e-06 | 2(Loss) | true |
| simdjson (reflection) | 482.807 | 0.238773 | 5482.7ms | 213963 | 640 | 6.51751e+08 | 422635 | 0.00140453 | 10.3927 | 41.6024 | 8.43663 | 0.0402134 | 0.206985 | 0.00032464 | 3(Loss) | true |
