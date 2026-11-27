
----
### Google Maps Response Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2211.93 | 0.119564 | 431.512ms | 9378 | 1280 | 29914.7 | 4043.32 | 0.0782893 | 1(Win) | true |
| Jsonifier | 1905.06 | 0.306513 | 402.068ms | 9378 | 320 | 66259.7 | 4694.62 | 0.499662 | 2(Loss) | true |
| simdjson (ondemand) | 1621.53 | 0.111331 | 558.604ms | 9378 | 2560 | 96524.7 | 5515.5 | 0.135292 | 3(Loss) | true |
| Glaze | 1542.61 | 0.179811 | 598.984ms | 9378 | 4890 | 531436 | 5797.68 | 0.39079 | 4(Loss) | true |
