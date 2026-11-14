
----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 759.914 | 0.0342132 | 491.8ms | 3873 | 40 | 110.615 | 4860.52 | 0.167226 | 3.23958 | 1(Win) | true |
| simdjson (ondemand) | 449.784 | 0.18428 | 826.003ms | 3873 | 1280 | 293124 | 8211.9 | 0.0208686 | 5.48639 | 2(Loss) | true |
