
----
### Marine IK Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 364.687 | 0.4132 | 7285.5ms | 1834197 | 80 | 3.14241e+10 | 4.79652e+06 | 0.682167 | 8.33382 | 1(Win) | true |
| Jsonifier (generic) | 352.561 | 0.856791 | 7722.4ms | 1834197 | 30 | 5.4212e+10 | 4.96149e+06 | 1.02241 | 8.62053 | 2(Loss) | true |
