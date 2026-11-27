
----
### Marine IK Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 506.262 | 0.165665 | 895.87ms | 4604 | 4890 | 1.00947e+06 | 8672.82 | 0.0552583 | 4.87415 | 1(Win) | true |
| Jsonifier (two-stage) | 456.199 | 0.240813 | 996.406ms | 4604 | 2560 | 1.37519e+06 | 9624.57 | 0.0482743 | 5.41047 | 2(Loss) | true |
| simdjson (ondemand) | 184.175 | 0.0921952 | 2430.53ms | 4604 | 4890 | 2.36231e+06 | 23840 | 0.548703 | 13.4252 | 3(Loss) | true |
| Glaze | 156.265 | 0.136783 | 2844.91ms | 4604 | 2560 | 3.78138e+06 | 28097.9 | 0.540929 | 15.827 | 4(Loss) | true |
