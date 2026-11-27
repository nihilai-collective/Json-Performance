
----
### Canada Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10494.4 | 0.0658597 | 821.27ms | 11579 | 1280 | 614.724 | 1052.24 | 0.111764 | 0.508894 | 2.68961 | 0.355558 | 0.00025909 | 7.08448e-06 | 3.37356e-07 | 1(Win) | true |
| simdjson (ondemand) | 8958.54 | 0.146809 | 837.039ms | 11579 | 1280 | 4191.65 | 1232.63 | 0.0259928 | 0.58608 | 3.02703 | 0.36048 | 0.000270222 | 9.04115e-06 | 2.09161e-06 | 2(Loss) | true |
