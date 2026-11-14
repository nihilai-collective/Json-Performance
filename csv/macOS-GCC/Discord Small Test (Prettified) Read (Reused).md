
----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2242.54 | 0.350362 | 349.238ms | 6701 | 2560 | 255194 | 2849.7 | 1.83603 | 1(Win) | true |
| Jsonifier (two-stage) | 2091.84 | 0.190755 | 359.844ms | 6701 | 2560 | 86938.6 | 3055 | 0.0327225 | 2(Loss) | true |
| Glaze | 2067.68 | 0.339831 | 361.715ms | 6701 | 2560 | 282410 | 3090.7 | 2.90671 | 3(Loss) | true |
| simdjson (ondemand) | 1491.8 | 0.383902 | 486.127ms | 6701 | 1280 | 346186 | 4283.8 | 0.0793058 | 4(Loss) | true |
| simdjson (reflection) | 1377.28 | 1.63165 | 480.832ms | 6701 | 80 | 458545 | 4640 | 0.820793 | 5(Loss) | true |
