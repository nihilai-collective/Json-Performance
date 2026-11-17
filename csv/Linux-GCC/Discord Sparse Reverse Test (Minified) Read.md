
----
### Discord Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1846.34 | 0.0467705 | 3610.02ms | 56369 | 640 | 118681 | 29115.8 | 0.0702969 | 2.7432 | 13.1183 | 2.49577 | 0.00434736 | 7.12382e-06 | 1.66315e-06 | 1(Win) | true |
| simdjson (ondemand) | 1318.56 | 0.0242858 | 4807.62ms | 56369 | 4890 | 479397 | 40770.1 | 0.0070717 | 3.88081 | 16.6249 | 2.98541 | 0.0118375 | 1.30639e-05 | 5.46719e-06 | 2(Loss) | true |
