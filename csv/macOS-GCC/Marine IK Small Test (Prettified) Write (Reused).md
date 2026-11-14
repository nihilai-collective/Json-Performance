
----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7921.09 | 0.442487 | 298.709ms | 24579 | 4890 | 838432 | 2959.23 | 0.389311 | 1(Win) | true |
| Glaze | 3554.48 | 0.484626 | 681.203ms | 24579 | 2560 | 2.61475e+06 | 6594.6 | 0.970086 | 2(Loss) | true |
| simdjson (reflection) | 287.804 | 0.408777 | 8319.19ms | 24893 | 640 | 7.27635e+07 | 82486 | 0.44848 | 3(Loss) | true |
