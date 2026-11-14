
----
### Random Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1972.97 | 0.0344429 | 964.754ms | 4926 | 4890 | 3288.95 | 2381.08 | 0.0808692 | 2.6524 | 11.7343 | 2.14576 | 0.00477538 | 2.29574e-05 | 2.24177e-06 | 1(Win) | true |
| simdjson (ondemand) | 1546.46 | 0.0965621 | 1032.02ms | 4926 | 40 | 344.179 | 3037.78 | 0.0518741 | 3.37645 | 13.378 | 2.3443 | 0.00676512 | 2.03004e-05 | 0 | 2(Loss) | true |
