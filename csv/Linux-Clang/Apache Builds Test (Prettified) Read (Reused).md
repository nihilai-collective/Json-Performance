
----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2733.7 | 0.0943624 | 5669.51ms | 124597 | 1280 | 2.15339e+06 | 43466.8 | 0.369655 | 0.9051 | 1(Win) | true |
| Jsonifier | 2328.64 | 0.231903 | 6308.9ms | 124597 | 160 | 2.24048e+06 | 51027.5 | 0.0127031 | 1.06264 | 2(Loss) | true |
| Glaze | 2123.32 | 0.11727 | 6650.94ms | 124597 | 640 | 2.75638e+06 | 55961.9 | 0.27059 | 1.16545 | 3(Loss) | true |
| simdjson (ondemand) | 1774.13 | 0.0617994 | 7827.06ms | 124597 | 2560 | 4.38585e+06 | 66976.6 | 0.0972775 | 1.39488 | 4(Loss) | true |
