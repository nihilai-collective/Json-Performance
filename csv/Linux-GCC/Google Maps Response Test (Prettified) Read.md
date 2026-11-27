
----
### Google Maps Response Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3855.35 | 0.0524755 | 1362.62ms | 25388 | 2560 | 27802.4 | 6280.07 | 0.0240224 | 1.31494 | 6.30479 | 1.06988 | 0.00281517 | 1.60632e-05 | 5.72367e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 3110.06 | 0.125336 | 1517.64ms | 25388 | 40 | 3808.28 | 7785.02 | 0.00331845 | 1.63473 | 7.92445 | 1.18828 | 0.00322987 | 7.87774e-06 | 0 | 2(Loss) | true |
| simdjson (reflection) | 3058.65 | 0.141487 | 1531.11ms | 25388 | 30 | 3763.15 | 7915.87 | 0.0379129 | 1.66176 | 6.74297 | 0.99614 | 0.00214274 | 1.18166e-05 | 1.31296e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2397.39 | 0.0226419 | 1786.86ms | 25388 | 4890 | 25569 | 10099.3 | 0.0183892 | 2.11904 | 8.74065 | 1.46731 | 0.00325193 | 1.53447e-05 | 6.79032e-06 | 4(Loss) | true |
| Glaze | 2389.08 | 0.0513351 | 1744.97ms | 25388 | 1280 | 34644.4 | 10134.4 | 0.000971313 | 2.12262 | 9.43428 | 1.81346 | 0.00572133 | 3.94502e-05 | 1.84327e-05 | 5(Loss) | true |
