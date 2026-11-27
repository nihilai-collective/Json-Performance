
----
### Canada Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2103.13 | 0.0692116 | 935.932ms | 4630 | 160 | 337.836 | 2099.49 | 0.0645572 | 2.49683 | 7.67322 | 0.385097 | 0.000236231 | 7.42441e-05 | 2.69978e-06 | 1(Win) | true |
| simdjson (reflection) | 1784.47 | 0.0378872 | 969.404ms | 4630 | 640 | 562.48 | 2474.41 | 0.23624 | 2.94816 | 9.84125 | 0.57041 | 0.00022172 | 3.00351e-05 | 6.41199e-06 | 2(Loss) | true |
| Glaze | 1716.07 | 0.250347 | 977.719ms | 4630 | 30 | 1244.79 | 2573.03 | 0.363998 | 2.99482 | 9.48315 | 0.60432 | 0.000215983 | 6.47948e-05 | 0 | 3(Loss) | true |
