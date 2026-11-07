
----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2319.51 | 0.144883 | 6724.1ms | 631514 | 320 | 4.52853e+07 | 259649 | 0.0851042 | 1.06721 | 1(Win) | true |
| Glaze | 1944.57 | 0.327146 | 8043.7ms | 631514 | 30 | 3.07981e+07 | 309713 | 0.100981 | 1.27304 | 2(Loss) | true |
| Jsonifier | 1681.71 | 0.089415 | 9187.03ms | 631514 | 1280 | 1.31248e+08 | 358122 | 0.0671219 | 1.47204 | 3(Loss) | true |
| simdjson (ondemand) | 1242.39 | 0.123619 | 6363.65ms | 631514 | 160 | 5.74574e+07 | 484759 | 0.147352 | 1.99261 | 4(Loss) | true |
