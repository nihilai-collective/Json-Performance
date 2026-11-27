
----
### Canada Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8713.83 | 0.167163 | 7321.57ms | 5212421 | 40 | 3.6375e+07 | 570467 | 0.0638878 | 0.576445 | 2.53192 | 0.327124 | 0.00226194 | 0.0590773 | 4.11997e-06 | 1(Win) | true |
| simdjson (ondemand) | 7688.59 | 0.349853 | 8366.05ms | 5212421 | 640 | 3.27444e+09 | 646536 | 0.0675951 | 0.663036 | 2.85499 | 0.331083 | 0.0021568 | 0.0590852 | 7.28009e-06 | 2(Loss) | true |
