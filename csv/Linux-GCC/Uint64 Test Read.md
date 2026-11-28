
----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1578.2 | 0.729392 | 75.3909ms | 1213 | 1280 | 36587.3 | 732.991 | 0.151258 | 1.50968 | 1(Win) | true |
| simdjson (reflection) | 1007.02 | 0.13007 | 118.461ms | 1213 | 80 | 178.601 | 1148.74 | 0.111954 | 2.40004 | 2(Loss) | true |
| Glaze | 909.274 | 0.0614021 | 131.849ms | 1213 | 160 | 97.638 | 1272.23 | 0.0427216 | 2.65672 | 3(Loss) | true |
| simdjson (ondemand) | 300.705 | 0.123975 | 387.122ms | 1213 | 4890 | 111228 | 3846.98 | 0.128516 | 8.17507 | 4(Loss) | true |
