
----
### Apache Builds Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3957.37 | 0.0700264 | 781.494ms | 2632 | 4890 | 964.697 | 634.278 | 0.0414633 | 1.38199 | 6.03382 | 0.921733 | 0.00100509 | 1.58502e-05 | 1.16546e-06 | 1(Win) | true |
| simdjson (ondemand) | 2717.57 | 0.0555704 | 811.199ms | 2632 | 2560 | 674.429 | 923.645 | 0.00477919 | 1.97867 | 7.08169 | 1.14134 | 0.000761363 | 3.23542e-05 | 1.14279e-05 | 2(Loss) | true |
