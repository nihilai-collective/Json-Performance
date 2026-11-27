
----
### Google Maps Response Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4514.44 | 0.0930849 | 927.941ms | 9378 | 640 | 2176.46 | 1981.1 | 0.213676 | 1.14343 | 5.31265 | 0.847622 | 0.0011433 | 1.21628e-05 | 1.99936e-06 | 1(Win) | true |
| simdjson (ondemand) | 3995.51 | 0.0555154 | 957.253ms | 9378 | 160 | 247.072 | 2238.4 | 0.130845 | 1.31268 | 5.84037 | 0.882064 | 0.000907043 | 7.33099e-06 | 1.99936e-06 | 2(Loss) | true |
