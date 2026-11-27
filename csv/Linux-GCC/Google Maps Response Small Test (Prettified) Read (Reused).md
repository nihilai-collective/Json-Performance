
----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2997.48 | 0.0351293 | 1043.06ms | 9378 | 4890 | 5372.26 | 2983.7 | 0.11598 | 1.7246 | 8.11079 | 1.39699 | 0.000478233 | 2.81083e-05 | 7.19606e-06 | 1(Win) | true |
| simdjson (ondemand) | 2435.91 | 0.090888 | 1113.49ms | 9378 | 640 | 7126.75 | 3671.55 | 0.0284625 | 2.11574 | 8.99435 | 1.53977 | 0.00188523 | 3.83211e-05 | 2.26594e-05 | 2(Loss) | true |
