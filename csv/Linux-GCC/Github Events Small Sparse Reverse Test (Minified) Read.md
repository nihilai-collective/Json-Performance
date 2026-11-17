
----
### Github Events Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3198.46 | 0.0621835 | 761.314ms | 1691 | 4890 | 480.689 | 504.199 | 0.167958 | 1.748 | 6.87877 | 1.21348 | 0.000609869 | 3.25312e-05 | 5.44202e-06 | 1(Win) | true |
| simdjson (ondemand) | 2700.92 | 0.0758122 | 769.68ms | 1691 | 4890 | 1001.96 | 597.079 | 0.108609 | 2.04278 | 8.48212 | 1.44829 | 0.000675294 | 3.74895e-05 | 1.25771e-05 | 2(Loss) | true |
