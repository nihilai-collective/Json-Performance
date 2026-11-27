
----
### Marine IK Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 937.007 | 0.151963 | 522.076ms | 4604 | 4890 | 247955 | 4685.9 | 0.099309 | 2.62631 | 1(Win) | true |
| Jsonifier (two-stage) | 832.914 | 0.187368 | 529.541ms | 4604 | 2560 | 249747 | 5271.51 | 0.00529054 | 2.95692 | 2(Loss) | true |
| Glaze | 673.853 | 0.164757 | 657.952ms | 4604 | 30 | 3457.39 | 6515.83 | 0.0255853 | 3.65939 | 3(Loss) | true |
| simdjson (ondemand) | 529.623 | 0.0514855 | 833.981ms | 4604 | 80 | 1457.46 | 8290.26 | 0.31279 | 4.65988 | 4(Loss) | true |
