
----
### Apache Builds Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2753.88 | 0.113849 | 808.204ms | 2632 | 1280 | 1378.31 | 911.466 | 0.107883 | 1.95491 | 8.30586 | 1.49582 | 0.0014031 | 1.36541e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2360.38 | 0.0556855 | 823.053ms | 2632 | 320 | 112.213 | 1063.42 | 0.0964802 | 2.26552 | 8.84498 | 1.51482 | 0.00247792 | 1.78097e-05 | 0 | 2(Loss) | true |
