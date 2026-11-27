
----
### Random Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2099.41 | 0.0356133 | 943.194ms | 4926 | 4890 | 3105.48 | 2237.67 | 0.115935 | 2.49115 | 11.3634 | 2.16058 | 0.00260543 | 2.75654e-05 | 9.71432e-06 | 1(Win) | true |
| simdjson (ondemand) | 1476.1 | 0.0449719 | 1040.6ms | 4926 | 1280 | 2622.11 | 3182.58 | 0.00574449 | 3.53177 | 14.0069 | 2.49899 | 0.00714671 | 2.41068e-05 | 1.0626e-05 | 2(Loss) | true |
