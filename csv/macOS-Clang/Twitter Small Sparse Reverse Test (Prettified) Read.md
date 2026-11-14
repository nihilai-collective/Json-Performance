
----
### Twitter Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3395.71 | 0.0553424 | 109.189ms | 3770 | 1280 | 439.488 | 1058.79 | 0.0429993 | 1(Win) | true |
| simdjson (ondemand) | 3019.4 | 0.0545502 | 122.535ms | 3770 | 1280 | 540.064 | 1190.75 | 0.000852934 | 2(Loss) | true |
