
----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 369.536 | 0.108309 | 317.809ms | 1213 | 30 | 344.875 | 3130.43 | 0.350159 | 6.64806 | 1(Win) | true |
| simdjson (reflection) | 346.035 | 0.193708 | 341.268ms | 1213 | 4890 | 205063 | 3343.03 | 0.588076 | 7.09988 | 2(Loss) | true |
| Glaze | 300.996 | 0.030699 | 392.695ms | 1213 | 160 | 222.726 | 3843.27 | 0.112246 | 8.17053 | 3(Loss) | true |
