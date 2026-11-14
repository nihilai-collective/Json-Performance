
----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1671.98 | 0.78529 | 224.798ms | 3370 | 1280 | 291653 | 1922.2 | 0.617672 | 1(Win) | true |
| simdjson (ondemand) | 1172.75 | 0.504969 | 296.631ms | 3370 | 4890 | 936447 | 2740.46 | 1.50392 | 2(Loss) | true |
