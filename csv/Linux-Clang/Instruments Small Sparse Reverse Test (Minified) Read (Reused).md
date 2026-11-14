
----
### Instruments Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3376.85 | 0.0680032 | 847.132ms | 4669 | 4890 | 3931.8 | 1318.6 | 0.142214 | 1.57312 | 7.37803 | 1.25123 | 0.00137644 | 1.77387e-05 | 1.79577e-06 | 1(Win) | true |
| simdjson (ondemand) | 2699.3 | 0.0911455 | 879.646ms | 4669 | 1280 | 2893.52 | 1649.58 | 0.013168 | 1.95305 | 9.51853 | 1.46948 | 0.00235161 | 1.58961e-05 | 2.17525e-06 | 2(Loss) | true |
