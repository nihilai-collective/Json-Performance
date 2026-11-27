
----
### Marine IK Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1270.83 | 0.108111 | 1553.89ms | 18245 | 640 | 140229 | 13691.7 | 0.190218 | 2.38794 | 1(Win) | true |
| simdjson (ondemand) | 1188.92 | 0.346794 | 1600.14ms | 18245 | 320 | 824288 | 14635 | 0.175401 | 2.55216 | 2(Loss) | true |
