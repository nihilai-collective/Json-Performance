
----
### Github Events Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3144.84 | 0.105692 | 762.075ms | 1691 | 4890 | 1436.42 | 512.797 | 0.133614 | 1.76781 | 6.87877 | 1.21348 | 0.000600557 | 5.91366e-05 | 1.62051e-05 | 1(Win) | true |
| simdjson (ondemand) | 2617.21 | 0.0365881 | 771.397ms | 1691 | 2560 | 130.115 | 616.176 | 0.0841178 | 2.09802 | 8.47901 | 1.44767 | 0.00072604 | 3.92704e-05 | 3.69604e-06 | 2(Loss) | true |
