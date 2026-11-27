
----
### Apache Builds Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2275.83 | 0.0319201 | 5947.22ms | 94653 | 1280 | 205176 | 39663.8 | 0.0784902 | 2.22115 | 10.4664 | 1.94124 | 0.00631993 | 1.54182e-05 | 1.06392e-05 | 1(Win) | true |
| simdjson (ondemand) | 1675.03 | 0.0402435 | 7394.61ms | 94653 | 640 | 301020 | 53890.4 | 0.0130543 | 3.03031 | 12.0929 | 2.24294 | 0.00945232 | 1.83235e-05 | 1.23312e-05 | 2(Loss) | true |
