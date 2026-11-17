
----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2724.75 | 0.0976308 | 144.33ms | 3808 | 160 | 270.917 | 1332.82 | 0.0323667 | 0.889383 | 1(Win) | true |
| Glaze | 2212.4 | 0.23849 | 174.001ms | 3808 | 80 | 1226.02 | 1641.47 | 0.0777344 | 1.09901 | 2(Loss) | true |
| Jsonifier | 1884.29 | 0.08689 | 202.998ms | 3808 | 160 | 448.702 | 1927.3 | 0.00907924 | 1.29527 | 3(Loss) | true |
| simdjson (ondemand) | 1291.23 | 0.720762 | 287.966ms | 3808 | 640 | 262995 | 2812.5 | 0.0864254 | 1.89712 | 4(Loss) | true |
