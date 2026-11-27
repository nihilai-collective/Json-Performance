
----
### Marine IK Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 950.938 | 0.111703 | 478.61ms | 4604 | 40 | 1064.04 | 4617.25 | 0.128699 | 2.58799 | 1(Win) | true |
| Jsonifier (two-stage) | 769.702 | 0.142167 | 563.842ms | 4604 | 4890 | 321610 | 5704.43 | 0.173526 | 3.20067 | 2(Loss) | true |
| simdjson (reflection) | 654.994 | 0.151351 | 699.847ms | 4604 | 4890 | 503354 | 6703.44 | 0.466 | 3.76443 | 3(Loss) | true |
| Glaze | 639.769 | 0.190692 | 689.758ms | 4604 | 1280 | 219229 | 6862.97 | 0.00561241 | 3.85448 | 4(Loss) | true |
| simdjson (ondemand) | 505.279 | 0.23845 | 895.405ms | 4604 | 1280 | 549557 | 8689.69 | 0.0279144 | 4.88467 | 5(Loss) | true |
