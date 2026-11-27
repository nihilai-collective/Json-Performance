
----
### Marine IK Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1166.69 | 0.102101 | 461.621ms | 4604 | 30 | 442.938 | 3763.4 | 0.147247 | 2.10641 | 1(Win) | true |
| Jsonifier (two-stage) | 920.601 | 0.109178 | 594.902ms | 4604 | 30 | 813.421 | 4769.4 | 0.130524 | 2.6734 | 2(Loss) | true |
| simdjson (reflection) | 758.654 | 0.382902 | 668.32ms | 4604 | 640 | 314296 | 5787.51 | 0.0588745 | 3.24884 | 3(Loss) | true |
| Glaze | 738.946 | 0.0805985 | 709.302ms | 4604 | 80 | 1834.8 | 5941.86 | 0.00988649 | 3.33538 | 4(Loss) | true |
| simdjson (ondemand) | 522.744 | 0.400526 | 912.349ms | 4604 | 160 | 181082 | 8399.36 | 0.240288 | 4.72046 | 5(Loss) | true |
