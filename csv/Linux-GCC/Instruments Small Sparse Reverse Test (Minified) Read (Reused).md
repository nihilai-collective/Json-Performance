
----
### Instruments Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3377.33 | 0.0527257 | 851.344ms | 4669 | 2560 | 1237.05 | 1318.41 | 0.0697942 | 1.57058 | 7.22082 | 1.2643 | 0.00141651 | 1.57287e-05 | 1.75693e-06 | 1(Win) | true |
| simdjson (ondemand) | 2673.46 | 0.0843786 | 882.468ms | 4669 | 2560 | 5055.98 | 1665.52 | 0.0641163 | 1.97151 | 9.22382 | 1.4954 | 0.0028136 | 9.20299e-06 | 1.00396e-06 | 2(Loss) | true |
