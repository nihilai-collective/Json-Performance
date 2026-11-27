
----
### Marine IK Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4161.82 | 0.530544 | 115.077ms | 4604 | 80 | 2506.33 | 1055 | 0.236407 | 0.71897 | 1(Win) | true |
| simdjson (ondemand) | 3586.32 | 0.148619 | 127.151ms | 4604 | 2560 | 8475.47 | 1224.3 | 0.0127641 | 0.835371 | 2(Loss) | true |
