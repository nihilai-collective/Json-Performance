
----
### Marine IK Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 919.975 | 0.156241 | 615.136ms | 4604 | 4890 | 271907 | 4772.65 | 0.4535 | 1(Win) | true |
| Jsonifier (two-stage) | 697.599 | 0.127955 | 778.501ms | 4604 | 4890 | 317161 | 6294.04 | 0.0327174 | 2(Loss) | true |
| simdjson (reflection) | 642.632 | 0.22913 | 816.907ms | 4604 | 1280 | 313704 | 6832.4 | 0.411498 | 3(Loss) | true |
| Glaze | 532.35 | 0.185163 | 1059.85ms | 4604 | 1280 | 298534 | 8247.8 | 0.0218192 | 4(Loss) | true |
| simdjson (ondemand) | 425.457 | 0.365526 | 1194.21ms | 4604 | 160 | 227676 | 10320 | 0.216584 | 5(Loss) | true |
