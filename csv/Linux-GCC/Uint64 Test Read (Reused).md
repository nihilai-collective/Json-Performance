
----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1891.99 | 0.14199 | 64.1212ms | 1213 | 40 | 30.1481 | 611.425 | 0.0340618 | 1.25431 | 1(Win) | true |
| simdjson (reflection) | 1181.8 | 0.0688224 | 102.484ms | 1213 | 80 | 36.3063 | 978.85 | 0.0843537 | 2.03885 | 2(Loss) | true |
| Glaze | 1011.88 | 0.131309 | 116.667ms | 1213 | 80 | 180.278 | 1143.22 | 0 | 2.37242 | 3(Loss) | true |
| simdjson (ondemand) | 334.125 | 0.0320437 | 351.474ms | 1213 | 30 | 36.9241 | 3462.2 | 0.017333 | 7.3562 | 4(Loss) | true |
