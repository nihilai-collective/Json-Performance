
----
### Random Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 821.031 | 0.0289411 | 1293.84ms | 4926 | 4890 | 13409.4 | 5721.83 | 0.0824525 | 6.31479 | 27.4139 | 5.50853 | 0.00898882 | 6.06523e-05 | 1.94286e-05 | 1(Win) | true |
| simdjson (ondemand) | 458.956 | 0.0221387 | 1744.84ms | 4926 | 4890 | 25110.7 | 10235.8 | 0.03566 | 11.2622 | 49.3512 | 9.00163 | 0.0247796 | 6.09844e-05 | 1.70623e-05 | 2(Loss) | true |
