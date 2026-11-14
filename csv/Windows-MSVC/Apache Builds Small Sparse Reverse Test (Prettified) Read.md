
----
### Apache Builds Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1810.64 | 0.292191 | 183.273ms | 3370 | 80 | 2151.9 | 1775 | 0.141044 | 1.66639 | 1(Win) | true |
| simdjson (ondemand) | 1711.65 | 0.167195 | 190.695ms | 3370 | 640 | 6307.49 | 1877.66 | 0.373072 | 1.75652 | 2(Loss) | true |
