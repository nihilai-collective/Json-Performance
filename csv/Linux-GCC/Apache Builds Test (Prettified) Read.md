
----
### Apache Builds Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1834.36 | 0.154704 | 6632.49ms | 124597 | 160 | 1.60683e+06 | 64777.3 | 0.0722724 | 1.34916 | 1(Win) | true |
| simdjson (ondemand) | 1735.47 | 0.291309 | 6865.99ms | 124597 | 40 | 1.59129e+06 | 68468.5 | 0.0657669 | 1.42605 | 2(Loss) | true |
