
----
### Twitter Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3650.1 | 0.491417 | 104.623ms | 3770 | 1280 | 29990.4 | 985 | 0.384304 | 1(Win) | true |
| simdjson (ondemand) | 3335.82 | 0.592534 | 117.349ms | 3770 | 2560 | 104410 | 1077.8 | 0.406579 | 2(Loss) | true |
