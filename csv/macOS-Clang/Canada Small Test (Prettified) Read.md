
----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1580.62 | 0.0489083 | 722.388ms | 11579 | 160 | 1867.98 | 6986.24 | 0.0101976 | 1(Win) | true |
| Jsonifier (two-stage) | 1524.04 | 0.0541057 | 735.718ms | 11579 | 160 | 2458.97 | 7245.59 | 0.153822 | 2(Loss) | true |
| simdjson (ondemand) | 1059.45 | 0.0526517 | 1058.39ms | 11579 | 40 | 1204.66 | 10423 | 0.033111 | 3(Loss) | true |
| Glaze | 1053 | 0.0252449 | 1063.89ms | 11579 | 160 | 1121.38 | 10486.8 | 0.0275867 | 4(Loss) | true |
