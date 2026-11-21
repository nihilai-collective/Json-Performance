
----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 905.095 | 0.0703143 | 628.038ms | 4604 | 4890 | 56895.5 | 4851.11 | 0.0307737 | 1(Win) | true |
| Jsonifier (two-stage) | 722.255 | 0.0638963 | 758.939ms | 4604 | 40 | 603.533 | 6079.18 | 0.0204291 | 2(Loss) | true |
| Glaze | 453.02 | 0.0908247 | 1116.75ms | 4604 | 2560 | 198374 | 9692.11 | 0.0291963 | 3(Loss) | true |
| simdjson (ondemand) | 377.376 | 0.0980681 | 1318.47ms | 4604 | 30 | 3905.71 | 11634.9 | 0.095026 | 4(Loss) | true |
