
----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 995.617 | 0.08193 | 828.605ms | 1213 | 320 | 289.984 | 1161.9 | 0.0360531 | 5.34074 | 28.4419 | 5.63067 | 0.00179823 | 0.00010305 | 1.28813e-05 | 1(Win) | true |
| simdjson (ondemand) | 389.391 | 0.0226928 | 1015.93ms | 1213 | 320 | 145.438 | 2970.81 | 0.00504887 | 13.4082 | 57.2597 | 11.4946 | 0.00634532 | 0.000193219 | 1.28813e-05 | 2(Loss) | true |
