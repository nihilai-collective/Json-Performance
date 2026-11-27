
----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 343.15 | 0.0543478 | 1055.94ms | 1213 | 2560 | 8593.24 | 3371.14 | 0.0495345 | 15.1731 | 73.4823 | 16.1113 | 0.0179633 | 0.000315914 | 8.30843e-05 | 1(Win) | true |
| Jsonifier | 338.841 | 0.0336827 | 1057.08ms | 1213 | 4890 | 6466.24 | 3414.01 | 0.065921 | 15.3991 | 73.451 | 16.2036 | 0.0205817 | 0.000287445 | 5.88377e-05 | 2(Loss) | true |
| Glaze | 296.666 | 0.0589829 | 1107.95ms | 1213 | 1280 | 6770.96 | 3899.36 | 0.0339684 | 17.5334 | 84.5787 | 17.6496 | 0.0333748 | 0.000407049 | 0.000171321 | 3(Loss) | true |
