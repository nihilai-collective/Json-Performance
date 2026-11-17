
----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1778.76 | 0.500636 | 5049.21ms | 83958 | 160 | 8.1256e+06 | 45013.8 | 0.116495 | 1.39099 | 1(Win) | true |
| Glaze | 1739.87 | 0.21077 | 5231.61ms | 83958 | 640 | 6.02128e+06 | 46019.8 | 0.327249 | 1.42211 | 2(Loss) | true |
| Jsonifier | 1675.24 | 0.188001 | 5373.31ms | 83958 | 640 | 5.16738e+06 | 47795.2 | 0.0192918 | 1.477 | 3(Loss) | true |
| simdjson (ondemand) | 1238.73 | 0.315949 | 7031.2ms | 83958 | 160 | 6.67305e+06 | 64637.5 | 0.268086 | 1.99764 | 4(Loss) | true |
