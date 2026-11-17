
----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 513.684 | 0.102503 | 985.887ms | 4604 | 40 | 3070.51 | 8547.5 | 0.166016 | 5.9056 | 1(Win) | true |
| Jsonifier (two-stage) | 474.736 | 0.21177 | 1055.61ms | 4604 | 320 | 122757 | 9248.75 | 0.027038 | 6.38963 | 2(Loss) | true |
| Glaze | 289.539 | 0.112338 | 1639.39ms | 4604 | 640 | 185735 | 15164.5 | 0.0897222 | 10.4807 | 3(Loss) | true |
| simdjson (ondemand) | 152.427 | 0.0777297 | 3017.17ms | 4604 | 640 | 320848 | 28805.3 | 0.156466 | 19.9239 | 4(Loss) | true |
