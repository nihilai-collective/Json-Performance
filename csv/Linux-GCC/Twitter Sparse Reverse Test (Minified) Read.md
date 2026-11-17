
----
### Twitter Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4674.4 | 0.0794259 | 6067.71ms | 264040 | 40 | 73227.2 | 53869.6 | 0.268946 | 1.0819 | 5.3236 | 0.873811 | 0.00215763 | 3.40857e-06 | 2.1777e-06 | 1(Win) | true |
| simdjson (ondemand) | 3919.08 | 0.0454278 | 7165.75ms | 264040 | 1280 | 1.0905e+06 | 64251.8 | 0.0493966 | 1.29068 | 6.34431 | 0.953653 | 0.0024783 | 3.18962e-06 | 1.88773e-06 | 2(Loss) | true |
