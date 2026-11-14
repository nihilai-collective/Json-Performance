
----
### Apache Builds Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2656.48 | 0.0512615 | 125.261ms | 3370 | 1280 | 492.312 | 1209.83 | 0.113588 | 1(Win) | true |
| simdjson (ondemand) | 2208.75 | 0.151918 | 148.381ms | 3370 | 4890 | 23894.3 | 1455.07 | 0.15082 | 2(Loss) | true |
