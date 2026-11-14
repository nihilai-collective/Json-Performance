
----
### Random Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2076.62 | 0.0349904 | 5415.02ms | 409725 | 1280 | 5.54853e+06 | 188163 | 0.0940708 | 2.45421 | 12.0765 | 2.22347 | 0.00748932 | 0.000527524 | 2.69617e-06 | 1(Win) | true |
| simdjson (ondemand) | 1537.18 | 0.143768 | 7110.83ms | 409725 | 40 | 5.34219e+06 | 254195 | 0.0868593 | 3.33039 | 13.7539 | 2.44449 | 0.010619 | 0.00137604 | 6.22369e-06 | 2(Loss) | true |
