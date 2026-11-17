
----
### Random Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2088.04 | 0.0788932 | 5477.34ms | 409725 | 160 | 3.48743e+06 | 187134 | 0.0117382 | 2.44696 | 11.8154 | 2.22986 | 0.00752157 | 0.000213741 | 4.11862e-07 | 1(Win) | true |
| simdjson (ondemand) | 1620.72 | 0.029603 | 6849.63ms | 409725 | 640 | 3.26004e+06 | 241093 | 0.0215852 | 3.16972 | 14.3514 | 2.38847 | 0.0104682 | 0.00257929 | 7.55461e-06 | 2(Loss) | true |
