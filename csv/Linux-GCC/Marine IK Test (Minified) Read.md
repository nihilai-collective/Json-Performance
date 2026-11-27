
----
### Marine IK Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 834.716 | 0.0900339 | 6484.04ms | 1834197 | 80 | 2.84785e+08 | 2.0956e+06 | 0.306313 | 2.96599 | 1(Win) | true |
| Jsonifier (two-stage) | 746.634 | 0.201304 | 7302.41ms | 1834197 | 30 | 6.6727e+08 | 2.34282e+06 | 0.089729 | 3.31589 | 2(Loss) | true |
| simdjson (reflection) | 669.369 | 0.0687539 | 8148.21ms | 1834197 | 30 | 9.68451e+07 | 2.61325e+06 | 0.652305 | 3.69866 | 3(Loss) | true |
| Glaze | 641.429 | 0.146126 | 8460.34ms | 1834197 | 80 | 1.27039e+09 | 2.72708e+06 | 0.382903 | 3.85976 | 4(Loss) | true |
| simdjson (ondemand) | 562.971 | 0.12616 | 9825.34ms | 1834197 | 30 | 4.60985e+08 | 3.10713e+06 | 0.936159 | 4.39771 | 5(Loss) | true |
