
----
### Google Maps Response Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3585.85 | 0.136024 | 680.205ms | 25388 | 4890 | 412491 | 6752.05 | 0.134434 | 0.687799 | 1(Win) | true |
| Jsonifier (two-stage) | 3300.09 | 0.0496321 | 786.01ms | 25388 | 30 | 397.789 | 7336.73 | 0.0868533 | 0.747427 | 2(Loss) | true |
| Glaze | 2451.24 | 0.0530626 | 987.92ms | 25388 | 40 | 1098.81 | 9877.4 | 0.0148509 | 1.00736 | 3(Loss) | true |
| simdjson (ondemand) | 2035.37 | 0.134191 | 1193.84ms | 25388 | 2560 | 652315 | 11895.5 | 0.0715886 | 1.2137 | 4(Loss) | true |
