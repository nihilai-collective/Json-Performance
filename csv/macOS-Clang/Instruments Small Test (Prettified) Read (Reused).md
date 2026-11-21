
----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2872.18 | 0.291238 | 305.57ms | 7932 | 320 | 18827.2 | 2633.72 | 0.873012 | 1(Win) | true |
| Jsonifier (two-stage) | 2278.2 | 1.06269 | 352.023ms | 7932 | 2560 | 3.18741e+06 | 3320.41 | 0.899491 | 2(Loss) | true |
| Glaze | 1557.46 | 2.48845 | 478.81ms | 7932 | 30 | 438238 | 4856.97 | 1.13045 | 3(Loss) | true |
| simdjson (ondemand) | 977.523 | 0.450659 | 834.485ms | 7932 | 2560 | 3.11349e+06 | 7738.48 | 0.47306 | 4(Loss) | true |
