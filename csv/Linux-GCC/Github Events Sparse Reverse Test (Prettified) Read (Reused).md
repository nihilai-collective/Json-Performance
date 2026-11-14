
----
### Github Events Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6474.52 | 0.0300961 | 1702.88ms | 65103 | 2560 | 21323 | 9589.45 | 0.123006 | 0.797476 | 3.81592 | 0.56641 | 0.00144953 | 5.04009e-06 | 1.90803e-06 | 1(Win) | true |
| simdjson (ondemand) | 5054.27 | 0.0363994 | 1968.76ms | 65103 | 1280 | 25590.8 | 12284.1 | 0.0105839 | 1.02159 | 4.94263 | 0.766248 | 0.0021241 | 5.8201e-06 | 2.73605e-06 | 2(Loss) | true |
