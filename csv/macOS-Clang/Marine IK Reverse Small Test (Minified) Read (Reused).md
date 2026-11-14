
----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 843.774 | 0.0898725 | 671.333ms | 4604 | 80 | 1749.69 | 5203.66 | 0.0703336 | 1(Win) | true |
| Jsonifier (two-stage) | 699.128 | 0.0887281 | 781.756ms | 4604 | 40 | 1242.05 | 6280.27 | 0.0486737 | 2(Loss) | true |
| Glaze | 444.568 | 0.11012 | 1124.02ms | 4604 | 4890 | 578411 | 9876.38 | 0.317668 | 3(Loss) | true |
| simdjson (ondemand) | 377.241 | 0.0396623 | 1325.13ms | 4604 | 160 | 3409.65 | 11639 | 0.0586046 | 4(Loss) | true |
