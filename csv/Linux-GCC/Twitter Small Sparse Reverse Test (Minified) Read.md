
----
### Twitter Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3930.53 | 0.34536 | 782.85ms | 2821 | 30 | 167.637 | 684.467 | 0.00974089 | 1.38686 | 5.50514 | 0.877348 | 0.000838946 | 1.18161e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3485.81 | 0.0717194 | 790.447ms | 2821 | 2560 | 784.357 | 771.791 | 0.0671576 | 1.55489 | 6.25665 | 0.913861 | 0.000752587 | 1.73088e-05 | 5.1234e-06 | 2(Loss) | true |
