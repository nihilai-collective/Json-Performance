
----
### Instruments Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3287.32 | 0.042272 | 859.225ms | 4669 | 4890 | 1603.17 | 1354.51 | 0.047271 | 1.60732 | 7.44356 | 1.32127 | 0.00150709 | 2.69366e-05 | 7.66488e-06 | 1(Win) | true |
| simdjson (ondemand) | 2518.21 | 0.0804922 | 895.276ms | 4669 | 2560 | 5185.76 | 1768.2 | 0.00311482 | 2.08722 | 9.78068 | 1.52538 | 0.00286389 | 2.49317e-05 | 9.37031e-06 | 2(Loss) | true |
