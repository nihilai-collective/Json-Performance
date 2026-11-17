
----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 952.655 | 0.051474 | 389.949ms | 3862 | 30 | 118.809 | 3866.13 | 0.103356 | 2.58091 | 1(Win) | true |
| simdjson (reflection) | 891.144 | 0.148433 | 416.883ms | 3862 | 4890 | 184034 | 4132.99 | 0.626712 | 2.76073 | 2(Loss) | true |
| Glaze | 775.906 | 0.140368 | 493.125ms | 3862 | 4890 | 217098 | 4746.83 | 0.153386 | 3.17316 | 3(Loss) | true |
