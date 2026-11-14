
----
### Canada Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1123.17 | 0.852678 | 6833.04ms | 5212421 | 30 | 4.27245e+10 | 4.42581e+06 | 2.02596 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 871.549 | 0.610379 | 8602.15ms | 5212421 | 30 | 3.63594e+10 | 5.70358e+06 | 5.54672 | -(Loss) | false |
