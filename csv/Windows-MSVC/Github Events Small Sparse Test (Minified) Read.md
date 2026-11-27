
----
### Github Events Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3694.68 | 0.194505 | 46.54ms | 1691 | 4890 | 3524.55 | 436.483 | 0.569897 | 0.788379 | 1(Win) | true |
| simdjson (ondemand) | 3088.28 | 0.44551 | 57.6752ms | 1691 | 320 | 1731.88 | 522.188 | 0.179856 | 0.949512 | 2(Loss) | true |
