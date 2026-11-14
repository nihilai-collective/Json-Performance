
----
### Apache Builds Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1262.49 | 0.239939 | 283.024ms | 3370 | 4890 | 182437 | 2545.66 | 0.439267 | 2.38993 | 1(Win) | true |
| simdjson (ondemand) | 769.771 | 0.125054 | 445.644ms | 3370 | 4890 | 133304 | 4175.11 | 0.0541815 | 3.93094 | 2(Loss) | true |
