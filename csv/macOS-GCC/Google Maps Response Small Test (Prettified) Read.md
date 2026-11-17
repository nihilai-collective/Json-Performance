
----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2234.7 | 0.572402 | 446.283ms | 9378 | 30 | 15743.7 | 4002.13 | 0.213675 | 1(Win) | true |
| Jsonifier | 2098.24 | 0.475725 | 406.046ms | 9378 | 1280 | 526297 | 4262.4 | 0.386246 | 2(Loss) | true |
| simdjson (reflection) | 1775.64 | 0.364862 | 521.32ms | 9378 | 160 | 54036.3 | 5036.8 | 0 | 3(Loss) | true |
| Glaze | 1434.69 | 0.41117 | 631.587ms | 9378 | 1280 | 840926 | 6233.8 | 1.75566 | 4(Loss) | true |
| simdjson (ondemand) | 1299.86 | 0.565508 | 672.932ms | 9378 | 640 | 968912 | 6880.4 | 0.437931 | 5(Loss) | true |
