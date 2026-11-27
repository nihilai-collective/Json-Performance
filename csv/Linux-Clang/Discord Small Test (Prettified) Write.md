
----
### Discord Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11222.6 | 0.209594 | 798.937ms | 7376 | 40 | 69.0359 | 626.8 | 0.583044 | 0.482067 | 1.60073 | 0.273048 | 0.000179637 | 2.7115e-05 | 1.69469e-05 | 1(Win) | true |
| Glaze | 2573.93 | 0.152341 | 1017.28ms | 7376 | 4890 | 84759.4 | 2732.9 | 0.21825 | 1.99871 | 4.57077 | 0.739426 | 0.00054851 | 4.28073e-05 | 1.12563e-05 | 2(Loss) | true |
