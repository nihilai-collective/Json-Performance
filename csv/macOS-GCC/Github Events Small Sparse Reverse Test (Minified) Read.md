
----
### Github Events Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2613.29 | 1.56921 | 64.905ms | 1691 | 2560 | 240056 | 617.1 | 0.691986 | 1(Win) | true |
| simdjson (ondemand) | 1888.22 | 0.691378 | 88.396ms | 1691 | 4890 | 170499 | 854.066 | 1.20468 | 2(Loss) | true |
