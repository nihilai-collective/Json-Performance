
----
### Apache Builds Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1826.92 | 0.0307094 | 5677.44ms | 94653 | 4890 | 1.12585e+06 | 49410 | 0.245279 | 2.78137 | 12.6353 | 2.4967 | 0.00715738 | 1.61369e-05 | 1.0876e-05 | 1(Win) | true |
| simdjson (ondemand) | 1554.02 | 0.0315735 | 6544.58ms | 94653 | 2560 | 861075 | 58086.8 | 0.0998991 | 3.28939 | 13.6165 | 2.44554 | 0.0089143 | 6.44212e-06 | 2.53393e-06 | 2(Loss) | true |
