
----
### Discord Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1783.76 | 0.0764214 | 3749.98ms | 56369 | 80 | 42435.3 | 30137.2 | 0.028528 | 2.89037 | 13.3859 | 2.50554 | 0.00722361 | 3.3263e-06 | 2.21753e-07 | 1(Win) | true |
| simdjson (ondemand) | 1336.24 | 0.25283 | 4761.34ms | 56369 | 40 | 413837 | 40230.6 | 0.110366 | 3.8567 | 17.5182 | 2.91568 | 0.0101177 | 5.32207e-06 | 8.87012e-07 | 2(Loss) | true |
