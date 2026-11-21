
----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2814.5 | 0.0445237 | 134.527ms | 3808 | 320 | 105.615 | 1290.32 | 0.165203 | 0.861643 | 1(Win) | true |
| Glaze | 2329.62 | 0.0875292 | 160.733ms | 3808 | 40 | 74.4712 | 1558.88 | 0.0133661 | 1.04478 | 2(Loss) | true |
| Jsonifier | 1949.53 | 0.144285 | 190.922ms | 3808 | 30 | 216.717 | 1862.8 | 0.0339874 | 1.25285 | 3(Loss) | true |
| simdjson (ondemand) | 1379.36 | 0.0402036 | 268.227ms | 3808 | 80 | 89.6304 | 2632.8 | 0.0208947 | 1.77806 | 4(Loss) | true |
