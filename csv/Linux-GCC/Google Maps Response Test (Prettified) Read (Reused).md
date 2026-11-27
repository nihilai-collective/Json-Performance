
----
### Google Maps Response Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3045.18 | 0.0548448 | 1586.88ms | 25388 | 1280 | 24339.6 | 7950.89 | 0.00780119 | 1.69032 | 8.33796 | 1.45592 | 0.001675 | 1.87404e-05 | 8.43164e-06 | 1(Win) | true |
| simdjson (ondemand) | 2413.78 | 0.0938749 | 1802.98ms | 25388 | 40 | 3546.68 | 10030.7 | 0.0821488 | 2.14312 | 9.13802 | 1.58835 | 0.00358043 | 2.26485e-05 | 3.93887e-06 | 2(Loss) | true |
