
----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 462.584 | 0.118967 | 958.64ms | 4604 | 640 | 81605.8 | 9491.72 | 0.0345577 | 6.5568 | 1(Win) | true |
| Jsonifier | 353.033 | 0.0955669 | 1246.2ms | 4604 | 4890 | 690819 | 12437.1 | 0.258749 | 8.59367 | 2(Loss) | true |
| Glaze | 283.346 | 0.121878 | 1549.1ms | 4604 | 640 | 228278 | 15495.9 | 0.111039 | 10.7104 | 3(Loss) | true |
| simdjson (ondemand) | 164.941 | 0.10684 | 2669.11ms | 4604 | 640 | 517681 | 26619.8 | 0.00176087 | 18.4115 | 4(Loss) | true |
