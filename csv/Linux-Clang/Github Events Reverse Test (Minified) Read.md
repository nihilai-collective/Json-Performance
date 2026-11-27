
----
### Github Events Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 975.983 | 0.0403321 | 5944.68ms | 53331 | 2560 | 1.13088e+06 | 52112 | 0.245379 | 5.22291 | 18.9308 | 3.84682 | 0.0157965 | 0.000112373 | 7.9127e-05 | 1(Win) | true |
| simdjson (ondemand) | 443.169 | 0.110987 | 6284.02ms | 53331 | 640 | 1.03835e+07 | 114765 | 0.14347 | 11.4981 | 40.7233 | 7.34983 | 0.0666907 | 0.000176463 | 0.000117222 | 2(Loss) | true |
