
----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2930.85 | 0.041132 | 868.604ms | 25388 | 30 | 346.378 | 8261.03 | 0.000806995 | 1(Win) | true |
| Jsonifier (two-stage) | 2208.5 | 0.0351174 | 1115ms | 25388 | 80 | 1185.76 | 10963 | 0.0144826 | 2(Loss) | true |
| Glaze | 1752.09 | 0.10737 | 1501.16ms | 25388 | 1280 | 281786 | 13818.9 | 0.0357964 | 3(Loss) | true |
| simdjson (ondemand) | 1649.32 | 0.0459243 | 1483.19ms | 25388 | 160 | 7271.95 | 14679.9 | 0.0310703 | 4(Loss) | true |
