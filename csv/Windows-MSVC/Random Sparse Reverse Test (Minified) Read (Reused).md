
----
### Random Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1395.45 | 0.123762 | 7742.47ms | 409725 | 320 | 3.84308e+07 | 280013 | 0.0746061 | 2.17787 | 1(Win) | true |
| simdjson (ondemand) | 1126.93 | 0.183443 | 9435.37ms | 409725 | 640 | 2.58925e+08 | 346734 | 0.174631 | 2.69684 | 2(Loss) | true |
