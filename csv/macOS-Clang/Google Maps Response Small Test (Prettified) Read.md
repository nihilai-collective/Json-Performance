
----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2307.98 | 2.5363 | 373.758ms | 9378 | 30 | 289788 | 3875.07 | 4.5742 | 1(Win) | true |
| Jsonifier (two-stage) | 2140.98 | 0.351531 | 485.344ms | 9378 | 160 | 34501.8 | 4177.32 | 0.675419 | 2(Loss) | true |
| Glaze | 1582.34 | 0.221088 | 553.627ms | 9378 | 2560 | 399751 | 5652.1 | 0.729824 | 3(Loss) | true |
| simdjson (ondemand) | 1559.71 | 0.0693259 | 617.298ms | 9378 | 160 | 2528.39 | 5734.11 | 0.0226765 | 4(Loss) | true |
