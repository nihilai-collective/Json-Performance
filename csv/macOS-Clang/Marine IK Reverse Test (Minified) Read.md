
----
### Marine IK Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 693.612 | 0.456874 | 8048.74ms | 1834197 | 80 | 1.06204e+10 | 2.52191e+06 | 0.975101 | 1(Win) | true |
| Jsonifier (two-stage) | 508.103 | 0.579225 | 9793.25ms | 1834197 | 160 | 6.36216e+10 | 3.44266e+06 | 0.462098 | 2(Loss) | true |
| Glaze | 492.221 | 0.0442682 | 5424.42ms | 1834197 | 80 | 1.97991e+08 | 3.55374e+06 | 0.123996 | 3(Loss) | true |
| simdjson (ondemand) | 400.159 | 0.205449 | 6611.41ms | 1834197 | 80 | 6.45242e+09 | 4.37132e+06 | 2.92193 | 4(Loss) | true |
