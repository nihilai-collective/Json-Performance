
----
### CitmCatalog Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2977.53 | 0.134958 | 8585.64ms | 500299 | 160 | 7.48285e+06 | 160241 | 0.162144 | 1.72616 | 9.78511 | 1.76254 | 0.00215867 | 1.05062e-05 | 1.41166e-06 | 1(Win) | true |
| simdjson (ondemand) | 2937.41 | 0.0407378 | 8726.88ms | 500299 | 2560 | 1.1209e+07 | 162430 | 0.0294793 | 1.74196 | 10.0929 | 1.72282 | 0.0023549 | 1.06881e-05 | 3.20824e-06 | 2(Loss) | true |
