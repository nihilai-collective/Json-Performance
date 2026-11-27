
----
### Twitter Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4530.39 | 0.14033 | 778.26ms | 2821 | 80 | 55.5555 | 593.837 | 0.0315843 | 1.21228 | 5.23467 | 0.850408 | 0.000722262 | 0 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3654.83 | 0.125899 | 786.522ms | 2821 | 2560 | 2198.64 | 736.098 | 0.142494 | 1.48777 | 6.26161 | 0.916342 | 0.000721015 | 3.04635e-05 | 1.30162e-05 | 2(Loss) | true |
