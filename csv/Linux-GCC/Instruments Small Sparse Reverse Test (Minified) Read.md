
----
### Instruments Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3389.25 | 0.0635731 | 848.518ms | 4669 | 4890 | 3411.12 | 1313.77 | 0.328821 | 1.56335 | 7.27843 | 1.31206 | 0.00151484 | 2.90827e-05 | 1.50232e-05 | 1(Win) | true |
| simdjson (ondemand) | 2646.8 | 0.113589 | 886.816ms | 4669 | 40 | 146.062 | 1682.3 | 0.0198102 | 1.99278 | 9.4667 | 1.54851 | 0.00284322 | 6.42536e-05 | 4.28357e-05 | 2(Loss) | true |
