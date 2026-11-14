
----
### Twitter Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6080.75 | 0.162967 | 62.5353ms | 3770 | 4890 | 4540.22 | 591.268 | 0.3656 | 0.48502 | 1(Win) | true |
| simdjson (ondemand) | 4941 | 0.320226 | 77.1822ms | 3770 | 640 | 3474.94 | 727.656 | 0.539724 | 0.59931 | 2(Loss) | true |
