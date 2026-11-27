
----
### Canada Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 909.744 | 0.0466101 | 490.524ms | 4630 | 40 | 204.712 | 4853.57 | 0.159593 | 2.70624 | 1(Win) | true |
| Jsonifier (two-stage) | 838.091 | 0.373235 | 530.043ms | 4630 | 640 | 247471 | 5268.53 | 0.778646 | 2.93896 | 2(Loss) | true |
| Glaze | 770.777 | 0.0884026 | 578.701ms | 4630 | 40 | 1025.87 | 5728.65 | 0.138584 | 3.19844 | 3(Loss) | true |
| simdjson (ondemand) | 766.937 | 0.0798057 | 580.964ms | 4630 | 30 | 633.333 | 5757.33 | 0.0798343 | 3.21303 | 4(Loss) | true |
