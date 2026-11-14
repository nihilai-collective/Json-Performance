
----
### Google Maps Response Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1802.05 | 0.112475 | 1343.85ms | 11812 | 320 | 15818.7 | 6251.09 | 0.0313347 | 2.87349 | 14.0227 | 2.64265 | 0.00845115 | 3.17474e-05 | 1.00533e-05 | 1(Win) | true |
| simdjson (ondemand) | 1596.28 | 0.017493 | 1427.61ms | 11812 | 4890 | 7451.93 | 7056.93 | 0.00428723 | 3.24406 | 14.6073 | 2.41238 | 0.00731712 | 2.26105e-05 | 5.03803e-06 | 2(Loss) | true |
