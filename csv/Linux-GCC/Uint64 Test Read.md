
----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1336.22 | 0.209095 | 989.697ms | 3873 | 2560 | 85519.9 | 2764.2 | 0.0372228 | 3.90025 | 18.1479 | 2.00646 | 0.00110521 | 5.0631e-05 | 4.63949e-06 | 1(Win) | true |
| simdjson (ondemand) | 744.176 | 0.0501307 | 1210.2ms | 3873 | 1280 | 7924.31 | 4963.32 | 0.00939795 | 6.97442 | 31.7565 | 3.66357 | 0.00553854 | 6.65666e-05 | 1.49271e-05 | 2(Loss) | true |
