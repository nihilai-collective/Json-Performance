
----
### Instruments Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5063.71 | 0.0610733 | 867.97ms | 7932 | 80 | 66.5918 | 1493.88 | 0 | 1.0638 | 5.11296 | 0.784039 | 0.000806858 | 7.87948e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4157.79 | 0.0299712 | 896.252ms | 7932 | 4890 | 1453.98 | 1819.37 | 0.0168545 | 1.26612 | 6.07552 | 0.878845 | 0.00147326 | 1.08798e-05 | 1.36642e-06 | 2(Loss) | true |
