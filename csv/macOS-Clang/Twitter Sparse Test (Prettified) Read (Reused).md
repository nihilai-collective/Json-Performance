
----
### Twitter Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5231.02 | 0.0745327 | 6742.67ms | 360584 | 2560 | 6.14574e+06 | 65738.5 | 0.171813 | 1(Win) | true |
| simdjson (ondemand) | 4456.28 | 0.157996 | 7977.42ms | 360584 | 640 | 9.5135e+06 | 77167.4 | 0.135778 | 2(Loss) | true |
