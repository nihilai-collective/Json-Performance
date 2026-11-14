
----
### Apache Builds Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1500.23 | 0.152994 | 171.393ms | 2632 | 320 | 2096.79 | 1673.12 | 0.224635 | 2.00262 | 1(Win) | true |
| simdjson (ondemand) | 1329.62 | 0.158784 | 192.97ms | 2632 | 1280 | 11501.1 | 1887.81 | 0.0745465 | 2.26212 | 2(Loss) | true |
