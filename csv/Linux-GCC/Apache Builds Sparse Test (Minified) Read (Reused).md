
----
### Apache Builds Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3295.86 | 0.127668 | 3947.79ms | 94653 | 320 | 391242 | 27388.3 | 0.0743263 | 1.53532 | 7.72976 | 1.27821 | 0.00324884 | 2.34409e-06 | 4.29199e-07 | 1(Win) | true |
| simdjson (ondemand) | 2179.43 | 0.0351834 | 5348.2ms | 94653 | 1280 | 271812 | 41418.2 | 0.134202 | 2.34791 | 8.84793 | 1.54693 | 0.00682527 | 8.26209e-06 | 4.29199e-06 | 2(Loss) | true |
