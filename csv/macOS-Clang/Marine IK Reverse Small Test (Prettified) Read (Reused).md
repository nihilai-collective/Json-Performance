
----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2282.06 | 0.0739343 | 913.384ms | 18245 | 4890 | 155394 | 7624.6 | 0.31273 | 1(Win) | true |
| Jsonifier | 2208.89 | 0.0694096 | 930.722ms | 18245 | 4890 | 146180 | 7877.16 | 0.0629678 | 2(Loss) | true |
| Glaze | 1370.37 | 0.157237 | 1435.86ms | 18245 | 30 | 11957.6 | 12697.1 | 0.0228346 | 3(Loss) | true |
| simdjson (ondemand) | 1309.47 | 0.0769286 | 1469.97ms | 18245 | 2560 | 267493 | 13287.6 | 0.0388346 | 4(Loss) | true |
