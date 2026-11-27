
----
### Canada Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2030.54 | 0.148931 | 947.807ms | 4630 | 40 | 419.536 | 2174.55 | 0.11254 | 2.53739 | 7.78488 | 0.411231 | 0.00024838 | 1.07991e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 1740.49 | 0.0541292 | 978.192ms | 4630 | 4890 | 9221.25 | 2536.93 | 0.123983 | 2.98416 | 9.91037 | 0.586826 | 0.000226318 | 5.23394e-05 | 2.09799e-05 | 2(Loss) | true |
| Glaze | 1542.56 | 0.0409399 | 1013.27ms | 4630 | 4890 | 6715.56 | 2862.46 | 0.0342402 | 3.34804 | 10.0108 | 0.722895 | 0.000220355 | 7.61902e-05 | 2.53084e-05 | 3(Loss) | true |
