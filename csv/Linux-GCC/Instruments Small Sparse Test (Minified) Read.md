
----
### Instruments Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4494.04 | 0.0551999 | 811.517ms | 4669 | 1280 | 382.878 | 990.802 | 0.0692614 | 1.20652 | 5.19576 | 0.739559 | 0.00148302 | 3.4804e-05 | 1.22149e-05 | 1(Win) | true |
| simdjson (ondemand) | 4387.32 | 0.0943305 | 814.268ms | 4669 | 1280 | 1173.17 | 1014.9 | 0.0735679 | 1.23108 | 5.56457 | 0.70015 | 0.00120693 | 2.25892e-05 | 5.35447e-06 | 2(Loss) | true |
