
----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2106.19 | 0.157474 | 993.021ms | 18245 | 4890 | 827600 | 8261.25 | 1.5617 | 1(Win) | true |
| Jsonifier (two-stage) | 2092.43 | 0.131799 | 1023.14ms | 18245 | 4890 | 587381 | 8315.59 | 0.872775 | 2(Loss) | true |
| simdjson (ondemand) | 1365.16 | 0.0618686 | 1414.2ms | 18245 | 4890 | 304068 | 12745.6 | 0.0743216 | 3(Loss) | true |
| Glaze | 1277.64 | 0.918213 | 1629ms | 18245 | 40 | 625487 | 13618.7 | 0.609477 | 4(Loss) | true |
