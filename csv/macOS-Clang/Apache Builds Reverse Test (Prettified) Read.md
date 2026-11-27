
----
### Apache Builds Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1007.4 | 0.699218 | 6247.53ms | 124597 | 320 | 2.17664e+08 | 117952 | 0.948773 | 1(Win) | true |
| simdjson (ondemand) | 585.158 | 0.570273 | 5131.1ms | 124597 | 320 | 4.29126e+08 | 203065 | 0.116523 | 2(Loss) | true |
