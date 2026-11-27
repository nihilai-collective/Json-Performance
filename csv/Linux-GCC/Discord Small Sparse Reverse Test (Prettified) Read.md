
----
### Discord Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4018.41 | 0.0592709 | 879.938ms | 6701 | 1280 | 1137.27 | 1590.32 | 0.137607 | 1.31185 | 5.71736 | 0.955977 | 0.000463667 | 1.70217e-05 | 6.06253e-06 | 1(Win) | true |
| simdjson (ondemand) | 2991.12 | 0.061735 | 934.823ms | 6701 | 1280 | 2226.82 | 2136.52 | 0.0508533 | 1.75359 | 7.76914 | 1.23743 | 0.00115036 | 2.22681e-05 | 7.11181e-06 | 2(Loss) | true |
