
----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17871.3 | 0.132168 | 790.402ms | 11521 | 4890 | 3228.74 | 614.801 | 0.272402 | 0.301925 | 1.47704 | 0.246854 | 8.74015e-05 | 1.65608e-05 | 7.33079e-06 | 1(Win) | true |
| Glaze | 5469.99 | 0.266172 | 928.436ms | 11521 | 320 | 9147.08 | 2008.65 | 0.290996 | 0.959362 | 3.62026 | 0.633279 | 0.00123931 | 2.38695e-05 | 5.69612e-06 | 2(Loss) | true |
