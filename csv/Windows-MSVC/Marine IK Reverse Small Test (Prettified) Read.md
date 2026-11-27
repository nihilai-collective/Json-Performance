
----
### Marine IK Reverse Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1578.61 | 0.281471 | 1135.71ms | 18245 | 320 | 308001 | 11022.2 | 0.493709 | 1.92089 | 1(Win) | true |
| Jsonifier | 1327.27 | 0.211714 | 1355.36ms | 18245 | 1280 | 986001 | 13109.5 | 0.207221 | 2.28608 | 2(Loss) | true |
| Glaze | 939.767 | 0.477712 | 1874.01ms | 18245 | 80 | 625848 | 18515 | 0.134844 | 3.231 | 3(Loss) | true |
| simdjson (ondemand) | 592.414 | 0.312873 | 2975.54ms | 18245 | 2560 | 2.1618e+07 | 29371 | 0.0600784 | 5.12583 | 4(Loss) | true |
