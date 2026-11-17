
----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 930.059 | 0.206643 | 629.23ms | 4604 | 2560 | 243630 | 4720.9 | 1.87687 | 1(Win) | true |
| Jsonifier (two-stage) | 724.7 | 0.793298 | 770.821ms | 4604 | 30 | 69302.4 | 6058.67 | 0.140647 | 2(Loss) | true |
| simdjson (reflection) | 631.894 | 0.289062 | 840.744ms | 4604 | 2560 | 1.03277e+06 | 6948.5 | 2.13932 | 3(Loss) | true |
| Glaze | 505.075 | 0.338949 | 1062.32ms | 4604 | 640 | 555657 | 8693.2 | 0.485482 | 4(Loss) | true |
| simdjson (ondemand) | 409.803 | 0.211282 | 1246.19ms | 4604 | 1280 | 655928 | 10714.2 | 2.53215 | 5(Loss) | true |
