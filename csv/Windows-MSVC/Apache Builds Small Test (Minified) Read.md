
----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 847.938 | 0.104852 | 299.851ms | 2632 | 4890 | 47109 | 2960.2 | 0.00892599 | 3.55829 | 1(Win) | true |
| simdjson (ondemand) | 786.625 | 0.135854 | 321.18ms | 2632 | 2560 | 48108.5 | 3190.94 | 0.210115 | 3.83955 | 2(Loss) | true |
