
----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1475.66 | 0.140969 | 333.403ms | 4390 | 4890 | 78219.1 | 2837.12 | 0.0492885 | 2.04532 | 1(Win) | true |
| Jsonifier (two-stage) | 1257.25 | 0.293316 | 386.216ms | 4390 | 30 | 2862.07 | 3330 | 0 | 2.40923 | 2(Loss) | true |
| Glaze | 1180.76 | 0.16873 | 399.548ms | 4390 | 1280 | 45814.2 | 3545.7 | 0.0418465 | 2.55947 | 3(Loss) | true |
| simdjson (ondemand) | 678.85 | 0.1211 | 667.635ms | 4390 | 4890 | 272758 | 6167.24 | 0.158805 | 4.46158 | 4(Loss) | true |
