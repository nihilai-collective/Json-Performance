
----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 887.847 | 0.179793 | 693.387ms | 4604 | 1280 | 101192 | 4945.35 | 1.06735 | 1(Win) | true |
| Jsonifier (two-stage) | 541.42 | 0.516062 | 951.924ms | 4604 | 1280 | 2.2419e+06 | 8109.63 | 0.201487 | 2(Loss) | true |
| Glaze | 375.342 | 0.233282 | 1265.47ms | 4604 | 4890 | 3.64155e+06 | 11697.9 | 0.0289854 | 3(Loss) | true |
| simdjson (ondemand) | 343.963 | 0.621338 | 1576.35ms | 4604 | 80 | 503262 | 12765.1 | 0.973867 | 4(Loss) | true |
