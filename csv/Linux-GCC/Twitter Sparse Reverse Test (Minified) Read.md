
----
### Twitter Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5122.96 | 0.175252 | 5680.64ms | 264040 | 160 | 1.18726e+06 | 49152.9 | 0.0757778 | 0.983757 | 5.14406 | 0.861907 | 0.00175525 | 9.08953e-06 | 5.25489e-06 | 1(Win) | true |
| simdjson (ondemand) | 3999.75 | 0.0330517 | 7079.72ms | 264040 | 2560 | 1.10841e+06 | 62955.9 | 0.0332194 | 1.26313 | 6.32691 | 0.948355 | 0.00222514 | 6.49316e-06 | 3.74588e-06 | 2(Loss) | true |
