
----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1967.02 | 0.0645664 | 895.649ms | 18245 | 30 | 978.599 | 8845.77 | 0.00150729 | 1(Win) | true |
| Jsonifier | 1459.38 | 0.499299 | 945.518ms | 18245 | 320 | 1.13403e+06 | 11922.8 | 0.298507 | 2(Loss) | true |
| Glaze | 1228.1 | 0.0962694 | 1444.42ms | 18245 | 30 | 5581.07 | 14168 | 0.03951 | 3(Loss) | true |
| simdjson (ondemand) | 1221.22 | 0.062698 | 1528.56ms | 18245 | 40 | 3192.03 | 14247.9 | 0.00386008 | 4(Loss) | true |
