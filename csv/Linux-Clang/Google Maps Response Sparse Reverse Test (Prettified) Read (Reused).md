
----
### Google Maps Response Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3389.82 | 0.0804079 | 1455.69ms | 25388 | 80 | 2638.71 | 7142.52 | 0.0129523 | 1.52863 | 7.12888 | 1.26107 | 0.0030802 | 2.21561e-05 | 1.72326e-05 | 1(Win) | true |
| simdjson (ondemand) | 3250.63 | 0.0792899 | 1487.02ms | 25388 | 2560 | 89288.8 | 7448.36 | 0.0502637 | 1.57483 | 7.23838 | 1.11667 | 0.003276 | 1.00934e-05 | 3.0157e-06 | 2(Loss) | true |
