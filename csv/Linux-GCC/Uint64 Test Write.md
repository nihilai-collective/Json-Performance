
----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 355.208 | 0.241756 | 329.111ms | 1213 | 1280 | 79345.3 | 3256.7 | 0.00244694 | 6.91478 | 1(Win) | true |
| simdjson (reflection) | 349.011 | 0.0950758 | 378.673ms | 1213 | 40 | 397.23 | 3314.53 | 0.0736114 | 7.04207 | 2(Loss) | true |
| Glaze | 296.349 | 0.140533 | 408.182ms | 1213 | 30 | 902.809 | 3903.53 | 0.02477 | 8.29651 | 3(Loss) | true |
