
----
### Instruments Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3534.85 | 0.0624094 | 209.947ms | 7932 | 80 | 142.696 | 2139.99 | 0.26623 | 0.691566 | 1(Win) | true |
| Jsonifier (two-stage) | 3437.8 | 0.0775888 | 219.546ms | 7932 | 80 | 233.18 | 2200.4 | 0.0635843 | 0.711242 | 2(Loss) | true |
| simdjson (reflection) | 2552.36 | 0.0925516 | 296.04ms | 7932 | 40 | 300.962 | 2963.75 | 0.200034 | 0.961539 | 3(Loss) | true |
| Glaze | 2158.48 | 0.218848 | 358.663ms | 7932 | 40 | 2352.97 | 3504.57 | 0.0871908 | 1.13887 | 4(Loss) | true |
| simdjson (ondemand) | 1731.16 | 0.107853 | 438.965ms | 7932 | 30 | 666.309 | 4369.63 | 0.0602281 | 1.42094 | 5(Loss) | true |
