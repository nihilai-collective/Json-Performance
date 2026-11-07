
----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 7474.91 | 0.146253 | 51.8814ms | 3808 | 80 | 40.391 | 485.837 | 0.125912 | 0.31294 | 1(Win) | true |
| Jsonifier | 7243.82 | 0.164396 | 52.5077ms | 3808 | 1280 | 869.464 | 501.337 | 0.511083 | 0.323007 | 2(Loss) | true |
| Jsonifier (two-stage) | 7205.33 | 0.122046 | 53.7567ms | 3808 | 1280 | 484.329 | 504.015 | 0.458103 | 0.3249 | 3(Loss) | true |
| Glaze | 3778.55 | 0.372565 | 100.82ms | 3808 | 2560 | 32823.9 | 961.108 | 0.623738 | 0.637146 | 4(Loss) | true |
