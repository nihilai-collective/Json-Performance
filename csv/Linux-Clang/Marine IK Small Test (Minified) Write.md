
----
### Marine IK Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1901.16 | 0.0324088 | 250.968ms | 4918 | 80 | 51.1392 | 2467 | 0.100224 | 1.289 | 1(Win) | true |
| Glaze | 863.527 | 0.0518672 | 515.165ms | 4604 | 30 | 208.654 | 5084.63 | 0.034078 | 2.85277 | 2(Loss) | true |
