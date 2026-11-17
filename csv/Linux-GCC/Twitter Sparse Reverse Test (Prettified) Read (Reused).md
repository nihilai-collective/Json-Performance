
----
### Twitter Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5723.56 | 0.109783 | 6793.39ms | 360584 | 30 | 130519 | 60081.4 | 0.299967 | 0.883348 | 4.321 | 0.65298 | 0.00149091 | 1.68246e-05 | 1.53455e-05 | 1(Win) | true |
| simdjson (ondemand) | 4981.59 | 0.0281928 | 7703.94ms | 360584 | 2560 | 969600 | 69030.1 | 0.153609 | 1.01742 | 4.98858 | 0.704395 | 0.00212868 | 5.73289e-06 | 3.88151e-06 | 2(Loss) | true |
