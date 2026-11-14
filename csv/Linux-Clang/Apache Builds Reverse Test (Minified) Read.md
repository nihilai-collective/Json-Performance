
----
### Apache Builds Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1129.28 | 0.016533 | 8713.95ms | 94653 | 4890 | 854040 | 79934.3 | 0.0100171 | 4.52716 | 20.9698 | 4.22029 | 0.0100701 | 6.87259e-06 | 2.73737e-06 | 1(Win) | true |
| simdjson (ondemand) | 717.515 | 0.121976 | 6732ms | 94653 | 40 | 941930 | 125807 | 0.00688936 | 7.04766 | 35.1168 | 7.03381 | 0.0116829 | 5.91635e-05 | 4.27879e-05 | 2(Loss) | true |
