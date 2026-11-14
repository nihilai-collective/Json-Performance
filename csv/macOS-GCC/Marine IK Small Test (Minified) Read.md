
----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 691.451 | 0.24772 | 645.283ms | 4604 | 1280 | 316723 | 6350 | 0.432765 | 1(Win) | true |
| Jsonifier (two-stage) | 586.367 | 0.763257 | 828.754ms | 4604 | 80 | 261314 | 7488 | 0.170648 | 2(Loss) | true |
| simdjson (reflection) | 510.252 | 0.254447 | 893.812ms | 4604 | 1280 | 613629 | 8605 | 0.109358 | 3(Loss) | true |
| Glaze | 428.513 | 0.219961 | 1034.27ms | 4604 | 1280 | 650195 | 10246.4 | 0.070318 | 4(Loss) | true |
| simdjson (ondemand) | 360.699 | 0.445653 | 1288.49ms | 4604 | 80 | 235432 | 12172.8 | 0.262192 | 5(Loss) | true |
