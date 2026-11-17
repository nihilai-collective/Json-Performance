
----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2870 | 0.0881526 | 1179.88ms | 9578 | 1280 | 10075.5 | 3182.68 | 0.0530422 | 1.7842 | 9.85467 | 1.77427 | 0.000206773 | 1.77816e-05 | 2.52858e-06 | 1(Win) | true |
| Glaze | 2015.47 | 0.239163 | 1331.68ms | 9578 | 80 | 9398.87 | 4532.09 | 0.00965246 | 2.58358 | 13.4357 | 2.53978 | 0.000606859 | 2.21863e-05 | 6.52537e-06 | 2(Loss) | true |
| simdjson (ondemand) | 1971.77 | 0.0876637 | 1336.95ms | 9578 | 2560 | 42220.1 | 4632.54 | 0.0999792 | 2.57933 | 13.3494 | 2.03248 | 0.00241015 | 1.92906e-05 | 2.44701e-06 | 3(Loss) | true |
| Jsonifier (two-stage) | 1819.97 | 0.100084 | 1363.69ms | 9578 | 1280 | 32296.5 | 5018.92 | 0.274669 | 2.80606 | 14.0902 | 2.17739 | 0.000306203 | 1.95761e-05 | 5.54657e-06 | 4(Loss) | true |
