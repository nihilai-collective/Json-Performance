
----
### Discord Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15460.8 | 0.105112 | 1323.59ms | 94370 | 1280 | 47919.5 | 5821.04 | 0.0788576 | 0.33226 | 1.33126 | 0.232245 | 0.000261578 | 3.09619e-06 | 9.18923e-07 | 1(Win) | true |
| Glaze | 4563.63 | 0.0628621 | 2719.78ms | 94370 | 4890 | 751509 | 19720.8 | 0.0167198 | 1.10525 | 4.12562 | 0.666091 | 0.00156537 | 1.58017e-05 | 8.19556e-06 | 2(Loss) | true |
