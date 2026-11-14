
----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 660.252 | 0.0929461 | 684.21ms | 4604 | 30 | 1146.13 | 6650.07 | 0.187819 | 1(Win) | true |
| Jsonifier (two-stage) | 547.692 | 0.172288 | 809.885ms | 4604 | 4890 | 932864 | 8016.76 | 0.429323 | 2(Loss) | true |
| Glaze | 388.578 | 0.0602215 | 1149.2ms | 4604 | 80 | 3704.3 | 11299.4 | 0.0239999 | 3(Loss) | true |
| simdjson (ondemand) | 331.827 | 0.0975208 | 1343.72ms | 4604 | 30 | 4995.31 | 13231.9 | 0.0951336 | 4(Loss) | true |
