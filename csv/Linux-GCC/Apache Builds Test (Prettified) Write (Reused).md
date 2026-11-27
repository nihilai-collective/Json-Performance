
----
### Apache Builds Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18577 | 0.0343131 | 1436.32ms | 136037 | 2560 | 14700.2 | 6983.65 | 0.0722986 | 0.273705 | 0.925741 | 0.125084 | 5.01386e-05 | 2.60154e-06 | 8.55696e-07 | 1(Win) | true |
| Glaze | 8249.29 | 0.0197256 | 2310.22ms | 136076 | 4890 | 47086.9 | 15731.3 | 0.156726 | 0.614723 | 3.76371 | 0.630104 | 4.94371e-05 | 7.15347e-06 | 4.58062e-06 | 2(Loss) | true |
| simdjson (reflection) | 628.417 | 0.150195 | 5445.03ms | 136037 | 1280 | 1.23067e+08 | 206447 | 0.119454 | 8.01298 | 34.7252 | 7.10928 | 0.0278288 | 0.0282963 | 3.56865e-05 | 3(Loss) | true |
