
----
### Twitter Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 901.663 | 0.114241 | 407.317ms | 3770 | 30 | 622.533 | 3987.47 | 0.0317763 | 1(Win) | true |
| simdjson (ondemand) | 283.262 | 0.0777026 | 1284.74ms | 3770 | 40 | 3890.79 | 12692.7 | 0.0681687 | 2(Loss) | true |
