
----
### Github Events Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4249.82 | 0.179601 | 767.367ms | 2158 | 640 | 484.125 | 484.262 | 0.2857 | 1.31029 | 5.36191 | 0.918906 | 0.00100933 | 2.31696e-05 | 7.96455e-06 | 1(Win) | true |
| simdjson (ondemand) | 3324.51 | 0.153434 | 779.607ms | 2158 | 1280 | 1154.79 | 619.047 | 0.133953 | 1.6436 | 6.77062 | 1.07461 | 0.000899632 | 1.95494e-05 | 5.06835e-06 | 2(Loss) | true |
