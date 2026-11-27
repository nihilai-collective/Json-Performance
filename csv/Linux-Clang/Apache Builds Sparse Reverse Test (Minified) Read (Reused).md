
----
### Apache Builds Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2211.66 | 0.0635713 | 5238.9ms | 94653 | 160 | 107715 | 40814.7 | 0.0440517 | 2.28661 | 10.7537 | 2.07042 | 0.00603916 | 6.6691e-06 | 3.56566e-06 | 1(Win) | true |
| simdjson (ondemand) | 1833.06 | 0.0372005 | 6123.79ms | 94653 | 2560 | 859114 | 49244.4 | 0.00208696 | 2.76668 | 11.779 | 2.03095 | 0.0071818 | 7.76686e-06 | 4.21358e-06 | 2(Loss) | true |
