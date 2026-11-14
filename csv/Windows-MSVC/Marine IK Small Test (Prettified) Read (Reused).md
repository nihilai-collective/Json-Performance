
----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2170.55 | 0.110909 | 925.367ms | 18245 | 2560 | 202357 | 8016.29 | 0.0608741 | 1.39651 | 1(Win) | true |
| Jsonifier | 1899.9 | 0.0599203 | 1040.49ms | 18245 | 4890 | 147259 | 9158.26 | 0.287291 | 1.59568 | 2(Loss) | true |
| simdjson (ondemand) | 1366.3 | 0.091323 | 1389.87ms | 18245 | 40 | 5410.26 | 12735 | 0.0915272 | 2.22004 | 3(Loss) | true |
| Glaze | 1094.18 | 0.0627684 | 1702.98ms | 18245 | 2560 | 255056 | 15902.2 | 0.0319437 | 2.774 | 4(Loss) | true |
