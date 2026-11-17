
----
### Google Maps Response Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1199.61 | 0.20477 | 5361.45ms | 4203059 | 80 | 3.74519e+09 | 3.34138e+06 | 0.155488 | 4.23472 | 17.8451 | 3.41887 | 0.0146411 | 0.0899235 | 0.0134879 | 1(Win) | true |
| simdjson (ondemand) | 951.688 | 0.107562 | 6721.98ms | 4203059 | 30 | 6.15718e+08 | 4.21183e+06 | 0.344963 | 5.32496 | 20.4366 | 3.55463 | 0.0271071 | 0.0891833 | 0.00137799 | 2(Loss) | true |
