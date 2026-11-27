
----
### Apache Builds Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1533.05 | 0.141254 | 166.138ms | 2632 | 4890 | 26155.9 | 1637.3 | 0.116791 | 1.96062 | 1(Win) | true |
| simdjson (ondemand) | 1314.82 | 0.116334 | 198.631ms | 2632 | 1280 | 6313.43 | 1909.06 | 0.262596 | 2.28924 | 2(Loss) | true |
