
----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2508.89 | 0.0369742 | 996.743ms | 6701 | 4890 | 4337.32 | 2547.17 | 0.0523183 | 2.08424 | 8.61767 | 1.53097 | 0.0019809 | 3.02735e-05 | 2.28883e-06 | 1(Win) | true |
| simdjson (ondemand) | 2335.64 | 0.0276039 | 1010.3ms | 6701 | 4890 | 2789.44 | 2736.11 | 0.00678294 | 2.23737 | 9.15699 | 1.51157 | 0.000549105 | 3.25013e-05 | 1.40381e-06 | 2(Loss) | true |
