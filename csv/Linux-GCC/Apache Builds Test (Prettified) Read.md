
----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1755.94 | 0.126873 | 6939.83ms | 124597 | 640 | 4.7175e+06 | 67670.2 | 0.429625 | 1.40943 | 1(Win) | true |
| simdjson (ondemand) | 1645.4 | 0.0582614 | 7293.55ms | 124597 | 2560 | 4.53183e+06 | 72216.4 | 0.100412 | 1.50414 | 2(Loss) | true |
