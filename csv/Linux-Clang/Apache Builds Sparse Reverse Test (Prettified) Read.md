
----
### Apache Builds Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2285.14 | 0.0163545 | 5939.69ms | 124597 | 4890 | 353649 | 51999 | 0.0738594 | 2.23085 | 10.4036 | 1.96387 | 0.00567363 | 1.80114e-05 | 1.35406e-05 | 1(Win) | true |
| simdjson (ondemand) | 2050.79 | 0.0243798 | 6510.17ms | 124597 | 2560 | 510828 | 57941.1 | 0.0663864 | 2.47723 | 10.3512 | 1.8235 | 0.00659977 | 8.94133e-06 | 5.08201e-06 | 2(Loss) | true |
