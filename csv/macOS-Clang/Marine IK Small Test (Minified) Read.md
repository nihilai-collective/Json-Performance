
----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 704.596 | 0.0473183 | 637.166ms | 4604 | 160 | 1391.13 | 6231.54 | 0.020866 | 1(Win) | true |
| Jsonifier (two-stage) | 580.432 | 0.0843973 | 808.066ms | 4604 | 4890 | 199312 | 7564.56 | 0.317351 | 2(Loss) | true |
| Glaze | 390.141 | 0.0568401 | 1146.11ms | 4604 | 80 | 3273.61 | 11254.2 | 0.0734742 | 3(Loss) | true |
| simdjson (ondemand) | 328.125 | 0.144885 | 1342.62ms | 4604 | 2560 | 962228 | 13381.2 | 0.0292827 | 4(Loss) | true |
