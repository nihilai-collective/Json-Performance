
----
### Random Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2703.6 | 0.0278421 | 6313.39ms | 676745 | 1280 | 5.65431e+06 | 238717 | 0.0682885 | 1.89266 | 8.49738 | 1.55396 | 0.00620246 | 0.00133876 | 2.10382e-05 | 1(Win) | true |
| simdjson (ondemand) | 2307.91 | 0.0535078 | 7333.22ms | 676745 | 320 | 7.16465e+06 | 279644 | 0.0194258 | 2.20248 | 9.75036 | 1.60194 | 0.007703 | 0.00499634 | 1.70762e-05 | 2(Loss) | true |
