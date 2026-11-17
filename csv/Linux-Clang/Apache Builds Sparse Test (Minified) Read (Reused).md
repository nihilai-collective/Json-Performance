
----
### Apache Builds Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3343.81 | 0.0188495 | 3949.1ms | 94653 | 4890 | 126618 | 26995.6 | 0.234997 | 1.52142 | 7.48156 | 1.35543 | 0.00351955 | 4.86547e-06 | 1.32223e-06 | 1(Win) | true |
| simdjson (ondemand) | 2323.93 | 0.0346191 | 5117.85ms | 94653 | 1280 | 231455 | 38842.9 | 0.0213345 | 2.18292 | 9.12156 | 1.51132 | 0.00656488 | 1.47826e-05 | 7.18083e-06 | 2(Loss) | true |
