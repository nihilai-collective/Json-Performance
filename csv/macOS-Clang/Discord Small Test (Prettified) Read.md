
----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2115.51 | 0.130716 | 307.852ms | 6701 | 40 | 623.687 | 3020.82 | 0.000827595 | 1(Win) | true |
| Jsonifier (two-stage) | 1640.87 | 0.0686445 | 393.788ms | 6701 | 4890 | 34950.4 | 3894.63 | 0.0201883 | 2(Loss) | true |
| Glaze | 1545.79 | 0.122815 | 427.252ms | 6701 | 160 | 4124.78 | 4134.17 | 0.0170803 | 3(Loss) | true |
| simdjson (ondemand) | 871.267 | 0.138311 | 747.435ms | 6701 | 1280 | 131734 | 7334.8 | 0.0370908 | 4(Loss) | true |
