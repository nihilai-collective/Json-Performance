
----
### Marine IK Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1235.52 | 0.170292 | 9284.91ms | 1922245 | 30 | 1.91525e+08 | 1.48374e+06 | 0.903142 | 2.00381 | 1(Win) | true |
| simdjson (reflection) DID NOT CONVERGE | 1079.22 | 0.518975 | 5415.68ms | 1922245 | 80 | 6.217e+09 | 1.69863e+06 | 2.68986 | 2.29402 | -(Loss) | false |
| Glaze | 895.823 | 0.23575 | 6115.49ms | 1833577 | 80 | 1.69413e+09 | 1.95199e+06 | 0.762813 | 2.76367 | 3(Loss) | true |
