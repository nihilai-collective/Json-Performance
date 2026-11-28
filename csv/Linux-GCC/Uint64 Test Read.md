
----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1689.51 | 0.130095 | 71.1167ms | 1213 | 30 | 23.8034 | 684.7 | 0.043834 | 1.41311 | 1(Win) | true |
| simdjson (reflection) | 1044.02 | 0.100413 | 112.903ms | 1213 | 30 | 37.1368 | 1108.03 | 0.00300842 | 2.31833 | 2(Loss) | true |
| Glaze | 967.931 | 0.288594 | 123.126ms | 1213 | 2560 | 30454.2 | 1195.13 | 0.0136276 | 2.49407 | 3(Loss) | true |
| simdjson (ondemand) | 323.358 | 0.05352 | 363.616ms | 1213 | 160 | 586.553 | 3577.48 | 0.0546524 | 7.60186 | 4(Loss) | true |
