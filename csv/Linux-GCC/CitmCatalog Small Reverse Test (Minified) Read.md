
----
### CitmCatalog Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 742.045 | 0.0319734 | 1399.24ms | 5092 | 1280 | 5604.1 | 6544.23 | 0.0253618 | 6.97978 | 30.8698 | 6.30185 | 0.00610839 | 3.03785e-05 | 5.6768e-06 | 1(Win) | true |
| simdjson (ondemand) | 451.475 | 0.0230489 | 1801.46ms | 5092 | 4890 | 30055.3 | 10756.1 | 0.0307564 | 11.3943 | 53.6296 | 10.9486 | 0.016229 | 0.000105663 | 4.99601e-05 | 2(Loss) | true |
