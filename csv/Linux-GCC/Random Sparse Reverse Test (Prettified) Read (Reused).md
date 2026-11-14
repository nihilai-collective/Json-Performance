
----
### Random Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2962.87 | 0.189581 | 6195.34ms | 676745 | 160 | 2.72858e+07 | 217828 | 0.0714132 | 1.70398 | 7.98991 | 1.396 | 0.00481335 | 0.00115443 | 4.24828e-06 | 1(Win) | true |
| simdjson (ondemand) | 2414.74 | 0.0374416 | 7474.07ms | 676745 | 640 | 6.40909e+06 | 267272 | 0.0477468 | 2.1206 | 8.84694 | 1.49224 | 0.00695014 | 0.00258292 | 2.1934e-06 | 2(Loss) | true |
