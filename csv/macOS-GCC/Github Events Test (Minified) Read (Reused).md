
----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1508.91 | 0.158201 | 4326.85ms | 53331 | 640 | 1.81984e+06 | 33706.8 | 0.00118672 | 1(Win) | true |
| simdjson (ondemand) | 985.135 | 0.0463861 | 5787.85ms | 53331 | 4890 | 2.80448e+06 | 51627.9 | 0.0152475 | 2(Loss) | true |
