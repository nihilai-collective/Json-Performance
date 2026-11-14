
----
### Github Events Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1183.65 | 0.0605204 | 901.95ms | 2158 | 320 | 354.331 | 1738.71 | 0.141108 | 4.4539 | 16.012 | 3.16914 | 0.00187819 | 5.64759e-05 | 4.3443e-06 | 1(Win) | true |
| simdjson (ondemand) | 1008.92 | 0.0408552 | 928.919ms | 2158 | 4890 | 3396.23 | 2039.84 | 0.151591 | 5.21629 | 20.7317 | 3.94764 | 0.00177141 | 0.000113242 | 4.72868e-05 | 2(Loss) | true |
