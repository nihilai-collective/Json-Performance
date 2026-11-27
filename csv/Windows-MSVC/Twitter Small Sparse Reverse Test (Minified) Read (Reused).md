
----
### Twitter Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4161.2 | 0.20051 | 69.862ms | 2821 | 2560 | 4302.09 | 646.523 | 0.96338 | 0.710247 | 1(Win) | true |
| simdjson (ondemand) | 3169.45 | 0.190891 | 89.2712ms | 2821 | 1280 | 3360.63 | 848.828 | 0.321101 | 0.939406 | 2(Loss) | true |
