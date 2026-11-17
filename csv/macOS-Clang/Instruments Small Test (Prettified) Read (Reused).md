
----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3116.7 | 0.133718 | 279.101ms | 7932 | 40 | 421.323 | 2427.1 | 0.0879737 | 1(Win) | true |
| Jsonifier (two-stage) | 2779.7 | 0.100562 | 319.492ms | 7932 | 80 | 599.142 | 2721.35 | 0.134305 | 2(Loss) | true |
| Glaze | 1758.38 | 0.378502 | 464.068ms | 7932 | 1280 | 339379 | 4301.99 | 2.24129 | 3(Loss) | true |
| simdjson (ondemand) | 1047.58 | 0.68907 | 841.233ms | 7932 | 640 | 1.58452e+06 | 7220.96 | 2.22998 | 4(Loss) | true |
