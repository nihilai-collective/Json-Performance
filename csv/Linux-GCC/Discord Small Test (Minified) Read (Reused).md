
----
### Discord Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2213.74 | 0.0785697 | 957.809ms | 4857 | 160 | 432.426 | 2092.38 | 0.016426 | 2.375 | 9.96562 | 1.84435 | 0.00114139 | 3.21701e-05 | 9.00762e-06 | 1(Win) | true |
| simdjson (ondemand) | 1652.05 | 0.0869885 | 1026.19ms | 4857 | 320 | 1903.54 | 2803.78 | 0.19589 | 3.10543 | 12.2738 | 2.11159 | 0.00232783 | 5.98363e-05 | 1.35114e-05 | 2(Loss) | true |
