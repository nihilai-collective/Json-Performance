
----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 696.409 | 0.650288 | 769.11ms | 4604 | 640 | 1.07581e+06 | 6304.8 | 0.780562 | 1(Win) | true |
| Jsonifier (two-stage) | 553.349 | 0.656324 | 917.151ms | 4604 | 1280 | 3.47151e+06 | 7934.8 | 1.53035 | 2(Loss) | true |
| simdjson (reflection) | 520.511 | 0.376862 | 971.129ms | 4604 | 2560 | 2.58712e+06 | 8435.4 | 0.692237 | 3(Loss) | true |
| Glaze | 434.174 | 0.384012 | 1104.75ms | 4604 | 2560 | 3.86076e+06 | 10112.8 | 0.980568 | 4(Loss) | true |
| simdjson (ondemand) | 422.098 | 0.886815 | 1247.04ms | 4604 | 30 | 255289 | 10402.1 | 0.743802 | 5(Loss) | true |
