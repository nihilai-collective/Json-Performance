
----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1892.82 | 0.112807 | 1101.39ms | 18245 | 40 | 4301.28 | 9192.5 | 0.00906454 | 1.60302 | 1(Win) | true |
| Jsonifier | 1532.12 | 0.100648 | 1336.79ms | 18245 | 30 | 3919.54 | 11356.7 | 0.471837 | 1.97752 | 2(Loss) | true |
| Glaze | 1042.41 | 0.193938 | 1832.21ms | 18245 | 160 | 167669 | 16691.9 | 0.123411 | 2.91235 | 3(Loss) | true |
| simdjson (ondemand) | 644.649 | 0.263666 | 2919.8ms | 18245 | 640 | 3.24138e+06 | 26991.1 | 0.0480714 | 4.71076 | 4(Loss) | true |
