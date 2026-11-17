
----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1530.1 | 0.416116 | 219.389ms | 3370 | 640 | 48891.2 | 2100.44 | 0.574608 | 1(Win) | true |
| Jsonifier (two-stage) | 1367.3 | 0.323189 | 228.145ms | 3370 | 2560 | 147736 | 2350.53 | 0.269226 | 2(Loss) | true |
| Glaze | 1274.15 | 0.153126 | 255.025ms | 3370 | 2560 | 38190.7 | 2522.38 | 0.151857 | 3(Loss) | true |
| simdjson (ondemand) | 991.188 | 0.808024 | 347.853ms | 3370 | 160 | 109829 | 3242.46 | 0.214077 | 4(Loss) | true |
