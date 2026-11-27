
----
### Prettify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4244.99 | 0.0861324 | 8477.51ms | 699405 | 640 | 1.17225e+07 | 157128 | 0.0174968 | 1.21013 | 4.75843 | 1.21762 | 0.00323032 | 0.000186096 | 1.38377e-05 | 1(Win) | true |
| Glaze | 3225.28 | 0.123749 | 5506.65ms | 699405 | 40 | 2.61978e+06 | 206805 | 0.0117637 | 1.5958 | 6.28688 | 1.35566 | 0.00206111 | 0.000747314 | 1.0366e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2489.83 | 0.136309 | 7731.52ms | 767297 | 640 | 1.02712e+08 | 293896 | 0.114914 | 2.03623 | 8.02298 | 1.07893 | 0.00367333 | 0.0951542 | 0.000158305 | 3(Loss) | true |
