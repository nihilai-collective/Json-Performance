
----
### Apache Builds Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1802.23 | 0.0424593 | 5757.94ms | 94653 | 2560 | 1.1578e+06 | 50086.8 | 0.0658539 | 2.8214 | 12.0654 | 2.47043 | 0.00926106 | 1.50798e-05 | 8.24145e-06 | 1(Win) | true |
| Glaze | 1430.89 | 0.0316273 | 7053.86ms | 94653 | 4890 | 1.94667e+06 | 63085.5 | 0.140397 | 3.54851 | 15.8331 | 3.11211 | 0.0157133 | 1.89887e-05 | 1.10273e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1397.05 | 0.0314331 | 7213.93ms | 94653 | 4890 | 2.01709e+06 | 64613.2 | 0.0575225 | 3.63491 | 16.3679 | 2.94707 | 0.0130652 | 4.11275e-05 | 3.1025e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1232.8 | 0.0511591 | 8068.76ms | 94653 | 1280 | 1.79613e+06 | 73222 | 0.0482812 | 4.10752 | 16.925 | 3.13362 | 0.0108169 | 2.54878e-05 | 1.26036e-05 | 4(Loss) | true |
