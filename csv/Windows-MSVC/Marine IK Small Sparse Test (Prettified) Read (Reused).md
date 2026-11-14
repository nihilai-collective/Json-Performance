
----
### Marine IK Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9358.84 | 0.124093 | 189.808ms | 18245 | 4890 | 26028.4 | 1859.18 | 0.235999 | 0.321285 | 1(Win) | true |
| simdjson (ondemand) | 7692.13 | 0.393906 | 228.618ms | 18245 | 4890 | 388230 | 2262.02 | 0.391506 | 0.392083 | 2(Loss) | true |
