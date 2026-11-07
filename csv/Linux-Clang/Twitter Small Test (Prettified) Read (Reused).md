
----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3076.22 | 0.130351 | 125.974ms | 3808 | 80 | 189.442 | 1180.54 | 0.10918 | 0.786699 | 1(Win) | true |
| Glaze | 2514.45 | 0.0693171 | 153.743ms | 3808 | 80 | 80.1821 | 1444.29 | 0.0597537 | 0.966689 | 2(Loss) | true |
| Jsonifier | 2083.44 | 0.124923 | 183.77ms | 3808 | 40 | 189.661 | 1743.08 | 0.0358433 | 1.17142 | 3(Loss) | true |
| simdjson (ondemand) | 1364.75 | 0.197482 | 273.519ms | 3808 | 2560 | 70694.6 | 2661 | 0.0945501 | 1.79458 | 4(Loss) | true |
