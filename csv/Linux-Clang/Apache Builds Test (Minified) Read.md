
----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1719.12 | 0.0261454 | 6025.69ms | 94653 | 4890 | 921631 | 52508.5 | 0.00525566 | 2.93531 | 13.5427 | 2.52189 | 0.00832954 | 3.26302e-05 | 2.14539e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1471.65 | 0.0461474 | 6901.23ms | 94653 | 2560 | 2.05115e+06 | 61338.2 | 0.0488554 | 3.41575 | 15.1324 | 2.84929 | 0.0120871 | 4.41167e-05 | 2.76751e-05 | 2(Loss) | true |
| Glaze | 1454.77 | 0.187928 | 6977.75ms | 94653 | 80 | 1.08781e+06 | 62049.6 | 0.0546636 | 3.47183 | 15.8336 | 3.11426 | 0.0155456 | 1.90168e-05 | 1.04328e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1201.18 | 0.0542588 | 8248.02ms | 94653 | 1280 | 2.12817e+06 | 75149.8 | 0.00646667 | 4.19104 | 16.8629 | 3.14901 | 0.0115101 | 9.0396e-05 | 6.42148e-05 | 4(Loss) | true |
