
----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6381.83 | 0.0415222 | 9396.28ms | 9930848 | 160 | 6.07522e+07 | 1.48402e+06 | 0.0155282 | 0.792319 | 2.51816 | 0.14758 | 0.000359036 | 0.0249858 | 0.000615677 | 1(Win) | true |
| Glaze | 4057.68 | 0.181548 | 7266.36ms | 9930228 | 80 | 1.43627e+09 | 2.3339e+06 | 0.128465 | 1.24418 | 4.4153 | 0.474313 | 0.000796453 | 0.0223812 | 0.000414142 | 2(Loss) | true |
| simdjson (reflection) | 308.654 | 1.9939 | 9343.8ms | 10018896 | 30 | 1.14294e+13 | 3.09562e+07 | 0.630312 | 13.1675 | 38.7853 | 5.80152 | 0.0259537 | 0.291642 | 0.129552 | 3(Loss) | true |
