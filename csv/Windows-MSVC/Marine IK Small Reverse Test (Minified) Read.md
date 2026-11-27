
----
### Marine IK Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 205.297 | 0.159359 | 2220.54ms | 4604 | 320 | 371716 | 21387.2 | 0.0716479 | 14.7801 | 1(Win) | true |
| simdjson (ondemand) | 163.705 | 0.0884554 | 2769.68ms | 4604 | 2560 | 1.4409e+06 | 26820.9 | 0.025931 | 18.5506 | 2(Loss) | true |
