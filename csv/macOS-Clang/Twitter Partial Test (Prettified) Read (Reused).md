
----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5545.1 | 0.143882 | 5687.56ms | 631514 | 160 | 3.90731e+06 | 108611 | 0.033606 | 1(Win) | true |
| Jsonifier (two-stage) | 5486.67 | 0.127387 | 5691.47ms | 631514 | 640 | 1.25136e+07 | 109768 | 0.0141771 | 2(Loss) | true |
| simdjson (ondemand) | 4918 | 0.129963 | 6416.99ms | 631514 | 640 | 1.62109e+07 | 122460 | 0.187525 | 3(Loss) | true |
| Glaze | 2797.68 | 0.255643 | 5647.65ms | 631514 | 40 | 1.21143e+07 | 215271 | 0.107853 | 4(Loss) | true |
