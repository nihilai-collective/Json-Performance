
----
### Twitter Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4989.46 | 0.0676538 | 792.544ms | 3770 | 1280 | 304.208 | 720.59 | 0.142991 | 1.08703 | 4.55438 | 0.680902 | 0.000782908 | 5.96817e-05 | 2.44529e-05 | 1(Win) | true |
| simdjson (ondemand) | 4525.62 | 0.116424 | 800.39ms | 3770 | 160 | 136.877 | 794.444 | 0.175746 | 1.19549 | 5.02149 | 0.693369 | 0.00103282 | 3.14987e-05 | 3.31565e-06 | 2(Loss) | true |
