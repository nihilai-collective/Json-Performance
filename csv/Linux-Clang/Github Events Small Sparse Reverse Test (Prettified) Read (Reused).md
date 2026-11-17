
----
### Github Events Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3928.54 | 0.472101 | 770.893ms | 2158 | 30 | 183.499 | 523.867 | 0.00636335 | 1.40799 | 5.52178 | 0.926784 | 0.00105036 | 3.08928e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3284.37 | 0.112913 | 777.531ms | 2158 | 2560 | 1281.52 | 626.614 | 0.0186429 | 1.66856 | 6.76738 | 1.07461 | 0.00109386 | 2.24456e-05 | 3.25823e-06 | 2(Loss) | true |
