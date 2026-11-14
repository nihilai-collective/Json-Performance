
----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1023.8 | 0.0927689 | 317.212ms | 3370 | 4890 | 41471.2 | 3139.18 | 0.0534048 | 2.94777 | 1(Win) | true |
| simdjson (ondemand) | 996.208 | 0.0917446 | 324.041ms | 3370 | 4890 | 42838 | 3226.11 | 0.210805 | 3.03094 | 2(Loss) | true |
