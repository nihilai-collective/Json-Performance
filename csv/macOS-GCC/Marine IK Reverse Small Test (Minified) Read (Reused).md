
----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 821.801 | 0.288241 | 678.46ms | 4604 | 1280 | 303570 | 5342.8 | 0.0897599 | 1(Win) | true |
| Jsonifier (two-stage) | 633.666 | 0.637053 | 909.221ms | 4604 | 30 | 58455.1 | 6929.07 | 0.2457 | 2(Loss) | true |
| simdjson (reflection) | 616.239 | 0.1149 | 862.562ms | 4604 | 4890 | 327736 | 7125.02 | 1.12791 | 3(Loss) | true |
| Glaze | 510.808 | 0.108572 | 1007.02ms | 4604 | 4890 | 425893 | 8595.63 | 0.147161 | 4(Loss) | true |
| simdjson (ondemand) | 427.379 | 0.401431 | 1193.48ms | 4604 | 160 | 272137 | 10273.6 | 0.108899 | 5(Loss) | true |
