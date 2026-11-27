
----
### Discord Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4296.18 | 0.346092 | 195.867ms | 6701 | 80 | 2120.25 | 1487.5 | 0.501672 | 0.701185 | 1(Win) | true |
| simdjson (ondemand) | 3745.39 | 2.94307 | 204.921ms | 6701 | 640 | 1.61386e+06 | 1706.25 | 2.01794 | 0.801687 | 2(Loss) | true |
