
----
### Twitter Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7008.88 | 0.0534368 | 4338.23ms | 264040 | 2560 | 943545 | 35927 | 0.0949408 | 0.725626 | 3.47071 | 0.476492 | 0.00122066 | 7.88529e-06 | 4.89983e-06 | 1(Win) | true |
| simdjson (ondemand) | 6004.41 | 0.0577133 | 4916.4ms | 264040 | 1280 | 749827 | 41937.2 | 0.0109806 | 0.841527 | 3.88472 | 0.435379 | 0.00144134 | 3.29022e-06 | 1.25159e-06 | 2(Loss) | true |
