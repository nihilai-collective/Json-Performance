
----
### Discord Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16952 | 0.13281 | 763.644ms | 7376 | 2560 | 777.506 | 414.954 | 0.648978 | 0.332047 | 1.09599 | 0.149268 | 0.000135575 | 2.52614e-05 | 7.25537e-06 | 1(Win) | true |
| Glaze | 3636.82 | 0.245145 | 919.669ms | 7376 | 2560 | 57555.1 | 1934.19 | 0.227294 | 1.43415 | 3.798 | 0.61307 | 0.000158453 | 3.52706e-05 | 1.48285e-05 | 2(Loss) | true |
| simdjson (reflection) | 527.622 | 0.151972 | 2077.46ms | 7376 | 1280 | 525449 | 13332.1 | 0.458037 | 9.7689 | 39.3871 | 8.02319 | 0.0130416 | 0.000117251 | 5.77252e-05 | 3(Loss) | true |
