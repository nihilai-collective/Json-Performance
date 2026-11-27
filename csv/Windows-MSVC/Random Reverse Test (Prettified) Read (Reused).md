
----
### Random Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 906.967 | 0.234181 | 5015.49ms | 676745 | 80 | 2.22157e+08 | 711596 | 0.128574 | 2.72968 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 453.29 | 0.162132 | 9636.12ms | 676745 | 30 | 1.59866e+08 | 1.4238e+06 | 3.83353 | 5.46168 | -(Loss) | false |
