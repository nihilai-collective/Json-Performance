
----
### Discord Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3877.66 | 0.165065 | 187.9ms | 6701 | 1280 | 9472.34 | 1648.05 | 0.0142194 | 0.77468 | 1(Win) | true |
| simdjson (ondemand) | 3672.08 | 0.119429 | 196.446ms | 6701 | 2560 | 11058.9 | 1740.31 | 0.406849 | 0.818947 | 2(Loss) | true |
