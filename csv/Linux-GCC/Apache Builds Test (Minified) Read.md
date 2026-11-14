
----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1317.97 | 0.0551303 | 7004.87ms | 94653 | 2560 | 3.64987e+06 | 68490.2 | 0.00788087 | 1.87774 | 1(Win) | true |
| simdjson (ondemand) | 1277.92 | 0.0980303 | 7132.72ms | 94653 | 4890 | 2.34472e+07 | 70636.8 | 0.0420156 | 1.9366 | 2(Loss) | true |
