
----
### Marine IK Reverse Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 877.353 | 0.29374 | 508.145ms | 4604 | 640 | 138302 | 5004.51 | 0.469052 | 2.80685 | 1(Win) | true |
| Jsonifier (two-stage) | 745.972 | 0.0694433 | 568.112ms | 4604 | 30 | 501.197 | 5885.9 | 0.0554691 | 3.3029 | 2(Loss) | true |
| simdjson (reflection) | 660.417 | 0.205073 | 668.419ms | 4604 | 4890 | 908991 | 6648.4 | 0.00847085 | 3.73421 | 3(Loss) | true |
| Glaze | 632.134 | 0.13405 | 665.898ms | 4604 | 30 | 2600.81 | 6945.87 | 0.172467 | 3.9011 | 4(Loss) | true |
| simdjson (ondemand) | 526.555 | 0.32151 | 863.395ms | 4604 | 640 | 459995 | 8338.58 | 0.183615 | 4.68732 | 5(Loss) | true |
