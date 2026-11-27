
----
### Apache Builds Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1014.08 | 0.160892 | 9004.1ms | 94653 | 1280 | 2.62544e+07 | 89014.8 | 0.214335 | 1(Win) | true |
| simdjson (ondemand) | 731.708 | 0.427403 | 6364.11ms | 94653 | 30 | 8.34047e+06 | 123366 | 0.194054 | 2(Loss) | true |
