
----
### Twitter Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3914.52 | 0.0812572 | 8997.43ms | 360584 | 2560 | 1.30443e+07 | 87847.3 | 0.0189205 | 1(Win) | true |
| simdjson (ondemand) | 3054.76 | 0.113516 | 5838.25ms | 360584 | 640 | 1.04508e+07 | 112572 | 0.150955 | 2(Loss) | true |
